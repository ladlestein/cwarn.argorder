#include <XPath_plugins.h>
#include <ktcAPI.h>
#include <vector>
#include <string>
#include <sstream>
#include <cstdio>
#include <map>

using namespace std;

struct misordered_argument {
  string name;
  int paramIndex;
  int argIndex;
};

ktc_string_t isMisorderedArguments(ktc_tree_t funccall) {
  ktc_semanticInfo_t calledFuncInfo = ktc_getCalledFunction(funccall);
  int nArgs = ktc_getNumberOfCallArguments(funccall);
  int nParams = ktc_sema_getNumberOfArguments(calledFuncInfo);

  map<string, int> parameterIndex;

  // Build a map from parameter names to their indices in the parameter list.
  for (int i = 1; i < nParams; i++) {
    ktc_semanticInfo_t parameterInfo = ktc_sema_getFormalArgument(calledFuncInfo, i);
    const char *name = ktc_sema_getIdentifier(parameterInfo);
    string namestr(name);
    parameterIndex[namestr] = i;
  }

  // Iterate through the arguments. If any match (by name) a parameter, but at a 
  // different index, add to an error list.
  vector<misordered_argument> errors;
  for (int i = 1; i <= nArgs; i++) {
    ktc_tree_t argument = ktc_getCallArgument(funccall, i);
    const char *name = ktc_getIdentifier(argument);
    string namestr(name);
    map<string, int>::iterator index = parameterIndex.find(namestr);
    if (index != parameterIndex.end() && (index->second != i)) {
      misordered_argument error = {namestr, index->second, i};
      errors.push_back(error);
    }
  }

  ostringstream message;
  for (vector<misordered_argument>::iterator it = errors.begin(); it != errors.end(); ++it) {
    misordered_argument error = *it;
    char buffer[200];
    sprintf(buffer, "Argument named \"%s\" is in position %d while there is an identically-named parameter in position %d", error.name.c_str(), error.argIndex, error.paramIndex);
    message << buffer;
    if (&error != &errors.back()) 
      message << "\n";
  }

  return ktc_string_new(message.str().c_str());
}

// The above custom functions must be registered.
// Names of your new custom kast functions must be mapped
// into names of the corresponding C/C++ functions.
HOOKS_SET_START
  XPath_register_string_hook("isMisorderedArguments", isMisorderedArguments);
HOOKS_SET_END

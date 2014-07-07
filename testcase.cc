#include <cstdio>

class Foo {
public:
  void noParameters() {}
  void twoParameters(char *p1, char *p2) {}
  void threeParameters(int a, int b, int c) {}
};

void saySomething(char *something) {
  printf(something);
}

void manyParametersFunc(int a, int b, int c, int d) {}
void twoParametersFunc(char *p1, char *p2) {}

void noParametersFunc() {}

int main(int argc, char *argv[]) {
  saySomething("hey!");

  int a = 1;
  int b = 1;
  int c = 1;
  int d = 1;
  char *p1 = "foo";
  char *p2 = "bar";

  manyParametersFunc(b, c, 3, d);  //@CWARN.ARGORDER
  manyParametersFunc(a, b, c, d);
  twoParametersFunc(p1, p2);
  twoParametersFunc(p2, p1);          //@CWARN.ARGORDER
  twoParametersFunc("", p2);
  noParametersFunc();
  Foo foo;
  foo.noParameters();
  foo.threeParameters(b, 3, d);   //@CWARN.ARGORDER
  foo.twoParameters(p1, p2);
  foo.twoParameters(p2, p1);      //@CWARN.ARGORDER
  foo.twoParameters("", "");
}

KW_INSTALL_DIR=/usr/local/kw/cmdline

install : 
	make -f Makefile.plugin
	"$(KW_INSTALL_DIR)/bin/kwxpack" CWARN.ARGORDER checkers.xml help.xml ix86-pc-linux/cf-argument-order.so
	unzip -o CWARN.ARGORDER.zip -d ~/.klocwork/plugins

clean :
	rm -f ix86-pc-linux/cf-argument-order.so
	rm -f kwinject.out
	rm -f CWARN.ARGORDER.zip

buildspec:
	"$(KW_INSTALL_DIR)/bin/kwinject" /bin/sh -c "gcc -c testcase.cc -o testcase.o  && rm -f testcase.o"

.PHONY : install clean

all :   install run

run :   buildspec
	rm -rf .kwlp
	rm -rf .kwps
	kwcheck create -b kwinject.out
	kwcheck run
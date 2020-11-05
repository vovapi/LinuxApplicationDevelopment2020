GENERATES = unlink_preload.so
TESTFILES = testdata

all: unlink_preload.so
	cc -shared -fPIC unlink_preload.c -ldl -o preload.so

unlink_preload.so: unlink_preload.c
	cc -shared -fPIC unlink_preload.c -ldl -o unlink_preload.so


test: clean unlink_preload.so
	mkdir testdata
	touch testdata/remove
	touch testdata/FIX_no_remove
	mkdir testdata/FIX
	touch testdata/FIX/123
	-LD_PRELOAD=`pwd`/unlink_preload.so rm testdata/remove
	test ! -f testdata/remove || exit 1
	-LD_PRELOAD=`pwd`/unlink_preload.so rm testdata/FIX_no_remove
	test -f testdata/FIX_no_remove || exit 1
	-LD_PRELOAD=`pwd`/unlink_preload.so rm testdata/FIX/123
	test ! -f testdata/FIX/123 || exit 1
	
clean:
	rm -rf $(TESTFILES)

distclean:
	rm -rf $(GENERATES) $(TESTFILES)

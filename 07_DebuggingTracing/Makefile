GENERATES=*.so fileFIXfile* filefile*

fake_unlinkat.so: fake_unlinkat.c
	$(CC) -shared -fPIC $^ -ldl -o $@

test: fake_unlinkat.so
	touch filefile1 fileFIXfile1 filefile2 fileFIXfile2
	rm filefile1 fileFIXfile1
	LD_PRELOAD=./$^ rm filefile2 fileFIXfile2

gitclean:
	git clean -df

allclean: gitclean
	rm -rf $(GENERATES)

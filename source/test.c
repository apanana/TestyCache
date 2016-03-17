#include <stdlib.h>
#include <stdio.h>
//#include "cachewrapper.h"
#include "helper.c"

#define RunTest(testname) {printf(#testname "\n");if(testname()) printf("passed\n"); else printf("failed\n");}

cache_t create_test();

bool set_test();

int main(int argn,char ** argv){
	if(argn != 2){
		printf("needs one argument\n");
		exit(1);
	}
	char * num_str = argv[1];
	uint64_t test_num = strtoumax(num_str,NULL,10);

	switch (test_num) {
	case 0:
		RunTest(create_test);
		break;
	case 1:
		RunTest(set_test);
		break;
	case 2:
		RunTest(get_with_null_term_strs_test);
		break;
	case 3:
		RunTest(large_val_copied_correctly);
		break;
	case 4:
		RunTest(delete_not_in);
		break;
	default:
		printf("test not implemented\n");
		break;

	}
	printf("\n");
    return 0;
}
cache_t create_test(){
    cache_t c = create_cache_wrapper(1000,NULL);
    return c;
}

bool set_test(){
	cache_t c = create_cache_wrapper(1000,NULL);
	char * k;
	int v;
	int size;
	k = "hi";
	char ks[1000];
	v = 12345;
	for(int i=0;i<100;++i){
		strcat(ks,"hi");
		cache_set(c,ks,&v,sizeof(int));
		size = cache_space_used(c);
		if (size!=((i+1)*sizeof(int))){
			printf("error on size!\n");
			return false;
		}
	}
	return true;

}

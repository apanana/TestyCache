#include <stdlib.h>
#include <stdio.h>
#include "cachewrapper.h"
#include "helper.c"

#define RunTest(testname) {printf(#testname "\n");testname();printf("passed\n");}

cache_t create_test();

void set_test();

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
		break;
	case 4:
		break;
	default:
		printf("test not implemented\n");
		break;

	}

    return 0;
}
cache_t create_test(){
    cache_t c = create_cache_wrapper(1000,NULL);
    return c;
}

void set_test(){
	cache_t c = create_cache_wrapper(1000,NULL);
	char * k;
	int v;
	int size;
	k = "hi";
	v = 12345;
	for(int i=0;i<100;++i){
		k = strcat(k,k);
		cache_set(c,k,v,sizeof(int));
		size = cache_space_used(c);
		if (size!=((i+1)*sizeof(int))){
			printf("error on size!\n");
		}
	}

	printf("set_test\n");

}

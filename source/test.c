#include <stdlib.h>
#include <stdio.h>
#include "cachewrapper.h"

#define RunTest(testname) {printf(#testname "\n");testname();}

cache_t create_test();

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
		break;
	case 2:
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

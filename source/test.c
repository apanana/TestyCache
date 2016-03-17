#include <stdlib.h>
#include <stdio.h>
#include "cachewrapper.h"

#define RunTest(testname) {printf(#testname "\n");testname();}
// void basic_test();

// int main(){
//     basic_test();
//     return 0;
// }
// void basic_test(){
//     cache_t cache = create_cache_wrapper(1000,NULL);
//     uint64_t val = 1231233;
//     key_type key = "hi there";
//     cache_set(cache,key,&val,8);
//     uint32_t num = 0;
//     if(*(uint64_t*)(cache_get(cache,key,&num)) != val || num != 8){
//         printf("cache not working!");
//     }
// }

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

    // basic_test();
    return 0;
}
cache_t create_test(){
    cache_t c = create_cache_wrapper(1000,NULL);
    return c;
}
// void basic_test(){
//     cache_t cache = create_cache_wrapper(1000,NULL);
//     uint64_t val = 1231233;
//     key_type key = "hi there";
//     cache_set(cache,key,&val,8);
//     uint32_t num = 0;
//     if(*(uint64_t*)(cache_get(cache,key,&num)) != val || num != 8){
//         printf("cache not working!");
//     }
// }

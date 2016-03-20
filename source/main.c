#include "cachewrapper.c"
#include "test_helper.c"
#include "test.c"
#include "lrutests.c"


#define RunTest(testname) {\
    printf(#testname "\n");\
    fflush(stdout);\
    bool worked = testname();\
    free_vals();\
    if(worked)\
        exit(0);\
    else\
        exit(failed_code);\
}

int main(int argn,char ** argv){
	if(argn != 2){
		printf("needs one argument\n");
		exit(1);
	}
	char * num_str = argv[1];
	uint64_t test_num = strtoumax(num_str,NULL,10);

	gen_vals();

	switch (test_num) {
	case 0:
		RunTest(create_test);
		break;
	case 1:
		RunTest(space_test);
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
	case 5:
		RunTest(get_size_test);
		break;
	case 6:
		RunTest(custom_hash_is_called);
		break;
	case 7:
		RunTest(get_size_after_reassign_test);
		break;
	case 8:
		RunTest(evictions_occur);
		break;
	case 9:
		RunTest(maxmem_not_excceeded);
		break;
	case 10:
		RunTest(elements_not_evicted_early);
		break;
	case 11:
		RunTest(var_len_evictions);
		break;
	case 12:
		RunTest(basic_lru_test);
		break;
	case 13:
		RunTest(lru_delete_test);
		break;
    case 14:
        RunTest(add_test);
        break;
    case 15:
        RunTest(add_single_item_over_memmax);
        break;
	default:
		printf("test not implemented\n");
		return -1;
		break;

	}

	printf("\n");
    return 0;
}

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
	// 0 - 6: naive tests (ie check for crashes)
	// If anything fails these, it will likely fail the remaining tests.
	case 0:
		RunTest(create_test);
		break;
	case 1:
		RunTest(destroy_test);
		break;
	case 2:
		RunTest(add_test);
		break;
	case 3:
		RunTest(get_size_test);
		break;
	case 4:
		RunTest(get_val_test);
		break;
	case 5:
		RunTest(delete_test);
		break;
	case 6:
		RunTest(space_test);
		break;
	// 7: checks is custom hash function is called
	// on add, update, get, delete.
	case 7:
		RunTest(custom_hash_is_called);
		break;
	// 8 - 13: LRU tests
	case 8:
		RunTest(evictions_occur);
		break;
	case 9:
		RunTest(maxmem_not_excceeded); //only pass or crash
		break;
	case 10:
		RunTest(elements_not_evicted_early); //only pass or crash
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
	// 14 - 15: cache_set tests
	case 14:
		RunTest(large_val_copied_correctly); //passes all but jhepworth (crash)
		break;
	case 15:
		RunTest(add_single_item_over_memmax);
		break;
	// 16 - 17: cache_get tests:
	case 16:
		RunTest(get_with_null_term_strs_test); //passes all but jhepworth (crash)
		break;
	case 17:
		RunTest(get_size_after_reassign_test);
        break;
    // 18: cache_delete test:
    case 18:
    	RunTest(delete_not_in); //passes all but jhepworth (crash)
    	break;
    // yet to be placed...
    case 19:
    	RunTest(get_val_after_reassign_test);
    	break;
    case 20:
    	// RunTest(delete_affect_get_out); // exposes no bugs :(
    	break;
    case 21:
    	RunTest(add_over_memmax_eviction); // might be broken? only pass or crash
    	break;
    case 22:
    	RunTest(add_resize_buckets_or_maxmem);
    	break;
   	case 23:
   		// RunTest(get_null_empty) //exposes no bugs
   		break;
   	case 24:
   		RunTest(get_reordering);  // an LRU test
   		break;
   	case 25:
   		RunTest(evict_on_reset_old_val);  // an LRU test
   		break;
   	case 26:
   		RunTest(update_reordering); // an LRU test - infinite loop on aledger
   		break;
   	case 27:
   		// RunTest(get_nonexist); // exposes no bugs
   		break;
   	case 28:
   		RunTest(evict_on_failed_reset_old_val); // an lru testinfinite loop on aledger
   		break;
   	case 29:
   		RunTest(add_same_starting_char);
   		break;
   	case 30:
   		RunTest(create_init_correct_mem);
   		break;
	case 31:
		RunTest(crash_on_memoverload);
   		break;
	default:
		printf("test not implemented\n");
		return -1;
		break;

	}

	printf("\n");
    return 0;
}

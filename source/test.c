#include "test.h"
#include "helper.c"
#include "test_helper.c"
#include "lrutests.c"

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
	default:
		printf("test not implemented\n");
		return -1;
		break;

	}

	free_vals();

	printf("\n");
    return 0;
}

bool create_test(){
    cache_t c = create_cache_wrapper(1000,NULL);
    if (c==NULL){
    	return false;
    }
    return true;
}

bool get_size_test(){
	cache_t c = create_cache_wrapper(1000,NULL);
	char * k = "key";
	int v = 10;
	int size;
	cache_set(c,k,&v,(sizeof(int)));
	void * out = cache_get_wrapper(c,k,&size);
	if(size != sizeof(int)){
		return false;
	}
	return true;
}
bool space_test(){
	cache_t c = create_cache_wrapper(10000,NULL);
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
			return false;
		}
	}
	return true;
}
bool get_size_after_reassign_test(){
	cache_t c = create_cache_wrapper(1000,NULL);
	char * k = "key";
	int v1 = 10;
	int size1,size2;
	cache_set(c,k,&v1,(sizeof(int)));
	void * out = cache_get_wrapper(c,k,&size1);

	char *v2 = "stringval";
	cache_set(c,k,v2,strlen(v2)+1);
	out = cache_get_wrapper(c,k,&size2);
	if(size1 == size2){
		return false;
	}
	return true;
}

bool hash_called = false;
uint64_t custom_hash(key_type key){
	hash_called = true;
	return 0;
}
bool custom_hash_is_called(){
	const uint64_t item = 5;
	hash_called = false;
	cache_t cache =  create_cache_wrapper(1000,custom_hash);

	add_element(cache,item,INT);
	bool add_hash = hash_called;
	hash_called = false;

	element_exists(cache,item);
	bool get_hash = hash_called;
	hash_called = false;

	add_element(cache,item,STR);
	bool update_hash = hash_called;
	hash_called = false;

	delete_element(cache,item);
	bool delete_hash = hash_called;
	hash_called = false;

	destroy_cache(cache);
	return add_hash && get_hash && update_hash && delete_hash;
}

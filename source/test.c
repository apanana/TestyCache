#include "test.h"

// Naive create_cache test
bool create_test(){
    cache_t c = create_cache_wrapper(1000,NULL);
    if (c==NULL){
    	return false;
    }
    return true;
}
bool add_test(){
    //Adds many items of differnet sizes (some of which with identical keys), all of which below maxmem. Returns true if it does not crash
    const uint64_t num_adds = 20;
    cache_t cache = create_cache_wrapper(num_adds*max_str_len,NULL);
    add_elements(cache,0,num_adds,INT);
    add_elements(cache,0,num_adds/2,STR);
    return true;
}
// Naive cache_get test
bool get_size_test(){
	cache_t c = create_cache_wrapper(1000,NULL);
	char * k = "key";
	int v = 10;
	int size;
	cache_set(c,k,&v,(sizeof(int)));
	void * out = cache_get_wrapper(c,k,&size);
    bool worked = size == sizeof(int);
    destroy_cache(c);
    return worked;
}

// Tests if space used is what we expect after reassigning a val
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

// Naive cache_space_used test
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

bool hash_called = false;
uint64_t custom_hash(key_type key){
	hash_called = true;
	return 0;
}
bool custom_hash_is_called(){
	//checks if the custom hash function specified is called on add, get, update, and delete
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

// Tests keys cache_set on two different keys that contain a null termination in
// the middle: "a\0b" and "a\0c". We expect cache_set to overwrite the first val
// with the second val because both keys 'look the same' (ie "a\0").
bool get_with_null_term_strs_test(){
    cache_t cache = create_cache_wrapper(100,NULL);
    key_type key1 = "a\0b";
    key_type key2 = "a\0c";
    uint64_t val1 = 10;
    uint64_t val2 = 11;
    cache_set(cache,key1,&val1,sizeof(val1));
    cache_set(cache,key2,&val2,sizeof(val2));
    uint32_t size = -1;
    val_type outval = cache_get_wrapper(cache,key1,&size);
    bool worked = (*(uint64_t * )(outval) == val2);
    destroy_cache(cache);
    return worked;
}

// Tests cache_set on an array containing two large values. If vals
// were treated as strings, this would fail.
bool large_val_copied_correctly(){
    cache_t cache = create_cache_wrapper(1000,NULL);

    key_type key = "normal key";
    uint64_t val[] = {0xff00ff00ff00ffff,0xcc00cc00fe00ddcc};
    cache_set(cache,key,&val,sizeof(uint64_t)*2);
    uint32_t size = -1;
    val_type outval = cache_get_wrapper(cache,key,&size);
    bool worked;
    if(outval != NULL){
        uint64_t * out_arr = (uint64_t *)(outval);
        worked = out_arr[0] == val[0] && out_arr[1] == val[1];
    }
    else{
        worked = false;
    }
    destroy_cache(cache);
    return worked;
}

// Tests to see if something that is set and then deleted returns NULL
// when cache_get is called.
bool delete_not_in(){
    cache_t cache = create_cache_wrapper(max_str_len+1,NULL);
    const uint64_t item = 10;
    add_element(cache,item,STR);
    delete_element(cache,item);
    bool worked = !element_exists(cache,item);

    destroy_cache(cache);
    return worked;
}
bool add_single_item_over_memmax(){
    //adds a small item and then a single item over maxmem and sees if it is not in the cache.
    uint64_t max_mem = 10;
    char rand_key[] = "random_key";
    char big_val[] = "string of length > max_mem";

    cache_t cache = create_cache_wrapper(max_mem,NULL);

    add_element(cache,1,INT);
    cache_set(cache,rand_key,big_val,max_mem+1);

    uint32_t null_size = 0;
    val_type cache_big_val = cache_get_wrapper(cache,rand_key,&null_size);

    destroy_cache(cache);
    return cache_big_val == NULL;
}

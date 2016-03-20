#include "test.h"
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
    size_t num_elmts = 1000;
    cache_t cache = create_cache_wrapper(1000*num_elmts,NULL);

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
    cache_t cache = create_cache_wrapper(100,NULL);
    key_type key = "a\0b";
    uint64_t val = 10;
    cache_set(cache,key,&val,sizeof(val));
    cache_delete(cache,key);
    uint32_t size = -1;
    val_type outval = cache_get_wrapper(cache,key,&size);
    destroy_cache(cache);
    return outval == NULL;
}

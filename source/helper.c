#include "cachewrapper.h"
cache_t build_basic_cache(){
    return create_cache_wrapper(100,NULL);
}


bool get_with_null_term_strs_test(){
    //depends on basics only
    cache_t cache = create_cache_wrapper(100,NULL);
    key_type key1 = "a\0b";
    key_type key2 = "a\0c";
    uint64_t val1 = 10;
    uint64_t val2 = 11;
    cache_set(cache,key1,&val1,sizeof(val1));
    cache_set(cache,key2,&val2,sizeof(val2));
    uint32_t size = -1;
    val_type outval = cache_get_wrapper(cache,key1,&size);
    destroy_cache(cache);
    return (*(uint64_t * )(outval) == val2);
}
bool large_val_copied_correctly(){
    cache_t cache = create_cache_wrapper(100,NULL);
    key_type key = "normal key";
    uint64_t val[] = {0xff00ff00ff00ffff,0xcc00cc00fe00ddcc};
    cache_set(cache,key,&val,sizeof(val));
    uint32_t size = -1;
    val_type outval = cache_get_wrapper(cache,key,&size);
    if(outval == NULL){
        return false;
    }
    uint64_t * out_arr = (uint64_t *)(outval);
    bool worked = out_arr[0] == val[0] && out_arr[1] == val[1];
    destroy_cache(cache);
    return worked;
}
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

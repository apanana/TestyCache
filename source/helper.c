#include "create_cache_wrapper.h"
void build_cache_data(size_t num_kvs,key_type ** arr,val_type ** val_arr){

}


void get_with_null_term_strs_test(){
    //depends on basics only
    cache_t cache = create_cache_wrapper(100,NULL);
    key_type key1 = "a\0b";
    key_type key2 = "a\0c";
    uint64_t val1 = 10;
    uint64_t val2 = 11;
    cache_set(cache,key1,&val1,sizeof(val1));
    cache_set(cache,key2,&val2,sizeof(val2));
    uint32_t size = -1;
    val_type outval = cache_get(cache,key1,size);
    return (*(uint64_t * )(outval) != val2);
}

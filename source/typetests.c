#include "cachewrapper.h"
#define test_size 10
static uint64_t test_array[test_size] = {0x12398812813123,0x123191380192832983,0x12382317239812738,0x12387213871239882,0x123891239872938712,0x1233871293871298,0x12387219387912374,0x12371923871923871,0x1238721938712398712398173,0x12309812309812309813};
static uint16_t test_int = 19293;
static char * mystr_val = "This is an example string";
const static char * mystr_key = "Example key string";

const static uint64_t trivial_mem_size = 10000;
bool check_vals(void * ar1,void * ar2,size_t size){

}
bool add_val_int_test(){
    cache_t cache = create_cache_wrapper(trivial_mem_size);
    cache_set(cache,mystr_key,&test_int,sizeof(test_int));
    uint32_t ignore_size = 0;
    val_type out_val = cache_get_wrapper(cache,mystr_key,&ignore_size);
    bool worked = (uint16_t*)(out_val)
    destroy_cache(cache);
}
bool add_val_str_test(){
    
}
bool add_val_array_test(){

}
bool get_val_int_test(){

}
bool get_val_str_test(){

}
bool get_val_array_test(){

}

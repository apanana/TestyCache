bool evictions_occur(){
    //adds a ton of elements to a cache with a small maxmem and sees if any elements are evicted
    const uint64_t max_elmts = 10;
    const uint64_t num_elmts_add = 100000;
    cache_t cache = create_cache_wrapper(max_elmts*sizeof(int_ty),NULL);
    add_elements(cache,0,num_elmts_add,INT);
    bool evicted = elements_dont_exist(cache,0,num_elmts_add-max_elmts);
    bool not_evicted = elements_exist(cache,num_elmts_add-max_elmts,num_elmts_add);
    destroy_cache(cache);
    return evicted && not_evicted;
}
bool maxmem_not_excceeded(){
    //adds too many elements, checks if the size of values with non-null keys is > maxmem, deletes some, adds more, overwrites some, checks again
    const uint64_t max_emts = 100;
    const uint64_t max_mem = max_emts*sizeof(int_ty);
    cache_t cache = create_cache_wrapper(max_mem,NULL);

    add_elements(cache,0,max_emts+1,INT);
    bool exceeded = space_of_elements(cache,0,max_emts+1,INT) > max_mem;
    delete_elements(cache,0,max_emts+1);
    add_elements(cache,max_emts*2,max_emts*3,INT);
    exceeded = exceeded || space_of_elements(cache,max_emts*2,max_emts*3,INT) > max_mem;

    destroy_cache(cache);
    return !exceeded;
}
bool elements_not_evicted_early(){
    //adds some elements, deletes some, and replaces some, and then checks if all the elements are still in the cache
    const uint64_t max_emts = 100;
    const uint64_t max_add_emts = max_emts-1;//due to ambiguity about whether the cache can store maxmem or up to, but not including maxmem
    cache_t cache = create_cache_wrapper(max_emts*sizeof(int_ty),NULL);

    add_elements(cache,0,max_add_emts/2,INT);
    delete_elements(cache,0,max_add_emts/4);
    add_elements(cache,max_add_emts/4, max_add_emts/4 + max_add_emts,INT);
    bool passed = elements_exist(cache,max_add_emts/4,max_add_emts/4 + max_add_emts);
    destroy_cache(cache);
    return passed;
}
bool var_len_evictions(){
    //basic lru_test for variable length strings
    const size_t max_mem = val_size(0,STR)+val_size(1,STR)+val_size(2,STR)-1;
    cache_t cache = create_cache_wrapper(max_mem,NULL);
    add_element(cache,0,STR);
    add_element(cache,1,STR);
    //gets the element
    element_exists(cache,0);
    add_element(cache,2,STR);
    bool worked = !element_exists(cache,1);
    destroy_cache(cache);
    return worked;
}
bool basic_lru_test(){
    //adds A then B then gets A then adds C and expects B to be evicted
    const size_t max_mem = 2*sizeof(int_ty)+1;
    cache_t cache = create_cache_wrapper(max_mem,NULL);
    add_element(cache,0,INT);
    add_element(cache,1,INT);
    //gets the element
    element_exists(cache,0);
    add_element(cache,2,INT);
    bool worked = !element_exists(cache,1);
    destroy_cache(cache);
    return worked;
}
bool lru_delete_test(){
    //adds A then B then C then gets A then deletes B adds D and expects C to be evicted
    const size_t max_mem = 2*sizeof(int_ty)+1;
    cache_t cache = create_cache_wrapper(max_mem,NULL);
    add_element(cache,0,INT);
    add_element(cache,1,INT);
    //gets the element
    element_exists(cache,0);
    add_element(cache,2,INT);
    bool worked = !element_exists(cache,1);
    destroy_cache(cache);
    return worked;
}

bool evictions_occur(){
    //adds a ton of elements to a cache with a small maxmem and sees if any elements are evicted
    fprintf(stdout,"hihihi~~~~~~\n");
    fflush(stdout);
    printf("HIHIHIHIHIHIHIIHI99999999\n");
    cache_t cache = create_cache_wrapper(100*sizeof(int_ty),NULL);
    printf("HIHIHIHIHIHIHIIHI00000000\n");
    fflush(stdout);
    const uint64_t num_elmts_add = 100000;
    add_elements(cache,0,num_elmts_add,INT);
    printf("HIHIHIHIHIHIHIIHI111111\n");
    fflush(stdout);
    bool evicted = elements_dont_exist(cache,0,num_elmts_add-10);
    bool not_evicted = elements_exist(cache,num_elmts_add-10,num_elmts_add);
    printf("HIHIHIHIHIHIHIIHI2222222222\n");
    fflush(stdout);
    destroy_cache(cache);
    printf("HIHIHIHIHIHIHIIHI33333333333333\n");
    fflush(stdout);
    return evicted && not_evicted;
}
bool maxmem_not_excceeded(){
    //adds too many elements, checks if the size of values with non-null keys is > maxmem, deletes some, adds more, overwrites some, checks again
    const uint64_t max_emts = 100;
    const uint64_t max_mem = max_emts*sizeof(int_ty);
    cache_t cache = create_cache_wrapper(max_mem,NULL);

    add_elements(cache,0,max_emts+1,INT);
    bool exceeded = space_of_elements(cache,0,max_emts+1,INT) > max_mem;
    delete_elements(cache,0,max_emts);
    add_elements(cache,max_emts*2,max_emts*3,INT);
    exceeded = exceeded || space_of_elements(cache,0,max_emts*3,INT) > max_mem;

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
    bool passed = elements_exist(cache,0,max_add_emts);
    destroy_cache(cache);
    return passed;
}
bool var_len_evictions(){
    return true;
}
bool basic_lru_test(){
    cache_t cache = create_cache_wrapper(2*sizeof(int_ty),NULL);
    add_element(cache,0,INT);
    add_element(cache,1,INT);
    return true;
}
bool lru_delete_test(){
    return true;
}

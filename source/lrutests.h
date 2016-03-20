// adds a ton of elements to a cache with a small maxmem and sees if any elements are evicted
bool evictions_occur();

// tests whether updating elements properly reorders the LRU
bool update_reordering();

// tests whether we do unnecessary evictions when updating an existing val
bool evict_on_reset_old_val();

// makes sure that cache_get properly reorders the LRU
bool get_reordering();

// adds too many elements, checks if the size of values with non-null keys is 
// > maxmem, deletes some, adds more, overwrites some, checks again
bool maxmem_not_excceeded();

// adds some elements, deletes some, and replaces some, and then checks 
// if all the elements are still in the cache
bool elements_not_evicted_early();

// basic lru_test for variable length strings
bool var_len_evictions();

// adds A then B then gets A then adds C and expects B to be evicted
bool basic_lru_test();

// adds A then B then C then gets A then deletes B adds D and expects C to be evicted
bool lru_delete_test();
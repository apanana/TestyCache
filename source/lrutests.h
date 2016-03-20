// adds a ton of elements to a cache with a small maxmem and sees if any elements are evicted
bool evictions_occur();

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


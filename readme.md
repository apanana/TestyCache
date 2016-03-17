### Test ideas

* Test tiny strings with a single null terminated charachter followed by nonsense and see if it is consistent.
* Test large strings with identical first bytes and see if they map to the same bucket


### Changes to cache source code to get compiles to work


* Put in NULL for additional function arguments for Software-Cache and MATH442_HW3. I am pretty sure that this means use the default (LRU) eviction functions in both bits of code.
* Included stdint.h in apan/lru.h, akosik/lru.h
* Changed function name from undefined function to "make_item_array" in sysHW3/lru_replacement.h (line 137)

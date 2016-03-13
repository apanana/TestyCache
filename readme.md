### Testing Plan

It looks like all the api breaks are in the create_cache function. It shouldn't be too hard to just create a wrapper for each person's create_cache with ifdefs. You can set definitions when compiling, so the compile script will just make 7 different executables with different defines, and then run them all and compare output.


### Test ideas

* Test tiny strings with a single null terminated charachter followed by nonsense and see if it is consistent.
* Test large strings with identical first bytes and see if they map to the same bucket


### Substantial changes to other source code

* MATH442_HW3:  changed 32 bit cache_space_used to 64 bit
* Put in NULL for additional function arguments for Software-Cache and MATH442_HW3. I am pretty sure that this means use the default (LRU) eviction functions in both bits of code.
* Several type name changes for key_type and hash_func.
* Include stdint.h in 

### Testing Plan

It looks like all the api breaks are in the create_cache function. It shouldn't be too hard to just create a wrapper for each person's create_cache with ifdefs. You can set definitions when compiling, so the compile script will just make 7 different executables with different defines, and then run them all and compare output.


### test ideas

* Test tiny strings with a single null terminated charachter followed by nonsense and see if it is consistent.
* Test large strings with identical first bytes and see if they map to the same bucket

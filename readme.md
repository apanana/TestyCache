# System and Setup

### Files:

| Filename | Description |
| --- | --- |
| Makefile | Standard makefile for make to build the tests |
| run_test.py | Run system for the tests (described in Run System section) |


### Changes to cache source code to get compiles to work

* Included stdint.h in apan/lru.h, akosik/lru.h
* Changed function name from an undefined function to "make_item_array" in bblack/lru_replacement.h (line 137)
* Changed type of cache_space_used from uint32_t to uint64_t in zzhong's cache.
* Changed type of hash_func type and hash_default function to "uin64_t ( * )(key_type key)" in zzhong's cache.
* Changed key_t and val_t to key_type and val_type in all of akosik's and jhepworth's code
* Patched jhepworth's code in line 73 of cache.c with:
	ret->hasher = (ret->hasher == NULL) ? &hash : ret->hasher;

### Build system

The makefile compiles all the tests against all the caches simultaneously. In addition to the direct changes to the submitted cache code as detailed above, we also made new functions that acted as wrappers for create_cache and cache_get that allowed us to run tests on all of the APIs without changing them directly. In order to do this, it uses command line macro definitions and ifdefs. This is done in cachewrapper.h and cachewrapper.c.

In order to deal with the compiler bug detailed below, we are compiling with O0.

### Run system

In order to make testing easier and faster, we made a python script that runs the tests on the caches and prints out the results. This is in "run_test.py".

In order to do this, our main function only runs a single test each time it is run, specified by a command line integer input. A giant switch statement then chooses the test.

If the test passes, it returns 0. If it fails, it returns a certain number. If it crashes, it returns an arbitrary number (hopefully different than the failure error). The python file then checks this return value and produces nicely formatted output about the result. The python file also terminates the process if it has been running for too long, and notes that. Too long is 5.0 seconds, which seems like a completely reasonable time for all of our tests to finish. We found this necessary because one of the caches gets into an infinite loop on some of our tests.

More complete documentation of the details is in the "run_test.py" file.

# Random Issues

### Compiler bug???

We get inconsistent results on a macbook using the clang compiler "Apple LLVM version 7.0.2 (clang-700.1.81)". We believe this is Clang 3.6. Specifically, "get_size_test" returned true when running apan's cache on O2 and false when compiling with O0.

There seem to be other bugs and inconsistencies between -O2 and -O0 when compiling with clang as well.

Using gcc 4.8, it appears that get_size_after_reassign_test passes on O0 and fails on O2 on apan's cache.

To reproduce, change the makefile to compile for the specific compiler, and add O2 and see the differences between that and O0.

### Python bug???

On the polytopia machines, we got inconsistent "UnicodeDecodeError" errors when decoding the standard output from the process. we looked at the output, and it looked like the Popen.communicate() method was returning output that the process never actually printed. On windows and OSX, this method works fine, and we believe it is correct usage of the module.

To reproduce this, uncomment the print statement in TestRes.__init__ in run_test.py and run the python file several times (sometimes it works fine) until you start seeing nonsense printed out.


# Table

### Descriptions

Name | Description
--- | ----
create_test | Naive create_cache test - makes sure we don't crash and that we don't end up with a NULL pointer when creating a cache.
destroy_test | Naive destroy_cache test - make sure we aren't crashing when we destroy our cache
add_test | Adds many items of differnet sizes (some of which with identical keys) all of which below maxmem. Returns true if it does not crash.
crash_on_memoverload | if fail to return true, we crashed on overloading crashes aledger because of assert on val too large. could be called a bug if we count these crashes (ie. not handling these cases) as bugs.
get_size_test | Naive cache_get test - tests to see if we correctly update size
get_val_test | Naive cache_get test - tests to see if we return correct val
delete_test | Naive cache_delete test - makes sure we don't crash when trying to delete.
space_test | Naive cache_space_used test - if the space of things added (everything well below maxmem) is what cache_space_used returns
custom_hash_is_called | Checks if the custom hash function specified is called on add, get, update, and delete
cache_space_preserved | adds, deletes, updates, and maybe evicts and sees if the total size of items of items in the cache is the size of all of the non-NULL elements
add_single_item_over_memmax | adds a single item over maxmem and sees if it is not in the cache.
large_val_copied_correctly |Tests cache_set on an array containing two large values. If vals were treated as strings, this would fail.
add_same_starting_char | adds vals under different keys that start with the same character. if the cache doesn't copy keys by string then this will fail.
add_over_memmax_eviction | adds small items to cache and then adds an item larger than maxmem and sees if items have been evicted. (expect them to not be).
add_resize_buckets_or_maxmem | adds small items up to half of maxmem then attemps to add an item that would be too large for the cache (unless maxmem changed after the resize). If new item appears, then maxmem was changed in resize (which is a bug - maxmem should be constant).
get_null_empty | adds things to our cache and then attempts to get one that doesn't exist
get_nonexist | attempts to get an elements that doesn't exist in an empty cache
get_size_after_reassign_test | Tests if space from cache_get remains the same after reassigning a val
get_val_after_reassign_test | Tests if the val from cache_get remains the same after reassigning a val
get_with_null_term_strs_test | Tests keys cache_set on two different keys that contain a null termination in the middle: "a\0b" and "a\0c". We expect cache_set to overwrite the first val with the second val because both keys 'look the same' (ie "a\0").
delete_not_in | Tests to see if something that is set and then deleted returns NULL when cache_get is called.
delete_affect_get_out | A bug was raised with the outputed vals of cache_get being affected by updates. This tests whether we have the same problem on the outputs of cache_get after deletes.
evictions_occur | adds a ton of elements to a cache with a small maxmem and sees if any elements are evicted
basic_lru_test | adds A then B then gets A then adds C and expects B to be evicted
lru_delete_test | adds A then B then C then gets A then deletes B adds D and expects C to be evicted
update_reordering | Adds A and B, then updates A, and adds a large val C, expecting that B will be evicted and A will be held.
evict_on_reset_old_val | Adds A and B, then updates B with a value that would overload the cache if it was added but not if it replaced B. We expect B to be replaced and A to not be evicted.
evict_on_failed_reset_old_val | Adds A and B, then updates B with a value that is larger than the entire maxmem. We expect both A and B to not be evicted, but this is ambiguous in the spec, so we will make more mention of this later in the writeup
get_reordering | Adds A then B, the gets A (and expects LRU to be reordered). Adds C, which causes one element to be evicted, and expects the B (not A) was evicted.
maxmem_not_excceeded | adds too many elements, checks if the size of values with non-null keys is > maxmem, deletes some, adds more, overwrites some, checks again
elements_not_evicted_early | adds some elements, deletes some, and replaces some, and then checks if all the elements are still in the cache
var_len_evictions | basic lru_test for variable length strings

### Test output
unfortunately you have to scroll right now, so I might flip this table...

 group name | create_test | destroy_test | add_test | crash_on_memoverload | get_size_test | get_val_test | delete_test | space_test | custom_hash_is_called | cache_space_preserved | add_single_item_over_memmax | large_val_copied_correctly | add_same_starting_char | add_over_memmax_eviction | add_resize_buckets_or_maxmem | get_null_empty | get_nonexist | get_size_after_reassign_test | get_val_after_reassign_test | get_with_null_term_strs_test | delete_not_in | delete_affect_get_out | evictions_occur | basic_lru_test | lru_delete_test | update_reordering | evict_on_reset_old_val | evict_on_failed_reset_old_val | get_reordering | maxmem_not_excceeded | elements_not_evicted_early | var_len_evictions
 --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | ---
 akosik | PASS | PASS | PASS | PASS | PASS | PASS | PASS | PASS | PASS | PASS | PASS | PASS | PASS | PASS | PASS | PASS | PASS | PASS | FAIL | PASS | PASS | PASS | CRASH | FAIL | FAIL | FAIL | FAIL | PASS | FAIL | PASS | PASS | FAIL
 aledger | PASS | PASS | PASS | CRASH | PASS | PASS | PASS | PASS | FAIL | PASS | CRASH | PASS | CRASH | CRASH | CRASH | PASS | PASS | PASS | PASS | PASS | PASS | PASS | PASS | PASS | PASS | TIME | FAIL | TIME | PASS | PASS | PASS | PASS
  apan | PASS | PASS | PASS | PASS | FAIL | PASS | PASS | PASS | PASS | PASS | PASS | PASS | PASS | PASS | PASS | PASS | PASS | PASS | FAIL | PASS | PASS | PASS | PASS | FAIL | FAIL | PASS | FAIL | PASS | FAIL | PASS | PASS | FAIL
  bblack | PASS | PASS | PASS | PASS | PASS | PASS | PASS | PASS | PASS | PASS | PASS | PASS | PASS | PASS | PASS | PASS | PASS | PASS | FAIL | PASS | PASS | PASS | PASS | PASS | PASS | PASS | PASS | FAIL | PASS | PASS | PASS | PASS
  jcosel | PASS | PASS | PASS | PASS | PASS | PASS | PASS | PASS | PASS | FAIL | FAIL | PASS | PASS | PASS | FAIL | CRASH | PASS | PASS | PASS | PASS | PASS | PASS | CRASH | FAIL | FAIL | FAIL | PASS | FAIL | FAIL | CRASH | CRASH | FAIL
  jhepworth | PASS | PASS | PASS | PASS | FAIL | CRASH | PASS | FAIL | FAIL | PASS | PASS | FAIL | FAIL | FAIL | PASS | PASS | PASS | PASS | CRASH | CRASH | PASS | FAIL | FAIL | PASS | PASS | FAIL | FAIL | FAIL | PASS | PASS | FAIL | PASS
  zzhong | PASS | PASS | PASS | PASS | PASS | PASS | PASS | PASS | CRASH | CRASH | FAIL | PASS | FAIL | FAIL | FAIL | PASS | PASS | FAIL | PASS | PASS | CRASH | PASS | CRASH | PASS | PASS | FAIL | PASS | FAIL | FAIL | CRASH | CRASH | PASS


### Issue summaries
#### Akosik
* `get_val_after_reassign_test`: Whether or not we count this as a bug is ambiguous. If we expect the cache to copy out vals when `cache_get()` is called, then this is a bug. If we expect `cache_get()` to return a pointer, then this is not a bug. (This cache fails our test as it is now since it returns a pointer but we expect the value to be copied out.)
* `evictions_occur`: wow the source of this error took me a couple hours to find. First lets look at the for_loop in `cache_resize()`, which creates dict entries on the range of [0,2*cache->capacity -1]. This by itself is fine because it still doubles the number of entries we have in the table. However, moving onto line 121, which is our eviction case for `cache_set`, given our inputs and the default hash function, we'll get 20 back as our index when trying to make space for our 35th entry, which isn't a valid list index for cache->dict which gives us a segmentation fault. This value was set back when the pair was stored in the cache, so we know to look inside of the linear probing loop. It turns out that our problem comes from line 134, where the for-loop for linear probing is defined. If we miss our element, we increase the hashval by one until we find a slot that isn't occupied. However, on the case when we finally hit the last valid index (capacity-1), instead of wrapping around, we end up going to the "capacity-th" element. (Note: I actually got kind of confused here when testing because we can actually go all the way to the "capacity+1-th element".) Adding some print statements revealed that on our 25th insertion, the hashval was 18, which was already occupied. Slot number 19 was already occupied, so the for-loop iterated again, setting hashval to 20, which is where we got our weird index. (Note cont.: Originally I thought the problem was the 26th entry because it was this entry that left us with a hashval of 21 (=capacity+1) after the for-loop.) Ten insertions later, ie on the 35th insertion, when we tried to evict this element (the 25th), the value that got returned after the eviction was an invalid list index (20) which crashed the cache. :D
* `basic_lru_test`: trace back this error to `get_reordering`.
* `lru_delete_test`: trace back this error to `get_reordering`.
* `update_reordering`: trace back this error to `get_reordering`. updating an existing element still calls `lru_add()` which creates problems. 
* `evict_on_reset_old_val`: Whether or not we count this as a bug is ambiguous. This finds that the cache uneccesarily evicts elements when updating an entry with a value that would overload the cache if added under a new key. The spec doesn't say whether or not we should call this an error, but if we do not want that behavior then this is an error.
* `get_reordering`: `cache_get()` calls the `lru_add()` from `lru.c` which does not update the lru element properly if we are getting the lru element.
* `var_len_evictions`: trace back this error to `get_reordering`.

#### Aledger
A main source of problems with this cache was that many cases were handled with exits that would crash the test instead doing nothing or returning NULL for example. Also did not follow the API for `cache_set()` by not allowing the user to pass their own hash function.
* `crash_on_memoverload`: asserts and exits when trying to add something greater than maxmem (it says crash in the table but we count this as a fail).
* `custom_hash_is_called`: Cache_set doesn't follow the API since it doesn't allow to user to pass their own hash function to the cache.
* `add_single_item_over_memmax`: we can trace back this error to `crash_on_memoverload` since this cache will crash on any inputs that exceed maxmem, we know this test will crash.
* `add_same_starting_char`: ???? SHOULD BE A PASS ?????
* `add_over_memmax_eviction`: trace back this error to `crash_on_memoverload`
* `add_resize_buckets_or_maxmem`: trace back this error to `crash_on_memoverload`
* `update_reordering`: we get into an infinite while-loop starting on line 136 of `cache.h`
* `evict_on_reset_old_val`: Whether or not we count this as a bug is ambiguous. This finds that the cache uneccesarily evicts elements when updating an entry with a value that would overload the cache if added under a new key. The spec doesn't say whether or not we should call this an error, but if we do not want that behavior then this is an error.
* `evict_on_failed_reset_old_val`: same infinite while-loop starting on line 136 of `cache.h`


#### Apan
`cache_get()` doesn't follow the API in this cache, so buffer size is never properly returned.
* `get_size_test`: `cache_get()` doesn't follow the API.
* `get_val_after_reassign_test`: Whether or not we count this as a bug is ambiguous. If we expect the cache to copy out vals when `cache_get()` is called, then this is a bug. If we expect `cache_get()` to return a pointer, then this is not a bug. (This cache fails our test as it is now since it returns a pointer but we expect the value to be copied out.)
* `basic_lru_test`: trace back this error to `get_reordering`
* `lru_delete_test`: trace back this error to `get_reordering`
* `evict_on_reset_old_val`: Whether or not we count this as a bug is ambiguous. This finds that the cache uneccesarily evicts elements when updating an entry with a value that would overload the cache if added under a new key. The spec doesn't say whether or not we should call this an error, but if we do not want that behavior then this is an error.
* `get_reordering`: `cache_get()` doesn't update the LRU
* `var_len_evictions`: trace back this error to `get_reordering`

#### Bblack
* `get_val_after_reassign_test`: Whether or not we count this as a bug is ambiguous. If we expect the cache to copy out vals when `cache_get()` is called, then this is a bug. If we expect `cache_get()` to return a pointer, then this is not a bug. (This cache fails our test as it is now since it returns a pointer but we expect the value to be copied out.)
* `evict_on_failed_reset_old_val`: Whether or not we count this as a bug is ambiguous. If we expect the cache to evict the element even though it cannot be rewritten, then this is not a bug. If we do expect the cache to evict the element anyway, then this is a bug. (Currently we call this a bug)

#### Jcosel
One initial bug can't be tested but is actually revealed to us by the cache's print statements: if you initialize it with a maxmem less than 64, it resizes automatically to 64. This is hard to test because of another bug that causes maxmem to double itself when exceeded.
* `cache_space_preserved`: trace back this error to the maxmem resize.
* `add_single_item_over_memmax`: trace back this error to the maxmem resize.
* `add_over_memmax_eviction`: we get a false positive (incorrect pass) here because of this maxmem resize bug!
* `add_resize_buckets_or_maxmem`: trace back this error to the maxmem resize.
* `get_null_empty`: crash ????? really weird because this passes when the cache is empty.?????
* `evictions_occur`: ????? THIS TEST IS WEIRD ???????
* `basic_lru_test`: trace back this error to initial cache resize
* `lru_delete_test`: trace back this error to initial cache resize
* `update_reordering`: trace back this error to initial cache resize
* `evict_on_failed_reset_old_val`: Whether or not we count this as a bug is ambiguous. If we expect the cache to evict the element even though it cannot be rewritten, then this is not a bug. If we do expect the cache to evict the element anyway, then this is a bug. (Currently we call this a bug)
* `get_reordering`: trace back this error to initial cache resize
* `maxmem_not_excceeded`: trace back this error to the maxmem resize
* `elements_not_evicted_early`: trace back this error to the maxmem resize
* `var_len_evictions`: trace back this error to the maxmem resize

#### Jhepworth
This cache compiles after we patch the section mentioned in the moodle forum, but continues to crash on mac. You need to be on polytopia to run tests on this cache.
* `get_size_test`: Fail
* `get_val_test`: Crashed
* `space_test`: Fail
* `custom_hash_is_called`: Fail
* `large_val_copied_correctly`: Fail
* `add_same_starting_char`: Fail
* `add_over_memmax_eviction`: Fail
* `get_val_after_reassign_test`: Crashes
* `get_with_null_term_strs_test`: Crashes
* `delete_affect_get_out`:
* `evictions_occur`: ????? THIS TEST IS WEIRD ???????
* `update_reordering`:
* `evict_on_reset_old_val`:
* `evict_on_failed_reset_old_val`:

#### Zzhong
* `custom_hash_is_called`: ???? SHOULD BE A PASS ?????
* `cache_space_preserved`: Line 46 in cache.c is causing a segmentation fault. Why it does this is a mystery because both the values of cache_space_used(cache) and cache->maxmem can be accessed before the if statement, but apparently not inside of it.
* `add_single_item_over_memmax`: doesn't check whether or not the new element will exceed maxmem, so we actually end up adding it to the cache.
* `add_same_starting_char`: this cache doesn't treat keys as strings, so keys with the same starting char collide will collide.
* `add_over_memmax_eviction`: we can trace this error back to `add_single_item_over_memmax` since we're apparently able to exceed maxmem, so we expect this cache to fail this test
* `add_resize_buckets_or_maxmem`: trace back to `add_single_item_over_memmax`
* `get_size_after_reassign_test`: in `cache.c` the if-statement in line 40 for the update case doesn't update the size of the item in the hash table, only rewrites the value.
* `delete_not_in`: ???? should be a pass????
* `evictions_occur`: ????? THIS TEST IS WEIRD ???????
* `update_reordering`: trace back to `add_single_item_over_memmax`
* `evict_on_failed_reset_old_val`: Whether or not we count this as a bug is ambiguous. If we expect the cache to evict the element even though it cannot be rewritten, then this is not a bug. If we do expect the cache to evict the element anyway, then this is a bug. (Currently we call this a bug)
* `get_reordering`: trace back to `add_single_item_over_memmax`
* `maxmem_not_excceeded`: trace back to `add_single_item_over_memmax`
* `elements_not_evicted_early`: trace back to `add_single_item_over_memmax`


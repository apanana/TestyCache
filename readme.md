### Files:

Filename | Description
-- | --
Makefile | Standard makefile for make to build the tests
run_test.py | Run system for the tests (described in Run System section)


### Changes to cache source code to get compiles to work

* Included stdint.h in apan/lru.h, akosik/lru.h
* Changed function name from an undefined function to "make_item_array" in sysHW3/lru_replacement.h (line 137)
* Changed key_t and val_t to key_type and val_type in all of akosik's and jhepworth's code

### Build system

To aid in our testing, we built a makefile that compiles all the tests against all the caches simultaneously. In addition to the direct changes to the cache code that are detailed above, we also made new functions that acted as wrappers for create_cache and cache_get that allowed us to run tests on all of the cache code without changing their code or the tests.

### Run system

In order to make testing easier and faster, we made a python script that runs the test in

An even more useful help to testing is the python script that runs tests on caches automatically.

The idea is this: Each test is called by a unique command line option. The python script runs through the specified executable(s) and the specified test(s) and runs them and produces a summary of the results. This  allows us to see which tests are crashing/failing on which caches and should hopefully allow us to create many more reliable tests.

### Test ideas

* Test tiny strings with a single null terminated charachter followed by nonsense and see if it is consistent.
* Test large strings with identical first bytes and see if they map to the same bucket
* Many more, see test.h for a larger list.



## Radom Issues

### Compiler bug???

We get different results on a macbook for "Apple LLVM version 7.0.2 (clang-700.1.81)" when compiling with -O2 and with -O0 on one of our tests. I believe this is Clang 3.6. Specifically, "get_size_test" returned true when running apan's test on O2

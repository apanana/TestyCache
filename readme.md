### Files:

| Filename | Description |
| --- | --- |
| Makefile | Standard makefile for make to build the tests |
| run_test.py | Run system for the tests (described in Run System section) |


### Changes to cache source code to get compiles to work

* Included stdint.h in apan/lru.h, akosik/lru.h
* Changed function name from an undefined function to "make_item_array" in bblack/lru_replacement.h (line 137)
* Changed key_t and val_t to key_type and val_type in all of akosik's and jhepworth's code

### Build system

The makefile compiles all the tests against all the caches simultaneously. In addition to the direct changes to the submitted cache code as detailed above, we also made new functions that acted as wrappers for create_cache and cache_get that allowed us to run tests on all of the APIs without changing them directly. In order to do this, it uses command line macro definitions and ifdefs. This is done in cachewrapper.h and cachewrapper.c.

In order to deal with the compiler bug detailed below, we are compiling with O0.

### Run system

In order to make testing easier and faster, we made a python script that runs the tests on the caches and prints out the results. This is in "run_test.py".

In order to do this, our main function only runs a single test each time it is run, specified by a command line integer input. A giant switch statement then chooses the test.

If the test passes, it returns 0. If it fails, it returns a certain number. If it crashes, it returns an arbitrary number (hopefully different than the failure error). The python file then checks this return value and produces nicely formatted output about the result. The python file also terminates the process if it has been running for too long, and notes that. Too long is 5.0 seconds, which seems like a completely reasonable time for all of our tests to finish. We found this necessary because one of the caches gets into an infinite loop on some of our tests.

More complete documentation of the details is in the "run_test.py" file.

## Random Issues

### Compiler bug???

We get inconsistent results on a macbook using the clang compiler "Apple LLVM version 7.0.2 (clang-700.1.81)". I believe this is Clang 3.6. Specifically, "get_size_test" returned true when running apan's cache on O2 and false when compiling with O0.

There seem to be other bugs and inconsistencies between -O2 and -O0 when compiling with clang as well.

Using gcc 4.8, I got that get_size_after_reassign_test passes on O0 and fails on O2 on apan's cache.

To reproduce, change the makefile to compile for the specific compiler, and add O2 and see the differences between that and O0.

### Python bug???

On the polytopia machines, I got inconsistent "UnicodeDecodeError" errors when decoding the standard output from the process. I looked at the output, and it looked like the Popen.communicate() method was returning output that the process never actually printed. On windows and OSX, this method works fine, and I believe it is correct usage of the module.

To reproduce this, uncomment the print statement in TestRes.__init__ in run_test.py and run the python file several times (sometimes it works fine) until you start seeing nonsense printed out.

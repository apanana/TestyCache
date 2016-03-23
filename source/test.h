#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#define failed_code 0x92
typedef bool (*test_fn_ty)();



//Undefined tests? May or may not be testable
bool large_val_copied_correctly();
bool add_single_item_over_memmax();
//bool add_key_int_test(); redundant
// bool add_key_str_test();
// bool add_val_int_test();
// bool add_val_str_test();
//bool add_val_bool_test(); redundant
// bool add_val_array_test();
// bool add_existing_key_test();

// bool add_many_items_test();

//bool add_resize_test(); impossible

// bool add_evict_test();///what is this?

// bool add_mem_overload_test();



// ? smth for different key types

bool get_size_after_reassign_test(); // naive - already done
bool get_val_after_reassign_test(); // raises some interesting errors
bool get_with_null_term_strs_test();

// bool get_val_int_test();
// bool get_val_str_test();
//bool get_val_bool_test(); redundant
// bool get_val_array_test();
// bool get_size_x_test();//what is this?
// bool get_rewritten_val_test();
// bool get_nonelement_val_test();
//bool get_nonelement_size_test();// not defined in API

// ? deleting on different key types
//bool delete_int_test(); redundant
// bool delete_str_test();
//bool delete_bool_test(); redundant
//bool delete_array_test(); redundant
bool delete_not_in();
// bool delete_nonelement_test();
//bool delete_post_resize_test(); impossible?
// bool delete_empty_reuse_test(); //can the cache be reused after being emptied?



// bool space_str_test(); //(others are actually redundant here) //for int/str/bool/array
// bool space_evict_test();
//bool space_resize_test(); impossible
// bool space_delete_test();
// bool space_clear_test();//what is this?



//more advanced tests to get crashes out of the more secure caches

// bool random_set_get_delete();//my own test

//time dependent tests (need a timing framework)

// bool reasonable_access_time_few_items();
// bool reasonable_access_time_many_items();
// bool long_str_collision_test();
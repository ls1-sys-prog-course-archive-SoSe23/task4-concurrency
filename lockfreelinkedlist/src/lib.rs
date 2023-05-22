pub struct List {}

/// insert val into the list and return 0 if successful
/// return 1 otherwise, e.g., could not allocate memory
#[no_mangle]
pub extern "C" fn insert_val(list: *mut List, val: libc::c_long) -> libc::c_int {
    return 1;
}

/// remove val from the list, if it exist and return 0 if successful
/// return 1 if item is not found
#[no_mangle]
pub extern "C" fn remove_val(list: *mut List, val: libc::c_long) -> libc::c_int {
    return 1;
}

/// check if val exists in list, return 0 if found, return 1 otherwise
#[no_mangle]
pub extern "C" fn lookup_val(list: *mut List, val: libc::c_long) -> libc::c_int {
    return 1;
}

/// allocate a list
#[no_mangle]
pub extern "C" fn alloc_list() -> *mut List {
    return std::ptr::null_mut();
}

/// free the list
#[no_mangle]
pub extern "C" fn free_list(list: *mut List) {}

/// print all elements in the hashmap as follows:
/// - val1 - val2 - val3 ...
#[no_mangle]
pub extern "C" fn print_list(list: *mut List) {}

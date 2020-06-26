# plf_indiesort
A sort wrapper enabling both use of random-access (eg. std::sort) sorting on non-random access containers, and increased performance for the sorting of large types.

Indiesort should be used when:

    The temporary memory cost mentioned is non-problematic,
    The container or iterators are not random_access and therefore std::sort cannot be used, and/or
    The element type is large or non-trivially-movable/copyable.


It is, on average across all numbers of sorted elements:

    +130% faster than std::sort when used on vectors or arrays of large structs (~480 bytes)
    +28% faster than std::list's internal sort, on types smaller than a large struct.

std::list's internal sort is faster for large structs (as it only writes previous and next pointers) and std::sort is faster on vectors and arrays for smaller types.

# plf_indiesort
A sort wrapper enabling use of random-access (eg. std::sort) sorting on non-random access containers, and increased performance for the sorting of large types in random-access containers.
plf::indiesort has a temporary memory cost of (N * (sizeof(pointer) + sizeof(size_t))) for sorting non-random-access iterators/containers,<br>
and a (N * (sizeof(U))) cost for random-access iterators/containers, where U = the smallest unsigned integer able to store N + 1 ie. if N is &lt; 255, U can be unsigned char.

Indiesort should be used when:

* The temporary memory cost mentioned is non-problematic,
* The container or iterators are not random_access and therefore std::sort cannot be used, and/or
* The element type is large or non-trivially-movable/copyable.


It is, on average across all numbers of sorted elements:

* +146% faster than std::sort when used on vectors or arrays of large structs (496 bytes). Crossover point for increased performance over std::sort is any type larger than 152 bytes.
* +28% faster than std::list's internal sort, on types smaller than 272 bytes.

std::list's internal sort is faster for types larger than 272 bytes (as it only writes previous and next pointers) and std::sort is faster on vectors and arrays for types smaller than 152 bytes.
C++98/03/11/14/etc-compatible.

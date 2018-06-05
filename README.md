# C++ Bit Pool Implementation

## Assignment

Dynamic allocation of game objects can be costly. Instead of allocating objects dynamically
during gameplay it can be more effective to retrieve a free object out of a pre-allocated
contiguous array of cache-friendly items. This is typically called "pooling."

An object pool is a common way to reduce dynamic allocation during gameplay. Included with
this document is a templated interface for a class named BitPool, a form of an object pool that
tracks pool object usage state via bit flipping.

Please do the following:

1. Without using the STL implement the BitPool class defined in `bitpool.h` and ensure it
passes the test cases in `bitpool_test.cpp.` You must use a single bit per object to record
pool object state as either ‘in use’ or ‘free’. Feel free to add any private member
variables or functions you need but keep the public interface intact without adding or
removing any functions.
2. Provide a brief description of your implementation of BitPool.
3. Given this interface, what would you change about it? Do you see any problems with
how it could be used by a programmer in the future? Please be as descriptive as
possible about the current problems and the solutions you would employ to address
them.




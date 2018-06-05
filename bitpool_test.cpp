#include "bitpool.h"
#include <cassert>
#include <vector>
#include <algorithm>

class FOO 
{
public:
    FOO() : brainPower_(100),   overdriveAcceleration_(0) {}
    ~FOO() {}

private:
    int brainPower_;
    int overdriveAcceleration_;
};

int main(int argc, char **argv) 
{
    BitPool<FOO> bp5 = BitPool<FOO>(5);

    size_t num_obj = bp5.GetMaxObjects();          // [num_obj] should be [5]
    assert(num_obj == 5);

    size_t num_used = bp5.GetObjectsInUse();       // [num_used] should be [0]
    assert(num_used == 0);

    FOO *pOne = bp5.GetObject();                   // [pOne] should be a valid pointer
    assert(pOne != nullptr);

    num_used = bp5.GetObjectsInUse();              // [num_used] should be [1]
    assert(num_used == 1);

    FOO *pTwo = bp5.GetObject();                   // [pTwo] should be a valid pointer
    assert(pTwo != nullptr);

    assert(pOne != pTwo);                          // [pOne] and [pTwo] should be different pointers

    num_used = bp5.GetObjectsInUse();              // [num_used] should be [2]
    assert(num_used == 2);

    bool success = bp5.ReturnObject(pTwo);         // [success] should be [true] - returning an 'in use' object
    assert(success == true);

    num_used = bp5.GetObjectsInUse();              // [num_used] should be [1]
    assert(num_used == 1);

    success = bp5.ReturnObject(pTwo);              // [success] should be [false] - returning a 'free' object
    assert(success == false);

    FOO *pFive = bp5.GetObjectAt(5);               // pFive should be [nullptr], a zero-indexed object at index [5] is out of bounds
    assert(pFive == nullptr);

    FOO *pFour = bp5.GetObjectAt(4);               // pFour should be valid, even though BitPool might have it marked as 'free'
    assert(pFour != nullptr);

    FOO *pOutsidePool = new FOO();
    success = bp5.ReturnObject(pOutsidePool);      // [success] should be [false] - Object isn't part of pool
    assert(success == false);

    BitPool<FOO> bp1024 = BitPool<FOO>(1024);
    for(unsigned int count = 0; count < 1024; ++count)
    {
        // Pretending the bp1024 objects are being saturated by another system
        FOO *pTempObj = bp1024.GetObject();
    }
    
    num_obj = bp1024.GetMaxObjects();              // [num_obj] should be 1024
    assert(num_obj == 1024);

    num_used = bp1024.GetObjectsInUse();           // [num_used] should be 1024
    assert(num_used == 1024);

    FOO *pAnotherObj = bp1024.GetObject();         // pAnotherObj should be [nullptr], pool has no additional 'free' objects
    assert(pAnotherObj == nullptr);

    BitPool<FOO> bp128 = BitPool<FOO>(128);
    
    FOO* pSixtyFive = nullptr;
    for (unsigned int count = 0; count < 90; ++count)
    {
        if (count == 65)
        {
            pSixtyFive = bp128.GetObject();
        }
        else
        {
            FOO *pTempObj = bp128.GetObject();
        }
    }

    success = bp128.ReturnObject(pSixtyFive);      // [success] should be [true] - pSixtyFive returned
    assert(success == true);

    num_used = bp128.GetObjectsInUse();            // [num_used] should be 89
    assert(num_used == 89);

    // grab the remainder of the objects from the pool
    for (unsigned int count = 0; count < 39; count++)
    {
        FOO *pTempObj = bp128.GetObject();         // [pTempObject] should always be valid
        assert(pTempObj != nullptr);
    }

    num_used = bp128.GetObjectsInUse();            // [num_used] should be 128
    assert(num_used == 128);

    // free half of bp128
    for (unsigned int count = 0; count < 128; count += 2)
    {
        FOO* pTemp = bp128.GetObjectAt(count);      // [pTemp] should always be valid
        assert(pTemp != nullptr);

        success = bp128.ReturnObject(pTemp);        // [success] should be [true] - all of these objects can be returned to the pool
        assert(success == true);
    }

    num_used = bp128.GetObjectsInUse();            // [num_used] should be 64
    assert(num_used == 64);

    // try to re-grab the free half of bp128
    for (unsigned int count = 0; count < 64; count++)
    {
        FOO* pTemp = bp128.GetObject();             // [pTemp] should always be valid
        assert(pTemp != nullptr);
    }

    num_used = bp128.GetObjectsInUse();             // [num_used] should be 128
    assert(num_used == 128);

    // free them all
    for (unsigned int count = 0; count < 128; count++)
    {
        FOO* pTemp = bp128.GetObjectAt(count);      // [pTemp] should always be valid
        assert(pTemp != nullptr);

        success = bp128.ReturnObject(pTemp);        // [success] should be [true] - all of these objects can be returned to the pool
        assert(success == true);
    }

    // grab 128 objects and ensure the pointer to each is unique
    std::vector<FOO*> vectorOfFooObjects;
    for (unsigned int count = 0; count < 128; count++)
    {
        vectorOfFooObjects.push_back(bp128.GetObject());
    }

    // strip duplicate pointers
    std::sort(vectorOfFooObjects.begin(), vectorOfFooObjects.end());
    auto lastUnique = std::unique(vectorOfFooObjects.begin(), vectorOfFooObjects.end());
    vectorOfFooObjects.erase(lastUnique, vectorOfFooObjects.end());

    assert(vectorOfFooObjects.size() == 128);       // should be 128 unique pointers returned from the pool

    return 0;
}
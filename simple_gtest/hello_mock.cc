#include <gtest/gtest.h>
#include <gmock/gmock.h>

//==========================================================================
// gmock

// Step 1：定义Allocator接口
class Allocator {
public:
    virtual ~Allocator() = default;
    virtual void* Allocate(size_t size) = 0;
    virtual void Free(void* ptr) = 0;
};

// 上面的buffer没有依赖别人, 不适合用gmock, 下面Buffer2可以, 即Buffer2是要被测试的对象
class Buffer2 {
public:
    Buffer2(Allocator* alloc, int size)
        : allocator(alloc)
    {
        data = static_cast<int*>(allocator->Allocate(size * sizeof(int)));
        capacity = size;
        used = 0;
    }

    ~Buffer2() {
        allocator->Free(data);
    }

    void Push(int v) {
        data[used++] = v;
    }

    int Size() const {
        return used;
    }

private:
    Allocator* allocator;
    int* data;
    int capacity;
    int used;
};

// Step 2：写 Mock 类, 只 mock virtual 方法
class MockAllocator : public Allocator {
public:
    MOCK_METHOD(void*, Allocate, (size_t size), (override));
    MOCK_METHOD(void, Free, (void* ptr), (override));
};

// Step 3：在 test 里用 EXPECT_CALL
// 这里你验证的不是结果，而是“交互是否符合设计”
TEST(HelloGmock, AllocateAndFree) {
    MockAllocator alloc;

    // 这里不能用任意的fake mem, 因为Push的时候会写.
    // void* mem = reinterpret_cast<void*>(0x1234);
    std::vector<int> storage(10);  // vector 管理内存
    int* mem = storage.data();

    // 设定约定/contract:
    // alloc 对象的 Allocate(40) 会被call一次, 返回mem
    EXPECT_CALL(alloc, Allocate(10 * sizeof(int)))
        .Times(1)
        // 当alloc 的 Allocate(...) 第一次被调用时，gMock 会拦截这个调用，
        // 并直接返回 mem（也就是 0x1234），而不是执行任何真实代码
        .WillOnce(::testing::Return(mem));

    EXPECT_CALL(alloc, Free(mem))
        .Times(1);

    // 测试开始
    {
        // alloc 的 Allocate(...) 第一次被调用, 在Buffer2的构造
        Buffer2 buf(&alloc, 10);
        buf.Push(1);
        buf.Push(2);
        EXPECT_EQ(buf.Size(), 2);
    } // 析构时验证 Free
}

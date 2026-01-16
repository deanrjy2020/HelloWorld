#include <gtest/gtest.h>

using namespace std;

/*
cmake -S . -B build
cmake --build build && ./build/hello_test

*/

//==========================================================================
// basic

TEST(HelloTest, BasicAssertions)
{
  int a = 1, b = 1;
  EXPECT_EQ(a, b);
  b = 2;
  EXPECT_NE(a, b);
  EXPECT_LT(a, b);
  bool cond = a < b;
  EXPECT_TRUE(cond);
  cond = false;
  EXPECT_FALSE(cond);

  EXPECT_STREQ("hello", "hello");
  EXPECT_STRNE("hello", "world");
  
  EXPECT_EQ(7 * 6, 42);
}

//==========================================================================
// test fixture

class Buffer
{
public:
  Buffer(int size)
  {
    data.reserve(size);
  }
  void Push(int elem)
  {
    data.push_back(elem);
  }
  int Size()
  {
    return data.size();
  }

private:
  vector<int> data;
};

class BufferTest : public ::testing::Test
{
protected:
  void SetUp() override
  {
    buffer = new Buffer(1024);
  }

  void TearDown() override
  {
    delete buffer;
  }

  Buffer *buffer;
};

// 用TEST_F + SetUp/TearDown 类
TEST_F(BufferTest, InitiallyEmpty)
{
  // 里面可以直接用buffer 变量.
  EXPECT_EQ(buffer->Size(), 0);
}

TEST_F(BufferTest, PushIncreasesSize)
{
  buffer->Push(1);
  EXPECT_EQ(buffer->Size(), 1);
}



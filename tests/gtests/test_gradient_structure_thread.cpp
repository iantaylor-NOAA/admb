#include <gtest/gtest.h>
#include <fvar.hpp>
#include <gradient_structure.h>

extern "C"
{
  void test_ad_exit(const int exit_code);
}

class test_gradient_structure_thread: public ::testing::Test {};

TEST_F(test_gradient_structure_thread, instance)
{
  ASSERT_TRUE(gradient_structure::get() == nullptr);
}
TEST_F(test_gradient_structure_thread, clean_empty)
{
  ASSERT_TRUE(gradient_structure::gradients == nullptr);
  ASSERT_TRUE(gradient_structure::gradients_size == 0);

  gradient_structure::clean();

  ASSERT_TRUE(gradient_structure::gradients == nullptr);
  ASSERT_TRUE(gradient_structure::gradients_size == 0);
}
TEST_F(test_gradient_structure_thread, clean0)
{
  ASSERT_TRUE(gradient_structure::gradients == nullptr);
  ASSERT_TRUE(gradient_structure::gradients_size == 0);

  gradient_structure gs(1000, 0);

  gradient_structure::create(0);

  ASSERT_TRUE(gradient_structure::gradients != nullptr);
  ASSERT_TRUE(gradient_structure::gradients[0] == &gs);
  ASSERT_TRUE(gradient_structure::gradients_size == 0);

  gradient_structure::clean();

  ASSERT_TRUE(gradient_structure::gradients == nullptr);
  ASSERT_TRUE(gradient_structure::gradients_size == 0);
}
TEST_F(test_gradient_structure_thread, clean1)
{
  ASSERT_TRUE(gradient_structure::gradients == nullptr);
  ASSERT_TRUE(gradient_structure::gradients_size == 0);

  gradient_structure gs;

  gradient_structure::create(1);

  ASSERT_TRUE(gradient_structure::gradients != nullptr);
  ASSERT_TRUE(gradient_structure::gradients[0] == &gs);
  ASSERT_TRUE(gradient_structure::gradients[1] != &gs);
  ASSERT_TRUE(gradient_structure::gradients[1]->x == 1);
  ASSERT_TRUE(gradient_structure::gradients_size == 1);

  gradient_structure::clean();

  ASSERT_TRUE(gradient_structure::gradients == nullptr);
  ASSERT_TRUE(gradient_structure::gradients_size == 0);
}
TEST_F(test_gradient_structure_thread, clean2)
{
  ASSERT_TRUE(gradient_structure::gradients == nullptr);
  ASSERT_TRUE(gradient_structure::gradients_size == 0);

  gradient_structure gs;

  gradient_structure::create(2);

  ASSERT_TRUE(gradient_structure::gradients != nullptr);
  ASSERT_TRUE(gradient_structure::gradients[0] == &gs);
  ASSERT_TRUE(gradient_structure::gradients[1] != &gs);
  ASSERT_TRUE(gradient_structure::gradients[2] != &gs);
  ASSERT_TRUE(gradient_structure::gradients[1] != gradient_structure::gradients[2]);
  ASSERT_TRUE(gradient_structure::gradients[1]->x == 1);
  ASSERT_TRUE(gradient_structure::gradients[2]->x == 2);
  ASSERT_TRUE(gradient_structure::gradients_size == 2);

  gradient_structure::clean();

  ASSERT_TRUE(gradient_structure::gradients == nullptr);
  ASSERT_TRUE(gradient_structure::gradients_size == 0);
}
TEST_F(test_gradient_structure_thread, get)
{
  gradient_structure gs;
  ASSERT_TRUE(gradient_structure::get() == &gs);
}
TEST_F(test_gradient_structure_thread, nested)
{
  gradient_structure top;
  ASSERT_TRUE(strcmp(gradient_structure::get()->fp->cmpdif_file_name, "cmpdiff.tmp") == 0);
  ASSERT_TRUE(gradient_structure::get() == &top);
  {
    gradient_structure nested(10000L, 10);
    ASSERT_TRUE(gradient_structure::get() == &nested);
    ASSERT_TRUE(strcmp(gradient_structure::get()->fp->cmpdif_file_name, "cmpdiff10.tmp") == 0);
  }
  ASSERT_TRUE(gradient_structure::get() == nullptr);
}

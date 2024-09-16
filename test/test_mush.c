#include "unity.h"
#include "mush.h"

void setUp(void) {}
void tearDown(void) {}

// Add your actual test functions here
void test_example(void) {
    TEST_ASSERT_EQUAL_INT(1, 1);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_example);
    // Add more RUN_TEST calls for your actual tests
    return UNITY_END();
}
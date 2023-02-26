#include "container_test.hpp"
#include <iostream>

// This test is to check the functionality
// Each test will compare the result with the
// standart container implementation
int main(void) {
    std::cout << "Vector time test -------------------------------------" << std::endl;
    vector_test();
    std::cout << "Stack time test --------------------------------------" << std::endl;
    stack_test();
    std::cout << "Map time test ----------------------------------------" << std::endl;
    map_test();
    std::cout << "Set time test ----------------------------------------" << std::endl;
    set_test();
    return (0);
}
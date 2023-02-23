
#include <iostream>

#include <vector>
#include "vector.hpp"

#include <map>
#include <map.hpp>

#include <set>
#include "set.hpp"

#include <stack>
#include "stack.hpp"

#include <string>
#include "utility.hpp"

#include "time.hpp"

void    print_results (double std_time, double ft_time) {
    std::cout << "Std_time: " << std_time << std::endl;
    std::cout << "Ft_time: " << ft_time << std::endl;
    std::cout << "Ratio: ";
    if (std_time == 0)
        std::cout << "Std_time is zero, ratio cannot be taken";
    else 
        std::cout << ft_time / std_time << " times in relation to the std implmentation";
    std::cout << std::endl << std::endl;
}

int main(void) {
    double std_time = 0, ft_time = 0;

    std::cout << "---------- Vector time op ------------------------" << std::endl;
    std_time = measure_vector_time<std::vector<int> >(0);
    ft_time = measure_vector_time<ft::vector<int> >(0);
    print_results(std_time, ft_time);
    std::cout << "--------------------------------------------------" << std::endl << std::endl;

    std::cout << "---------- Stack time op -------------------------" << std::endl;
    std_time = measure_stack_time<std::stack<int> >(0);
    ft_time = measure_stack_time<ft::stack<int> >(0);
    print_results(std_time, ft_time);
    std::cout << "--------------------------------------------------" << std::endl << std::endl;

    std::cout << "---------- Map time op ---------------------------" << std::endl;
    ft_time = measure_map_time<ft::map<int, int>, ft::pair<int, int> >(-1);
    print_results(std_time, ft_time);
    std::cout << "--------------------------------------------------" << std::endl << std::endl;


    /*
    std::cout << "---------- Set time op ---------------------------" << std::endl;
    //print_results(std_time, ft_time);
    std::cout << "--------------------------------------------------" << std::endl << std::endl;
    */
    return (0);
}
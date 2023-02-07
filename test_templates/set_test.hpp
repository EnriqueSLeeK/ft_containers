
#ifndef MAP_TEST_HPP
# define MAP_TEST_HPP

#include "set.hpp"
#include "test.hpp"
#include "utility.hpp"

#include <set>
#include <string>
#include <iostream>
#include <stdexcept>

// Test function #####################################################################################
template <typename std_tree, typename ft_tree>
bool check_equality (std_tree std_set, ft_tree ft_set) {

    if (std_set.size() != ft_set.size())
        return (false);

    typename std_tree::iterator begin = std_set.begin();
    typename std_tree::iterator end = std_set.end();

    typename ft_tree::iterator fbegin = ft_set.begin();
    typename ft_tree::iterator fend = ft_set.end();

    typename std_tree::reverse_iterator rbegin = std_set.rbegin();
    typename std_tree::reverse_iterator rend = std_set.rend();

    typename ft_tree::reverse_iterator rfbegin = ft_set.rbegin();
    typename ft_tree::reverse_iterator rfend = ft_set.rend();

    return (check_interval_normal(begin, end, fbegin, fend) &&
                check_interval_normal(rbegin, rend, rfbegin, rfend));
}

template <typename std_set_type, typename ft_set_type,
          typename data_type >
void init_set_test (data_type *data) {

    std::cout << "Copy constructor and contructor test" << std::endl;
    std::cout << "Every test will call the copy constructor" <<std::endl;
    std::cout << "Every test will use the normal iterator and the reverse iterator" <<std::endl;


    std::cout << "Default" << std::endl;
    std_set_type std_set;
    ft_set_type ft_set;
    std::cout << (check_equality(std_set, ft_set) ? "OK" : "KO") << std::endl;

    std::cout << "Fill constructor" << std::endl;
    std_set_type s_set_2(data, data + 6);
    ft_set_type f_set_2(data, data + 6);
    std::cout << (check_equality(s_set_2, f_set_2) ? "OK" : "KO") << std::endl;

    std_set_type s_set_3(data + 1, data + 4);
    ft_set_type f_set_3(data + 1, data + 4);
    std::cout << (check_equality(s_set_3, f_set_3) ? "OK" : "KO") << std::endl;
}

template <typename std_set_type, typename ft_set_type,
            typename data_type>
void capacity_test(data_type *data) {

    std::cout << "Size method test" << std::endl;
    std_set_type set(data, data + 6);
    ft_set_type fset(data, data + 6);
    if (set.size() == fset.size())
        std::cout << "OK";
    else
        std::cout << "KO";
    std::cout << std::endl;

    std_set_type set2(data, data + 6);
    ft_set_type fset2(data, data + 6);
    if (set2.size() == fset2.size())
        std::cout << "OK";
    else
        std::cout << "KO";
    std::cout << std::endl;
    
    std::cout << "Empty method test" << std::endl;
    std_set_type empty_set;
    ft_set_type empty_fset;
    if (empty_set.empty() == empty_fset.empty())
        std::cout << "OK";
    else
        std::cout << "KO";
    std::cout << std::endl;

}

template <typename std_set_type, typename ft_set_type>
static void wipe_eveything(std_set_type &std_set, ft_set_type &ft_set) {
    std_set.clear();
    ft_set.clear();
}

template <typename std_set_type, typename ft_set_type,
            typename data_type >
void insert_delete_test(data_type *data) {
    std_set_type set;
    ft_set_type fset;

    std::cout << "Random insertion" << std::endl;
    set.insert(data[5]);
    set.insert(data[4]);
    set.insert(data[1]);
    set.insert(data[2]);
    set.insert(data[0]);
    set.insert(data[0]);
    set.insert(data[0]);
    fset.insert(data[5]);
    fset.insert(data[4]);
    fset.insert(data[1]);
    fset.insert(data[2]);
    fset.insert(data[0]);
    fset.insert(data[0]);
    fset.insert(data[0]);
    std::cout << (check_equality(set, fset) ? "OK" : "KO") << std::endl;

    std::cout << "Clear everything" << std::endl;
    wipe_eveything(set, fset);
    std::cout << (check_equality(set, fset) ? "OK" : "KO") << std::endl;

    std::cout << "Insert and individual deletion" << std::endl;

    fset.insert(data[5]);
    fset.insert(data[1]);
    fset.insert(data[3]);
    fset.insert(data[2]);
    fset.insert(data[4]);
    fset.insert(data[0]);

    fset.erase(++fset.begin());
    fset.erase(++++fset.begin());
    fset.erase(--fset.end());

    set.insert(data[0]);
    set.insert(data[2]);
    set.insert(data[4]);
    std::cout << (check_equality(set, fset) ? "OK" : "KO") << std::endl;
    wipe_eveything(set, fset);

    std::cout << "Bulk deletion and insertion" << std::endl;
    fset.insert(data + 1, data + 5);
    set.insert(data + 1, data + 5);
    
    fset.erase(fset.begin(), fset.end());
    set.erase(set.begin(), set.end());
    std::cout << (check_equality(set, fset) ? "OK" : "KO") << std::endl;
    wipe_eveything(set, fset);
}


template <typename std_set_type, typename ft_set_type,
            typename data_type >
void swap_test (data_type *data) {
    std_set_type set1(data + 1, data + 3);
    std_set_type set2(data, data + 5);

    ft_set_type fset1(data + 1, data + 3);
    ft_set_type fset2(data, data + 5);

    std::cout << "First swap operation => Swap 1 with 2" << std::endl;
    set1.swap(set2);
    fset1.swap(fset2);
    std::cout << (check_equality(set1, fset1) ? "OK" : "KO") << std::endl;

    std::cout << "Second swap operation => Swap 1 with 2 aka will restore the original content" << std::endl;
    swap(set1, set2);
    swap(fset1, fset2);
    std::cout << (check_equality(set1, fset1) ? "OK" : "KO") << std::endl;
}

template <typename std_set_type, typename ft_set_type,
            typename data_type >
void look_up_test (data_type *data, data_type valid, data_type invalid) {

    std_set_type set(data, data + 5);
    ft_set_type fset(data, data + 5);
    
    std::cout << "Count method test" << std::endl;
    std::cout << (set.count(valid) == fset.count(valid) ? "OK" : "KO") << std::endl; // Test a valid case
    std::cout << (set.count(invalid) == fset.count(invalid) ? "OK" : "KO") << std::endl; // Test invalid case
    
    std::cout << "Find method test" << std::endl;
    typename std_set_type::iterator iter = set.find(valid);
    typename ft_set_type::iterator fiter = fset.find(valid);
    std::cout << ((*iter) == (*fiter) ? "OK" : "KO") << std::endl; // Test a valid case

    iter = set.find(invalid);
    fiter = fset.find(invalid);
    std::cout << (iter == set.end() && fiter == fset.end() ? "OK" : "KO") << std::endl;
    
    typename std_set_type::iterator end = set.end();
    typename ft_set_type::iterator fend = fset.end();

    std::cout << "Lower Bound test" << std::endl;
    iter = set.lower_bound(valid);
    fiter = fset.lower_bound(valid);
    std::cout <<
        (check_interval_normal(iter, end, fiter, fend) ? "OK" : "KO")
            << std::endl;

    std::cout << "Upper Bound test" << std::endl;
    iter = set.upper_bound(valid);
    fiter = fset.upper_bound(valid);
    std::cout <<
        (check_interval_normal(iter, end, fiter, fend) ? "OK" : "KO")
            << std::endl;

    std::cout << "Equal Bound test" << std::endl;
    ft::pair<typename ft_set_type::iterator,
                typename ft_set_type::iterator> feq = fset.equal_range(valid);
    std::pair<typename std_set_type::iterator,
                typename std_set_type::iterator> eq = set.equal_range(valid);

    std::cout <<
        (check_interval_normal(eq.first, eq.second, feq.first, feq.second) ? "OK" : "KO")
            << std::endl;

}


template <typename std_set_type, typename ft_set_type,
            typename data_type >
void operator_test (data_type *data) {
    
    ft_set_type fset1(data, data + 3);
    ft_set_type fset2(data, data + 3);
    ft_set_type fset3(data, data + 5);

    std_set_type set1(data, data + 3);
    std_set_type set2(data, data + 3);
    std_set_type set3(data, data + 5);
    
    std::cout << "Operator ==" << std::endl;
    std::cout << ((set1 == set2) == (fset1 == fset2) ? "OK" : "KO") << std::endl;
    std::cout << ((set1 == set3) == (fset1 == fset3) ? "OK" : "KO") << std::endl;

    std::cout << "Operator <" << std::endl;
    std::cout << ((set1 < set2) == (fset1 < fset2) ? "OK" : "KO") << std::endl;
    std::cout << ((set1 < set3) == (fset1 < fset3) ? "OK" : "KO") << std::endl;

    std::cout << "Operator <=" << std::endl;
    std::cout << ((set1 <= set2) == (fset1 <= fset2) ? "OK" : "KO") << std::endl;
    std::cout << ((set1 <= set3) == (fset1 <= fset3) ? "OK" : "KO") << std::endl;

    std::cout << "Operator >" << std::endl;
    std::cout << ((set1 > set2) == (fset1 > fset2) ? "OK" : "KO") << std::endl;
    std::cout << ((set1 > set3) == (fset1 > fset3) ? "OK" : "KO") << std::endl;

    std::cout << "Operator >=" << std::endl;
    std::cout << ((set1 >= set2) == (fset1 >= fset2) ? "OK" : "KO") << std::endl;
    std::cout << ((set1 >= set3) == (fset1 >= fset3) ? "OK" : "KO") << std::endl;

    std::cout << "Operator !=" << std::endl;
    std::cout << ((set1 != set2) == (fset1 != fset2) ? "OK" : "KO") << std::endl;
    std::cout << ((set1 != set3) == (fset1 != fset3) ? "OK" : "KO") << std::endl;
}

// Test functions end ################################################################################

// Wrappers for the test functions ###################################################################
template <typename std_set_type, typename ft_set_type,
            typename data_type >
void capacity_test_b (data_type *data) {
    capacity_test < std_set_type,
                    ft_set_type > (data);
}

template <typename std_set_type, typename ft_set_type,
            typename data_type >
void insert_delete_test_b (data_type data){
    insert_delete_test < std_set_type,
                         ft_set_type > (data);
}

template <typename std_set_type, typename ft_set_type,
            typename data_type>
void swap_test_b (data_type data){
    swap_test < std_set_type,
                 ft_set_type > (data);
}

template <typename std_set_type, typename ft_set_type,
            typename data_type >
void look_up_test_b (data_type *data, data_type valid,
                        data_type invalid){
    look_up_test < std_set_type,
                 ft_set_type > (data, valid, invalid);
}

template <typename std_set_type, typename ft_set_type,
            typename data_type>
void operator_test_b (data_type data) {
    operator_test < std_set_type,
                    ft_set_type > (data);
}

template <typename std_set_type, typename ft_set_type,
         typename data_type >
void init_set_test_b (data_type *data) {
    init_set_test< std_set_type,
                    ft_set_type > (data);
}
// Wrappers for the test functions end ###############################################################

#endif

// a4_main.cpp

#include "a4.h"

// Use this main function to call the test functions. Or re-write it any way you
// like. The marker will use their own main function.
int main () {
	// cout << "a4_main.cpp called ... \n";
    // cout << sum_of_squares(5) << endl;
    // cout << strange_seq(5) << endl;
    // cout << is_ternary("111112121201010120211") << endl;
    // cout << is_int("--25151525") << endl;
    // cout << strip("    dfs     fds       poop    ") << endl;
    // vector<int> v = {0, 8, -9, -1};
    // cout << sum_neg(v) << endl;
    // vector<int> a = {3, 4, 1, 8};
    // vector<int> b = {2, 5, 2, 9};
    // // for(int i = 0; i < a.size(); i++){
    //     cout << max_vec(a, b).at(3) << endl;
    // // }
    //     vector<string> test = {"hi", "poop", "poop", "poop", "test", "poop", "poop"};
    //     cout << count(test, "poop") << endl;
    //     cout << zip("abc", "xyz").at(2) << endl;
    //     cout << join({"he", "we", "see"}, "-") << endl;
    sum_of_squares_test();
    strange_seq_test();
    is_ternary_test();
    is_int_test();
    strip_test();
    sum_neg_test();
    max_vec_test();
    zip_test();
    join_test();
}
// a4.cpp

/////////////////////////////////////////////////////////////////////////
//
// Student Info
// ------------
//

//
// Statement of Originality
// ------------------------
//
// All the code and comments below are my own original work. For any non-
// original work, I have provided citations in the comments with enough detail
// so that someone can see the exact source and extent of the borrowed work.
//
// In addition, I have not shared this work with anyone else, and I have not
// seen solutions from other students, tutors, websites, books, etc.
//
/////////////////////////////////////////////////////////////////////////

#include "a4.h"  // no other includes are allowed!

using namespace std;

//
// Put your implementations of the functions specified in "a4.h" here.
//

int sum_of_squares(int n){
    if(n < 0){cmpt::error("n must be greater then 0");}
    if(n > 0){
        return n * n + sum_of_squares(n - 1);
    }
    else{
        return 0;
    }
}

void sum_of_squares_test(){
    assert(sum_of_squares(4) == 30);
    assert(sum_of_squares(0) == 0);
    assert(sum_of_squares(1) == 1);
    cout << "all sum of squares tests passed\n";
}

int strange_seq(int n){
    if(n < 0){cmpt::error("n must be greater or equal to 0");}
    if(n > 0){
        if(n == 1){
        int x = 2*strange_seq(n-1) + 3;
        return x;
        }
        int x = 2*strange_seq(n-1) + 1;
        return x;
    }
    else{return 0;}
}

void strange_seq_test(){
    assert(strange_seq(1) == 3);
    assert(strange_seq(2) == 7);
    assert(strange_seq(7) == 255);
    cout << "all strange seq tests passed";
}

int is_ternary(const string& s, int n){
    if(s.size() == 0){cout << s << endl; return 1;}
    else if(s.at(0) != '2' && s.at(0) != '0' && s.at(0) != '1'){
        n += 2;
        return n;
    }
    else{
        return is_ternary(s.substr(1), n + 1);
    }
}

bool is_ternary(const string& s){
    if(is_ternary(s, 0) == 1){
        return true;
    }
    else{
        return false;
    }
}

void is_ternary_test(){
    assert(is_ternary("1202011201") == 1);
    assert(is_ternary("1202511201") == 0);
    assert(is_ternary("5202111201") == 0);
    assert(is_ternary("202111205") == 0);
    cout << "all is ternary tests passed\n";
}

int is_int(const string& s, int n){
    if(s.size() == 0){return 0;}
    else if(s.size() == n){return 1;}
    else if(!(s.at(0) == '-' || s.at(n) == '0' || s.at(n) == '1' ||
       s.at(n) == '2' || s.at(n) == '3' || s.at(n) == '4' ||
       s.at(n) == '5' || s.at(n) == '6' || s.at(n) == '7' ||
       s.at(n) == '8' || s.at(n) == '9')){
        return 0;
    }
    else if(n != 0){
        if(s.at(0) == '-' && !(s.at(n) == '0' || s.at(n) == '1' ||
        s.at(n) == '2' || s.at(n) == '3' || s.at(n) == '4' ||
        s.at(n) == '5' || s.at(n) == '6' || s.at(n) == '7' ||
        s.at(n) == '8' || s.at(n) == '9')){
        return 0;
    }
    else{
        return is_int(s, n + 1);
    }
    }
    else{
        return is_int(s, n + 1);
    }
}

bool is_int(const string& s){
    if(is_int(s, 0) == 0){
        return false;
    }
    else{
        return true;
    }
}

void is_int_test(){
    assert(is_int("0123456789") == 1);
    assert(is_int("-0123456789") == 1);
    assert(is_int("") == 0);
    assert(is_int("12314532g") == 0);
    assert(is_int("-12314532g") == 0);
    assert(is_int("--1234") == 0);
    cout << "all is int tests passed\n";
}

string strip_front(const string& s, int n){
    string str = s;
    bool conditionA = char(s.at(n)) >= 'a' && char(s.at(n)) <= 'z';
    bool conditionB = char(s.at(n)) >= 'A' && char(s.at(n)) <= 'Z';
    if(conditionA || conditionB){
        return str.substr(n, s.size() - n);
    }
    else if(n == s.size() -1){
        return "";
    }
    else{
        return strip_front(s, n + 1);
    }
}

string strip_back(const string& s, int n){
    string str = s;
    bool conditionA = char(s.at(n)) >= 'a' && char(s.at(n)) <= 'z';
    bool conditionB = char(s.at(n)) >= 'A' && char(s.at(n)) <= 'Z';
    if(conditionA || conditionB){
        return str.substr(0, n + 1);
    }
    else{
        return strip_back(s, n - 1);
    }
}

string strip(const string& s){
    string str = "";
    if(s == ""){
        return str;
    }
    str = strip_front(s, 0);
    if (str == ""){
        return str;
    }
    str = strip_back(str, str.size() - 1);
    return str;
}

void strip_test(){
    assert(strip("   a   a   b c  ") == "a   a   b c");
    assert(strip("     ") == "");
    assert(strip("") == "");
    assert(strip("aaaa    ") == "aaaa");
    assert(strip("     aaaa") == "aaaa");
    cout << "all strip tests passed\n";
}

int sum_neg(const vector<int>& v, int begin){
    if(begin >= v.size()){
        return 0;
    }
    else if(v[begin] < 0){
        return v[begin] + sum_neg(v, begin + 1);
    }
    else{
        return sum_neg(v, begin + 1);
    }
}

int sum_neg(const vector<int>& v){
    return sum_neg(v, 0);
}

void sum_neg_test(){
    assert(sum_neg({0, 8, -9, -1}) == -10);
    assert(sum_neg({0}) == 0);
    assert(sum_neg({0, -8, -9, -1}) == -18);
    assert(sum_neg({0, 8}) == 0);
    assert(sum_neg({}) == 0);
    cout << "all sum neg tests passed\n";
}

vector<int> max_vec(const vector<int>& a, const vector<int>& b, int begin, vector<int>& max){
    if(b.size() != a.size() && a.size() <= 0){cmpt::error("vectors must be greator or equal to zero and same size");}
    if(begin == a.size()){
        return max;
    }
    else if(a[begin] > b[begin]){
        max.push_back(a[begin]);
        return max_vec(a, b, begin + 1, max);
    }
    else if(b[begin] > a[begin]){
        max.push_back(b[begin]);
        return max_vec(a, b, begin + 1, max);
    }
    else{
        max.push_back(a[begin]);
        return max_vec(a, b, begin + 1, max);
    }
}

vector<int> max_vec(const vector<int>& a, const vector<int>& b){
    vector<int> max;
    return max_vec(a, b, 0, max);
}

void max_vec_test(){
    vector<int> v = {5, 8};
    vector<int> b = {4, 7, 2, 7};
    assert(max_vec({5, 8}, {0, 2}) == v);
    assert(max_vec({5, 8}, {0, 2}).size() == 2);
    assert(max_vec({4, 7, 1, 4}, {1, 2, 2, 7}) == b);
    assert(max_vec({4, 7, 1, 4}, {1, 2, 2, 7}).size() == 4);
    cout << "all max vec tests passed\n";
}

int count(const vector<string>& v, const string& s, int begin, int tick){
    if(begin == v.size()){
        return tick;
    }
    else{
        if(v[begin] == s){
            tick++;
            return count(v, s, begin + 1, tick);
        }
        else{
            return count(v, s, begin + 1, tick);
        }
    }
}

int count(const vector<string>& v, const string& s){
    return count(v, s, 0, 0);
}

void count_test(){
    assert(count({"hi", "hi", "test", "test", "hi"}, "hi") == 3);
    assert(count({"hi", "hi", "test", "test", "hi"}, "test") == 2);
    assert(count({"hi", "hi", "test", "test", "hi"}, "Hi") == 0);
    assert(count({}, "hi") == 0);
    cout << "all count tests passed\n";
}

vector<string> zip(const string& s, const string& t, int begin, vector<string> vec){
    if(s.size() != t.size()){cmpt::error("Vectors must be same size");}
    if(s.size() == 0){
        return vec;
    }
    else if(begin == s.size()){
        return vec;
    }
    else{
        string str = "";
        str.push_back(s[begin]);
        str.push_back(t[begin]);            
        vec.push_back(str);
        return zip(s, t, begin + 1, vec);
    }
}

vector<string> zip(const string& s, const string& t){
    vector<string> vec;
    return zip(s, t, 0, vec);
}

void zip_test(){
    vector<string> v = {"xy", "yb", "zn"};
    vector<string> b = {};
    assert(zip("xyz", "ybn") == v);
    assert(zip("xyz", "ybn").size() == 3);
    assert(zip("", "") == b);
    cout << "all zip tests passed\n";
}

string join(const vector<string>& v, const string& sep, int begin, string str){
    if(begin == v.size()){
        return str;
    }
    else{
        if(begin != v.size()-1){
            str += v[begin] + sep;
        }
        else{
            str += v[begin];
        }
        return join(v, sep, begin + 1, str);
    }    assert(join({"he", "we", "see"}, "") == "hewesee");
}

string join(const vector<string>& v, const string& sep){
    string str = "";
    return join(v, sep, 0, str);
}

void join_test(){
    assert(join({"one"}, ", ") == "one");
    assert(join({"up", "dog"}, ", ") == "up, dog");
    assert(join({"he", "we", "see"}, "-") == "he-we-see");
    assert(join({"he", "we", "see"}, "") == "hewesee");
    assert(join({}, "- ") == "");
    cout << "all join tests passed\n";
}
//
// Don't put main() in this file. It goes in a4_main.cpp.
//

// a2.cpp

/////////////////////////////////////////////////////////////////////////
//
// Student Info
// ------------
//
// Name : Yu Shan <put your full name here!>
// St.# : 301573835 <put your full SFU student number here>
// Email: sam_shan@sfu.ca <put your SFU email address here>
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

//
// These are the only permitted includes: don't include anything else.
//
#include "cmpt_error.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <algorithm>

using namespace std;

class str_vec {
  private:
  string* arr1;
  int arr_capacity;
  int arr_size;

  public:
  
  // default constructor
  str_vec()
  : arr_capacity(10), 
    arr_size(0)
  {
    arr1 = new string[arr_capacity];
  }

  // destructor
  ~str_vec(){
    delete[] arr1;
    // cout << "destructor called";
  }

  // constructor for str_vec
  str_vec(int n, string s)
  :arr_capacity(10), arr_size(n)
  {
    if(n < 1){
      cmpt::error("str_vec(int n): n must be 1 or greater");
    }
    while(arr_size > arr_capacity){
      arr_capacity = arr_capacity * 2;
    }
    arr1 = new string[arr_capacity];
    for(int i = 0; i < arr_size; i++){
        arr1[i] = s;
    }
  }

  // copy constructor for str_vec
  str_vec(const str_vec& other)
  : arr1(new string[other.arr_capacity]),
    arr_capacity(other.arr_capacity),
    arr_size(other.arr_size)
    {
      for(int i = 0; i < arr_size; i++){
        arr1[i] = other.arr1[i];
      }
    }

  // arr constructor for str_vec
  str_vec(const char* arr[], int n)
  :str_vec(n, "")
  {
    for(int i = 0; i < n; i++){
      arr1[i] = arr[i];
    }
  }

  // puts str_vec in form of array
  string to_str() const{
    string str_rep = "{";
    for(int i = 0; i < arr_size; i++){
        if(i != 0){
            str_rep += ", ";
        }
        str_rep += "\"" + arr1[i] + "\"";     
    }
        str_rep += "}";
    return str_rep;
  }

  // prints str_vec in form of array
  void print() const{
    string str_rep = "{";
    for(int i = 0; i < arr_size; i++){
        if(i != 0){
            str_rep += ", ";
        }
        str_rep += "\"" + arr1[i] + "\"";     
    }
        str_rep += "}";
    cout << str_rep;
  }

  // prints str_vec in form of array with line
  void println() const{
  string str_rep = "{";
    for(int i = 0; i < arr_size; i++){
        if(i != 0){
            str_rep += ", ";
        }
        str_rep += "\"" + arr1[i] + "\"";     
    }
    str_rep += "}";
    cout << str_rep << endl;
  }

  // checks and returns string at index i
  string get(int i) const{
    if(i < 0 || i > arr_size - 1){
      cmpt::error("get: index out of bounds");
    }
    return arr1[i];
  }

  // checks and sets string at index i
  void set(int i, string word){
    if(i < 0 || i > arr_size - 1){
      cmpt::error("set: index out of bounds");
    }
    arr1[i] = word;
  }

  // adds s to the end of array
  void append(string s){
    arr_size++;
    while ((arr_size) > arr_capacity){
        arr_capacity = arr_capacity * 2;
        string* arr_new = new string[arr_capacity];
        for(int i = 0; i < (arr_size -1); i++){
          arr_new[i] = arr1[i];
        }
        delete[] arr1;
        arr1 = arr_new;
      }
    arr1[arr_size - 1] = s;
  }

  // adds sv to the end of array
  void append(str_vec sv){
    arr_size += sv.arr_size;
    while ((arr_size) > arr_capacity){
      arr_capacity = arr_capacity * 2;
      string* arr_new = new string[arr_capacity];
      for(int i = 0; i < (arr_size - sv.arr_size); i++){
        arr_new[i] = arr1[i];
      }
      delete[] arr1;
      arr1 = arr_new;
    }
    int o = 0;
    for(int i = (arr_size - sv.arr_size); i < (arr_size); i++){
      arr1[i] = sv.arr1[o];
      o++;
    }
  }

  // checks and capitilizes first letter
  void capitalize_all(){
    if(arr_size != 0){
      for(int i = 0; i < arr_size; i++){
      bool conditionA = arr1[i] != "";
        if(conditionA){
          bool conditionB = char(arr1[i].at(0)) > 'a' && char(arr1[i].at(0)) < 'z';
          bool conditionC = char(arr1[i].at(0)) > 'A' && char(arr1[i].at(0)) < 'Z';
          if(conditionA || conditionB || conditionC){
            arr1[i].at(0) = char(toupper(arr1[i].at(0)));
          }
        }
      }
    }
  }

// removes first string s in str_vec
  void remove_first(const string& s){
    for(int i = 0; i < arr_size; i++){
      if(arr1[i] == s){
          int x = 0;
          for(int o = 0; o < arr_size; o++){
            if(o != i){
              arr1[x] = arr1[o];
              x++;
            }
          }
          arr_size--;
          break;
      }
    }
  }

// keeps all the strings in str_vec that starts with c
  void keep_all_starts_with(char c){
      int x = 0;
      for(int i = 0; i < arr_size; i++){
        if(char(arr1[i].at(0)) == c){
              arr1[x] = arr1[i];
              x++;
          }
      }
      arr_size = x;
  }

  void clear(){
    arr_size = 0;
  }

  void squish(){
    if(arr_size != arr_capacity){
      arr_capacity = arr_size;
    }
  }

  void sort(){
    std::sort(arr1, arr1 + arr_size);
  }

  int size() const{
      return arr_size;
    }
  int length() const{
      return arr_size;
    }
  int capacity() const{
      return arr_capacity;
    }
  double pct_used() const{
      double x = arr_size;
      double y = arr_capacity;
      return (x/y);
    }

}; // class str_vec

// operator overloads
bool operator==(const str_vec a, const str_vec b){
  bool isTrue = true;
  if(a.size() != b.size()){
    isTrue = false;
    return isTrue;
  }
  for(int i = 0; i < a.size(); i++){
    if(a.get(i) != b.get(i)){
      isTrue = false;
      return isTrue;
    }
  }
  return isTrue;
}

bool operator!=(const str_vec a, const str_vec b){
  bool isTrue = false;
  if(a.size() != b.size()){
    isTrue = true;
    return isTrue;
  }
  for(int i = 0; i < a.size(); i++){
    if(a.get(i) != b.get(i)){
      isTrue = true;
      return isTrue;
    }
  }
  return isTrue;
}

// ... put test functions here ...

// size test function
void test_get_size(){
  str_vec a(5, "test");
  if(a.size() != 5) {cout << "test failed\n";}
  if(a.length() != 5) {cout << "test failed\n";} 
  str_vec b(7, "test");
  if(b.size() != 7) {cout << "test failed\n";}
  if(b.length() != 7) {cout << "test failed\n";} 
  str_vec c(9, "test");
  if(c.size() != 9) {cout << "test failed\n";}
  str_vec d(15, "test");
  if(d.size() != 15) {cout << "test failed\n";}
  cout << "all tests passed\n";
}

// capacity test function
void test_get_capacity(){
  str_vec a(5, "test");
  if(a.capacity() != 10) {cout << "test failed\n";}
  str_vec b(7, "test");
  if(b.capacity() != 10) {cout << "test failed\n";}
  str_vec c(12, "test");
  if(c.capacity() != 20) {cout << "test failed\n";}
  str_vec d(32, "test");
  if(d.capacity() != 40) {cout << "test failed\n";}
  str_vec e(50, "test");
  if(e.capacity() != 80) {cout << "test failed\n";}
  cout << "all tests passed\n";
}

// pct_used test function
void test_get_pct_used(){
  str_vec a(5, "test");
  if(a.pct_used() != 0.5) {cout << "test failed\n";}
  str_vec b(7, "test");
  if(b.pct_used() != 0.7) {cout << "test failed\n";}
  str_vec c(9, "test");
  if(c.pct_used() != 0.9) {cout << "test failed\n";}
  str_vec d(15, "test");
  if(d.pct_used() != 0.75) {cout << "test failed\n";}
  cout << "all tests passed\n";
}

// to_str() test fuction
void test_to_str(){
  str_vec a(5, "test");
  if(a.to_str() != ("{\"test\", \"test\", \"test\", \"test\", \"test\"}")) {cout << "test failed\n";}
  str_vec b(2, "cat");
  if(b.to_str() != ("{\"cat\", \"cat\"}")) {cout << "test failed\n";}
  str_vec c(1, "test");
  if(c.to_str() != ("{\"test\"}")) {cout << "test failed\n";}
  cout << "all tests passed\n";
}

// get(i) test function
void test_get(){
  str_vec a(5, "test");
  if(a.get(2) != "test") {cout << "test failed\n";}
  str_vec b(7, "cat");
  if(b.get(5) != "cat") {cout << "test failed\n";}
  str_vec c(9, "dog");
  if(c.get(8) != "dog") {cout << "test failed\n";}
  cout << "all tests passed\n";
}

// set(i) test function
void test_set(){
  str_vec a(5, "test");
  a.set(3, "coat");
  if(a.get(3) != "coat") {cout << "test failed\n";}
  if(a.get(2) != "test") {cout << "test failed\n";}
  str_vec b(7, "cat");
  b.set(2, "test");
  if(b.get(5) != "cat") {cout << "test failed\n";}
  if(b.get(2) != "test") {cout << "test failed\n";}
  str_vec c(9, "dog");
  c.set(8, "cat");
  if(c.get(2) != "dog") {cout << "test failed\n";}
  if(c.get(8) != "cat") {cout << "test failed\n";}
  cout << "all tests passed\n";
}

// append(s) test function
void test_append(){
  str_vec a(5, "test");
  a.append("coat");
  if(a.get(5) != "coat") {cout << "test failed\n";}
  if(a.get(2) != "test") {cout << "test failed\n";}
  str_vec b(7, "cat");
  b.append("test");
  if(b.get(5) != "cat") {cout << "test failed\n";}
  if(b.get(7) != "test") {cout << "test failed\n";}
  str_vec c;
  c.append("cat");
  if(c.get(0) != "cat") {cout << "test failed\n";}
  cout << "all tests passed\n";
}

// append(sv) test function
void test_appendsv(){
  str_vec a(5, "test");
  str_vec b(7, "cat");
  a.append(b);
  if(a.get(2) != "test") {cout << "test failed\n";}
  if(a.get(9) != "cat") {cout << "test failed\n";}
  if(a.size() != 12) {cout << "test failed\n";}
  str_vec c;
  str_vec d(5, "test");
  c.append(d);
  if(c.get(2) != "test") {cout << "test failed\n";}
  if(c.size() != 5) {cout << "test failed\n";}
  cout << "all tests passed\n";
}

// capitalize_all test function
void test_capitalize_all(){
  str_vec a(5, "test");
  str_vec b(7, "cat");
  str_vec c(1, "-at");
  str_vec d;
  a.append(b);
  a.append(c);
  a.capitalize_all();
  b.capitalize_all();
  d.capitalize_all();
  if(a.get(2).at(0) != 'T') {cout << "test failed\n";}
  if(a.get(4).at(0) != 'T') {cout << "test failed\n";}
  if(a.get(8).at(0) != 'C') {cout << "test failed\n";}
  if(a.get(11).at(0) != 'C') {cout << "test failed\n";}
  if(b.get(5).at(0) != 'C') {cout << "test failed\n";}
  if(a.get(12).at(0) != '-') {cout << "test failed\n";}  
  if(d.to_str() != "{}") {cout << "test failed\n";}     
  cout << "all tests passed\n";
}

// remove first test function
void test_remove_first(){
  str_vec a(3, "test");
  str_vec b(4, "cat");
  a.remove_first("test");
  if(a.size() != 2) {cout << "test failed\n";}
  if(a.get(0) != "test") {cout << "test failed\n";}
  a.append(b);
  if(a.size() != 6) {cout << "test failed\n";}
  if(a.get(1) != "test") {cout << "test failed\n";}
  if(a.get(4) != "cat") {cout << "test failed\n";}
  a.remove_first("cat");
  if(a.size() != 5) {cout << "test failed\n";}
  if(a.get(1) != "test") {cout << "test failed\n";}
  if(a.get(4) != "cat") {cout << "test failed\n";}
  cout << "all tests passed\n";
}

//  keep_all_starts_with test function
void test_keep_all_starts_with(){
  str_vec a(3, "test");
  str_vec b(3, "dog");
  str_vec c(2, "coconut");
  str_vec d(4, "cat");
  a.keep_all_starts_with('t');
  if(a.size() != 3) {cout << "test failed\n";}
  if(a.get(2) != "test") {cout << "test failed\n";}
  a.keep_all_starts_with('c');
  if(a.size() != 0) {cout << "test failed\n";}
  b.append(c);
  b.append(d);
  b.keep_all_starts_with('c');
  if(b.size() != 6) {cout << "test failed\n";}
  if(b.get(1) != "coconut") {cout << "test failed\n";}
  if(b.get(3) != "cat") {cout << "test failed\n";}
  cout << "all tests passed\n";
}

// squish test function
void test_squish(){
  str_vec arr;   
  arr.append("a"); 
  arr.append("b");
  arr.squish(); 
  if(arr.capacity() != 2) {cout << "test failed\n";}
  arr.append("c");
  if(arr.capacity() != 4) {cout << "test failed\n";}
  arr.squish(); 
  if(arr.capacity() != 3) {cout << "test failed\n";}
  arr.append("a"); 
  arr.append("b");
  arr.append("b");
  if(arr.capacity() != 6) {cout << "test failed\n";}
  arr.squish(); 
  if(arr.capacity() != 6) {cout << "test failed\n";} 
  cout << "all tests passed\n";  
}

// clear test function
void test_clear(){
  str_vec arr;   
  arr.append("a"); 
  arr.append("b");
  arr.clear(); 
  if(arr.size() != 0) {cout << "test failed\n";}
  if(arr.capacity() != 10) {cout << "test failed\n";}
  arr.append("c");
  if(arr.size() != 1) {cout << "test failed\n";}
  arr.clear(); 
  if(arr.size() != 0) {cout << "test failed\n";}
  arr.append("a"); 
  arr.append("b");
  arr.append("b");
  if(arr.size() != 3) {cout << "test failed\n";}
  arr.clear(); 
  if(arr.size() != 0) {cout << "test failed\n";} 
  cout << "all tests passed\n";  
}

// tests == operand
void test_equal_operands(){
  str_vec a(3, "cat"); 
  str_vec b(3, "cat");
  if ((a == b) != 1) {cout << "test failed\n";}     
  str_vec c(3, "aat");
  str_vec d;  
  str_vec e(7, "aat");
  if ((a == d) != 0) {cout << "test failed\n";}     
  if ((a == c) != 0) {cout << "test failed\n";}   
  if ((c == e) != 0) {cout << "test failed\n";}        
  cout << "all tests passed\n";  
}

// tests != operand
void test_not_equal_operands(){
  str_vec a(3, "cat"); 
  str_vec b(3, "cat");
  if ((a != b) != 0) {cout << "test failed\n";}     
  str_vec c(3, "aat");
  str_vec d;  
  str_vec e(7, "aat");
  if ((a != d) != 1) {cout << "test failed\n";}  
  if ((a != c) != 1) {cout << "test failed\n";}   
  if ((c != e) != 1) {cout << "test failed\n";}        
  cout << "all tests passed\n";  
}

// tests != operand
void test_sort(){
  str_vec a(2, "cat"); 
  str_vec b(1, "at");
  a.append(b);
  a.sort();
  if (a.get(0) != "at") {cout << "test failed\n";}     
  if (a.get(1) != "cat") {cout << "test failed\n";}
  str_vec c(3, "aat");
  a.append(c);  
  a.sort();
  if (a.get(0) != "aat") {cout << "test failed\n";}     
  if (a.get(1) != "aat") {cout << "test failed\n";}
  if (a.get(3) != "at") {cout << "test failed\n";}     
  if (a.get(5) != "cat") {cout << "test failed\n";}
  str_vec d;
  a.append(d);
  if (a.get(0) != "aat") {cout << "test failed\n";}     
  if (a.get(1) != "aat") {cout << "test failed\n";}
  if (a.get(3) != "at") {cout << "test failed\n";}     
  if (a.get(5) != "cat") {cout << "test failed\n";}
  cout << "all tests passed\n";  
}

int main() {
  cout << "Assignment 2 ... \n";

  //
  // ... put code that calls your test functions here ...
  //

  test_get_size();
  test_get_capacity();
  test_get_pct_used();
  test_to_str();
  test_get();
  test_set();
  test_append();
  test_appendsv();
  test_capitalize_all();
  test_remove_first();
  test_keep_all_starts_with();
  test_squish();
  test_clear();
  test_equal_operands();
  test_not_equal_operands();
  test_sort();
}
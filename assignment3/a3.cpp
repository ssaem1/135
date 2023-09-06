// a3.cpp

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


#include "cmpt_error.h"
#include <iostream>
#include <cassert>
#include "Date_base.h"
#include "Todo_item_base.h"
#include "Todo_list_base.h"
#include <vector>
#include <fstream>  
#include <algorithm>

using namespace std;

class Date : public Date_base {
private:
  int day;
  int month;
  int year;

public:
  Date(int d, int m, int y)
  :day(d), month(m), year(y)
  {
    if(d < 1 && d > 31){
      cmpt::error("str_vec(int n): n must be 1 or greater");
    }
    if(m < 1 && m > 12){
      cmpt::error("str_vec(int n): n must be 1 or greater");
    }
    if(y < 0){
      cmpt::error("str_vec(int n): n must be 0 or greater");
    }
  }

  Date(const Date &other)
  :day(other.day),
  month(other.month),
  year(other.year)
  {}

  // default constructor
  Date()
  :day(0),
  month(0),
  year(0)
  {}

  // string constructor
  Date(const string str)
  :day(stoi(str)),
   month(stoi(str.substr(3))),
   year(stoi(str.substr(6)))
   {}

  // getters
  int get_year() const {return year;}
	int get_month() const {return month;}
	int get_day() const {return day;}

	// setters
	void set_year(int new_year) {year = new_year;}
	void set_month(int new_month) {month = new_month;}
	void set_day(int new_day) {day = new_day;}  

  Date &operator=(const Date &other){
    day = other.day; 
    month = other.month;
    year = other.year;
    return *this;
  }

  string to_string() const{
    string date = "";
    if(day < 10){
      date += "0" + std::to_string(day) + "/";
    }
    else{
      date += std::to_string(day) + "/";
    }
    if(month < 10){
      date += "0" + std::to_string(month) + "/";
    }
    else{
      date += std::to_string(month) + "/";
    }
    if(year < 10){
      date += "000" + std::to_string(year);
    }
    else if(year < 100){
      date += "00" + std::to_string(year);
    }
    else if(year < 1000){
      date += "0" + std::to_string(year);
    }
    else{
      date += std::to_string(year);
    }
    return date;
  }
};

  bool operator<(const Date& a, const Date& b) {
    if(a.get_year() < b.get_year()){
      return true;
    }
    if(a.get_year() == b.get_year()){
      if(a.get_month() < b.get_month()){
        return true;
      }
      if(a.get_month() == b.get_month()){
        if(a.get_day() < b.get_day()){
          return true;
        }
      }
    }
    return false;
  }

class Todo_item : public Todo_item_base {
private:
  bool done;
  Date due_date;
  string description;

public:
  Todo_item(string description, Date deadline)
  :done(false),
  due_date(deadline),
  description(description)
  {}

  Todo_item()
  {}
  
  Todo_item(string str)
  :done(str[10] == '@'),
  due_date(Date(str)),
  description(str.substr(12))
  {}
  

	bool is_done() const{return done;}
  string get_description() const{return description;}
	Date get_due_date() const {return due_date;}

  // setters
	void set_description(const string& new_description){description = new_description;}
	void set_done(){done = true;}
	void set_not_done(){done = false;}
	void set_due_date(const Date& new_due_date){due_date = new_due_date;}

  string to_string() const{
    string str = "";
    str += due_date.to_string();
    if(done){
      return due_date.to_string() + "@" + " " + description;
    }
    else{
      return due_date.to_string() + "!" + " " + description;
    }
  }
  
  string to_html_item() const{
    if(done){
      return "<li><del>" + due_date.to_string() + " " + description + "</del></li>";
    }
    else{
      return "<li>" + due_date.to_string() + " " + description + "</li>";
    }
  }
};

    bool operator<(const Todo_item& t1, const Todo_item& t2){
    if(t1.get_due_date().get_year() < t2.get_due_date().get_year()){
      return true;
    }
    if(t1.get_due_date().get_year() == t2.get_due_date().get_year()){
      if(t1.get_due_date().get_month() < t2.get_due_date().get_month()){
        return true;
      }
      if(t1.get_due_date().get_month() == t2.get_due_date().get_month()){
        if(t1.get_due_date().get_day() < t2.get_due_date().get_day()){
          return true;
        }
      }
    }
    return false;
  }

class Todo_list : public Todo_list_base {
private:
  vector<Todo_item> vect;
  Todo_item item;
  int vectSize = vect.size();

public:
  Todo_list()
  :vectSize(0)
  {}

	int size() const{return vect.size();}
	Todo_item get_item(int i) const{return vect.at(i);}

	// setters
	void add_item(const Todo_item& item) {vect.push_back(item);}
	void remove_item(int i) {vect.erase(vect.begin() + i);}

  void read_from_file(const string& filename){
     // tests if file name exists
    ifstream testingFile(filename);
    while(true){
        if(filename == ""){
            exit(EXIT_FAILURE);
        }
        else{
            break;
        }
    }
        while(true){
          string temp = "";
          getline(testingFile, temp);
          if(testingFile.fail()){
            break;
          }
          vect.push_back(Todo_item(temp));
        }
  }
  void write_to_file(const string& filename){
        ofstream fileOut(filename);
        while(true){
        if(filename == ""){
          ofstream fileOut(filename + ".txt");
        }
        else{
            break;
        }
      }
      sort(vect.begin(), vect.end());
      for(int i = 0; i < vect.size(); i++){
        fileOut << vect.at(i).to_string() << endl;
      }
  }
  void write_to_html_file(const string& filename){
        ofstream fileOut(filename);
        while(true){
        if(filename == ""){
          ofstream fileOut(filename + ".txt");
        }
        else{
            break;
        }
      }
      sort(vect.begin(), vect.end());
      fileOut << "<ul>" << endl;
      for(int i = 0; i < vect.size(); i++){
        fileOut << vect.at(i).to_html_item() << endl;
      }   
      fileOut << "</ul>";
  }
};

void step_2_1_test(){
    Date xmas(25, 12, 2018);

    cout << xmas.get_day() << " "
         << xmas.get_month() << " "
         << xmas.get_year() << "\n";

    assert(xmas.get_day() == 25);
    assert(xmas.get_month() == 12);
    assert(xmas.get_year() == 2018);

    xmas.set_year(2020);

    assert(xmas.get_day() == 25);
    assert(xmas.get_month() == 12);
    assert(xmas.get_year() == 2020);

    cout << "All step_2_1 tests passed!\n";
}

void step_2_2_test()
{
    Date a(25, 12, 2018);
    Date b = a;

    assert(a.get_day() == 25);
    assert(a.get_month() == 12);
    assert(a.get_year() == 2018);

    assert(a.get_day() == b.get_day());
    assert(a.get_month() == b.get_month());
    assert(a.get_year() == b.get_year());

    b = Date(1, 1, 2019);
    a = b;

    assert(a.get_day() == 1);
    assert(a.get_month() == 1);
    assert(a.get_year() == 2019);

    assert(a.get_day() == b.get_day());
    assert(a.get_month() == b.get_month());
    assert(a.get_year() == b.get_year());

    cout << "All step_2_2 tests passed!\n";
}

void step_2_3_test()
{
    Date a(25, 12, 2018);
    Date b(4, 19, 1999);
    Date c(1, 1, 0);

    assert(a.to_string() == "25/12/2018");
    assert(b.to_string() == "04/19/1999");
    assert(c.to_string() == "01/01/0000");

    cout << "All step_2_3 tests passed!\n";
}

void step_2_4_test()
{
    Date a("25/12/2018");
    Date b("04/19/1999");
    Date c("01/01/0000");

    assert(a.get_day() == 25);
    assert(a.get_month() == 12);
    assert(a.get_year() == 2018);

    assert(b.get_day() == 4);
    assert(b.get_month() == 19);
    assert(b.get_year() == 1999);

    assert(c.get_day() == 1);
    assert(c.get_month() == 1);
    assert(c.get_year() == 0);

    cout << "All step_2_4 tests passed!\n";
}

void step_2_5_test()
{
    Date a("01/01/0000");
    Date b("01/01/2018");
    Date c("02/01/2018");
    Date d("01/02/2018");

    assert(a < b);
    assert(a < c);
    assert(a < d);
    assert(b < c);
    assert(b < d);
    assert(c < d);

    assert(!(a < a));
    assert(!(b < a));
    
    cout << "All step_2_5 tests passed!\n";
}

void step_3_1_test()
{
    Date xmas(25, 12, 2018);
    Todo_item buy_gifts("Buy gifts", xmas);

    assert(buy_gifts.get_description() == "Buy gifts");
    assert(buy_gifts.get_due_date().get_day() == xmas.get_day());
    assert(buy_gifts.get_due_date().get_month() == xmas.get_month());
    assert(buy_gifts.get_due_date().get_year() == xmas.get_year());
    assert(!buy_gifts.is_done());

    buy_gifts.set_done();
    assert(buy_gifts.is_done());
    buy_gifts.set_not_done();
    assert(!buy_gifts.is_done());

    Date earlier(20, 12, 2018);
    buy_gifts.set_due_date(earlier);
    assert(buy_gifts.get_due_date().get_day() == earlier.get_day());
    assert(buy_gifts.get_due_date().get_month() == earlier.get_month());
    assert(buy_gifts.get_due_date().get_year() == earlier.get_year());

    buy_gifts.set_description("Buy gifts for family");
    assert(buy_gifts.get_description() == "Buy gifts for family");

    cout << "All step_3_1 tests passed!\n";
}

void step_3_2_test()
{
    Date xmas(25, 12, 2018);
    Todo_item buy_gifts("Buy gifts", xmas);

    assert(buy_gifts.to_string() == "25/12/2018! Buy gifts");

    buy_gifts.set_done();
    assert(buy_gifts.to_string() == "25/12/2018@ Buy gifts");

    cout << "All step_3_2 tests passed!\n";
}

void step_3_3_test()
{
    Date xmas(25, 12, 2018);
    Todo_item buy_gifts("Buy gifts", xmas);

    assert(buy_gifts.to_html_item() == "<li>25/12/2018 Buy gifts</li>");

    buy_gifts.set_done();
    assert(buy_gifts.to_html_item() == "<li><del>25/12/2018 Buy gifts</del></li>");

    Date easter(21, 4, 2019);
    Todo_item weave_basket("Weave basket", easter);

    assert(weave_basket.to_html_item() == "<li>21/04/2019 Weave basket</li>");

    weave_basket.set_done();
    assert(weave_basket.to_html_item() == "<li><del>21/04/2019 Weave basket</del></li>");

    cout << "All step_3_3 tests passed!\n";
}

void step_3_4_test()
{
    Date halloween(31, 10, 2018);
    Date xmas(25, 12, 2018);
    Date easter(21, 4, 2019);

    Todo_item carve_pumpkin("Carve pumpkin", halloween);
    Todo_item buy_gifts("Buy gifts", xmas);
    Todo_item weave_basket("Weave basket", easter);

    assert(carve_pumpkin < buy_gifts);
    assert(buy_gifts < weave_basket);
    assert(carve_pumpkin < weave_basket);

    assert(!(carve_pumpkin < carve_pumpkin));

    assert(!(buy_gifts < carve_pumpkin));
    assert(!(weave_basket < buy_gifts));
    assert(!(weave_basket < carve_pumpkin));

    cout << "All step_3_4 tests passed!\n";
}

void step_3_5_test()
{
    Todo_item a("01/01/0000@ buy a hamster");
    assert(a.get_description() == "buy a hamster");
    assert(a.get_due_date().get_day() == 1);
    assert(a.get_due_date().get_month() == 1);
    assert(a.get_due_date().get_year() == 0);
    assert(a.is_done());

    Todo_item b("01/01/2018! sell hamster");
    assert(b.get_description() == "sell hamster");
    assert(b.get_due_date().get_day() == 1);
    assert(b.get_due_date().get_month() == 1);
    assert(b.get_due_date().get_year() == 2018);
    assert(!b.is_done());

    assert(a < b);
    assert(!(b < a));

    cout << "All step_3_5 tests passed!\n";
}

void step_4_1_test()
{
    Date easter(21, 4, 2018);
    Date halloween(31, 10, 2018);

    Todo_item weave_basket("Weave basket", easter);
    Todo_item carve_pumpkin("Carve pumpkin", halloween);

    Todo_list list;
    assert(list.size() == 0);

    list.add_item(weave_basket);
    assert(list.size() == 1);
    Todo_item item = list.get_item(0);
    Date date = item.get_due_date();
    assert(item.get_description() == weave_basket.get_description());
    assert(date.get_day() == weave_basket.get_due_date().get_day());
    assert(date.get_month() == weave_basket.get_due_date().get_month());
    assert(date.get_year() == weave_basket.get_due_date().get_year());

    list.add_item(carve_pumpkin);
    assert(list.size() == 2);
    list.remove_item(0);
    assert(list.size() == 1);
    item = list.get_item(0);
    date = item.get_due_date();
    assert(item.get_description() == carve_pumpkin.get_description());
    assert(date.get_day() == carve_pumpkin.get_due_date().get_day());
    assert(date.get_month() == carve_pumpkin.get_due_date().get_month());
    assert(date.get_year() == carve_pumpkin.get_due_date().get_year());

    list.remove_item(0);
    assert(list.size() == 0);

    cout << "All step_4_1 tests passed!\n";
}

void step_4_2_test()
{
    Todo_list list;
    list.read_from_file("todo_example.txt");
    assert(list.size() == 11);

    // 13/02/2023! optometrist in afternoon
    Todo_item eyes("optometrist in afternoon", Date(13, 2, 2023));

    Todo_item item = list.get_item(0);
    Date date = item.get_due_date();
    assert(item.get_description() == eyes.get_description());
    assert(date.get_day() == eyes.get_due_date().get_day());
    assert(date.get_month() == eyes.get_due_date().get_month());
    assert(date.get_year() == eyes.get_due_date().get_year());

    cout << "All step_4_2 tests passed!\n";
}

void step_4_3_test()
{
    Todo_list list;

    list.add_item(Todo_item("Buy tinsel", Date(20, 12, 2018)));
    list.add_item(Todo_item("21/04/2018@ Weave basket"));
    list.add_item(Todo_item("Carve pumpkin", Date(31, 10, 2018)));

    list.write_to_file("step_4_3_output.txt");
    list.write_to_html_file("step_4_3_output.html");

    // read step_4_3_output.txt back in and compare to list
    Todo_list list2;
    list2.read_from_file("step_4_3_output.txt");
    assert(list2.size() == 3);
    assert(list2.get_item(0).get_description() == "Weave basket");
    assert(list2.get_item(1).get_description() == "Carve pumpkin");
    assert(list2.get_item(2).get_description() == "Buy tinsel");
    
    assert(list2.get_item(0).get_due_date().get_day() == 21);
    assert(list2.get_item(0).get_due_date().get_month() == 4);
    assert(list2.get_item(0).get_due_date().get_year() == 2018);

    assert(list2.get_item(1).get_due_date().get_day() == 31);
    assert(list2.get_item(1).get_due_date().get_month() == 10);
    assert(list2.get_item(1).get_due_date().get_year() == 2018);

    assert(list2.get_item(2).get_due_date().get_day() == 20);
    assert(list2.get_item(2).get_due_date().get_month() == 12);
    assert(list2.get_item(2).get_due_date().get_year() == 2018);

    assert(list2.get_item(0).is_done() == true);
    assert(list2.get_item(1).is_done() == false);
    assert(list2.get_item(2).is_done() == false);

    cout << "All step_4_3 tests run: check the HTML results by hand!\n";
}

void part5(){
  Todo_list list;
  int num_done = 0;
  int num_not_done = 0;
  Todo_item newest;
  list.read_from_file("part5_todos.txt");
  Todo_item oldest = list.get_item(0);
  for(int i = 0; i < list.size(); i++){
    if(list.get_item(i).is_done()){
      num_done++;
    }
    else{
      num_not_done++;
    }
    if(list.get_item(i) < oldest){
      oldest = list.get_item(i);
    }
    if(newest < list.get_item(i)){
      newest = list.get_item(i);
    }
  }
  cout << "done: " << num_done << endl << "not done: " << num_not_done << endl << "oldest: " << oldest.to_string()
  << endl << "newest: " << newest.to_string() << endl;

  list.write_to_file("final_output");
  list.write_to_html_file("final_output.html");
}

int main()
{
    cout << "Hello from assignment 3!\n";
    step_2_1_test();
    step_2_2_test();
    step_2_3_test();
    step_2_4_test();
    step_2_5_test();
    step_3_1_test();
    step_3_2_test();
    step_3_3_test();
    step_3_4_test();
    step_3_5_test();
    step_4_1_test();
    step_4_2_test();
    step_4_3_test();
    part5();
}
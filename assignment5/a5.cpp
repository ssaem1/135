// a5.cpp

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
// You can use any other C++17 standard #includes that you need.
//
#include <iostream>
#include <vector>
#include "cmpt_error.h"
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

class cords{
private:
    bool isSelected;
    char codeY;
    int codeX;
    bool isChaos;

public:

  cords(bool s, char y, int x, bool c)
  :isSelected(s), codeY(y), codeX(x), isChaos(c)
  {
    if(y > 'x' && y > 31){
      cmpt::error("str_vec(int n): n must be 1 or greater");
    }
    if(x > 0 && x > 12){
      cmpt::error("str_vec(int n): n must be 1 or greater");
    }
  }

  cords(const cords &other)
  :isSelected(other.isSelected),
  codeY(other.codeY),
  codeX(other.codeX),
  isChaos(other.isChaos)
  {}

  // default constructor
  cords()
  :isSelected(0),
  codeY('a'),
  codeX(0),
  isChaos(0)
  {}

	void set_isSelected(bool selected) {isSelected = selected;}
	void set_codeY(char Y) {codeY = Y;}
	void set_codeX(int C) {codeX = C;}  
  void set_isChaos(bool chaos) {isChaos = chaos;}

 bool get_isSelected(){return isSelected;}
 char get_codeY(){return codeY;}
 int get_codeX(){return codeX;}
 bool get_isChaos(){return isChaos;}
};

class board{
private:
    int size;
    vector<cords> grid;
    cords items;

public:

// constructors
board(int s)
  :size(s)
  {}

board()
  :size(0)
  {}
// setters and getters

int get_size(){return size;}
cords get_cords(int i){return grid.at(i);}

void set_size(int i){size = i;}
void add_cord(const cords item){grid.push_back(item);}

void player_move(string move){
  char codeY;
  char codeX;
  if(move[1] < 97 || move[1] > 97 +size){
    cout << "Enter valid Y cordinate" << endl;
    return;}
  if(stoi(move.substr(0,1)) < 0 || stoi(move.substr(0,1)) > size - 1){
    cout << "Enter valid X cordinate" << endl;
    return;}
  for(char i = 97; i < size + 97; i++){
    if(move[1] == (char(i))){
      codeY = i;
    }
  }
  for(int i = 0; i < size; i++){
    if(stoi(move.substr(0, 1)) == i){
      codeX = i;
    }
  }
  for(int i = 0; i < size*size; i++){
    if(grid.at(i).get_codeX() == codeX && grid.at(i).get_codeY() == codeY){
      if((grid.at(i).get_isSelected())){
        cout << "Enter valid cordinate" << endl;
        return;
      }
      if(move.substr(2, 3) == "X"){
        grid.at(i).set_isChaos(1);
        grid.at(i).set_isSelected(1);
      }
      else if(move.substr(2, 3) == "O"){
          grid.at(i).set_isChaos(0);
          grid.at(i).set_isSelected(1);
      }
    }
  }
}

string check_boardXX(){
  int countXX = 0;
  string code = "";
  for(int i = 0; i < size * size;i++){
    if(grid.at(i).get_isSelected() && grid.at(i).get_isChaos()){
      int traverse = 0;
      int count = 0;
      while(true){
        if(grid.at(traverse).get_codeX() == grid.at(i).get_codeX() + count
        && grid.at(traverse).get_codeY() == grid.at(i).get_codeY()){
          if(grid.at(traverse).get_isSelected() && grid.at(traverse).get_isChaos()){
            countXX++;
            count++;
          }
        }
        traverse++;
        if(traverse == size*size){
          break;
        }
      }
      while(countXX > 0){
        if(countXX >= 5){
          code = "5";
          return code;
        }
        if(countXX == 4){
          if((grid.at(i + count).get_codeX()) % size == 0){
            code = "X" + to_string(grid.at(i - 1).get_codeX()) + grid.at(i).get_codeY();
          }
          else{
            code = "X" + to_string(grid.at(i + count).get_codeX()) + grid.at(i).get_codeY();
          }
          return code;
        }
        else if(countXX == 3){
          if(grid.at(i).get_codeX() == 0){
            code = "X" + to_string(grid.at(i + count).get_codeX()) + grid.at(i).get_codeY(); 
          }
          else{
            code = "X" + to_string(grid.at(i - 1).get_codeX()) + grid.at(i).get_codeY(); 
          }
        }
        countXX--;
      }
      countXX = 0;
      count = 0;
    }
  }
  return code;
}

string check_boardXO(){
  int countXO = 0;
  string code = "";
  for(int i = 0; i < size * size -1;i++){
    if(grid.at(i).get_isSelected() && !grid.at(i).get_isChaos()){
      int traverse = 0;
      int count = 0;
      while(true){
        if(grid.at(traverse).get_codeX() == grid.at(i).get_codeX() + count
        && grid.at(traverse).get_codeY() == grid.at(i).get_codeY()){
          if(grid.at(traverse).get_isSelected() && !grid.at(traverse).get_isChaos()){
            countXO++;
            count++;
          }
        }
        traverse++;
        if(traverse == size*size){
          break;
        }
      }
      while(countXO > 0){
        if(countXO >= 5){
          code = "5";
          return code;
        }
        if(countXO == 4){
          if((grid.at(i + count).get_codeX()) % size == 0){
            code = "O" + to_string(grid.at(i - 1).get_codeX()) + grid.at(i).get_codeY();
          }
          else{
            code = "O" + to_string(grid.at(i + count).get_codeX()) + grid.at(i).get_codeY();
          }
          return code;
        }
        else if(countXO == 3){
          if(grid.at(i).get_codeX() == 0){
            code = "O" + to_string(grid.at(i + count).get_codeX()) + grid.at(i).get_codeY(); 
          }
          else{
            code = "O" + to_string(grid.at(i - 1).get_codeX()) + grid.at(i).get_codeY(); 
          }
        }
        countXO--;
      }
      countXO = 0;
      count = 0;
    }
  }
  return code;
}

string check_boardYX(){
  int countYX = 0;
  string code = "";
  for(int i = 0; i < size * size -1;i++){
    if(grid.at(i).get_isSelected() && grid.at(i).get_isChaos()){
      int traverse = 0;
      int count = 0;
      while(true){
        if(grid.at(traverse).get_codeY() == grid.at(i).get_codeY() + count
      && grid.at(traverse).get_codeX() == grid.at(i).get_codeX()){
          if(grid.at(traverse).get_isSelected() && grid.at(traverse).get_isChaos()){
            countYX++;
            count++;
          }
        }
        traverse++;
        if(traverse == size*size){
          break;
        }
      }
      while(countYX > 0){
        if(countYX >= 5){
          code = "5";
          return code;
        }
        if(countYX == 4){
          if((grid.at(i + count).get_codeY()) == 97 + size){
            code = "X" + to_string(grid.at(i).get_codeX()) + grid.at(i - size).get_codeY();
          }
          else{
            code = "X" + to_string(grid.at(i).get_codeX()) + grid.at(i + (4*size)).get_codeY();
          }
          return code;
        }
        else if(countYX == 3){
          if(grid.at(i).get_codeY() == 97){
            code = "X" + to_string(grid.at(i).get_codeX()) + grid.at(i + (3 * size)).get_codeY(); 
          }
          else{
            code = "X" + to_string(grid.at(i).get_codeX()) + grid.at(i - size).get_codeY(); 
          }
        }
        countYX--;
      }
      countYX = 0;
      count = 0;
    }
  }
  return code;
}

string check_boardYO(){
  int countYO = 0;
  string code = "";
  for(int i = 0; i < size * size -1;i++){
    if(grid.at(i).get_isSelected() && !grid.at(i).get_isChaos()){
      int traverse = 0;
      int count = 0;
      while(true){
        if(grid.at(traverse).get_codeY() == grid.at(i).get_codeY() + count
      && grid.at(traverse).get_codeX() == grid.at(i).get_codeX()){
          if(grid.at(traverse).get_isSelected() && !grid.at(traverse).get_isChaos()){
            countYO++;
            count++;
          }
        }
        traverse++;
        if(traverse == size*size){
          break;
        }
      }
      while(countYO > 0){
        if(countYO >= 5){
          code = "5";
          return code;
        }
        if(countYO == 4){
          if((grid.at(i + count).get_codeY()) == 97 + size){
            code = "O" + to_string(grid.at(i).get_codeX()) + grid.at(i - size).get_codeY();
          }
          else{
            code = "O" + to_string(grid.at(i).get_codeX()) + grid.at(i + (4*size)).get_codeY();
          }
          return code;
        }
        else if(countYO == 3){
          if(grid.at(i).get_codeY() == 97){
            code = "O" + to_string(grid.at(i).get_codeX()) + grid.at(i + (3 * size)).get_codeY(); 
          }
          else{
            code = "O" + to_string(grid.at(i).get_codeX()) + grid.at(i - size).get_codeY(); 
          }
        }
        countYO--;
      }
      countYO = 0;
      count = 0;
    }
  }
  return code;
}

string check_boardDX(){
  int countDX = 0;
  string code = "";
  for(int i = 0; i < size * size -1;i++){
    if(grid.at(i).get_isSelected() && grid.at(i).get_isChaos()){
      int traverse = 0;
      int count = 0;
      while(true){
        if(grid.at(traverse).get_codeX() == grid.at(i).get_codeX() + count
      && grid.at(traverse).get_codeY() == grid.at(i).get_codeY() + count){
          if(grid.at(traverse).get_isSelected() && grid.at(traverse).get_isChaos()){
            countDX++;
            count++;
          }
        }
        traverse++;
        if(traverse == size*size){
          break;
        }
      }
      while(countDX > 0){
        if(countDX >= 5){
          code = "5";
          return code;
        }
        if(countDX == 4){
          if((grid.at(i + size * count + count).get_codeY()) == 97 + size || grid.at(i + size * count + count).get_codeX() == size 
          || grid.at(i + size * count + count).get_codeX() == 0){
            code = "X" + to_string(grid.at(i - size * count - count).get_codeX()) + grid.at(i - size * count - count).get_codeY();
          }
          else{
            code = "X" + to_string(grid.at(i + size * count + count).get_codeX()) + grid.at(i + size * count + count).get_codeY();
          }
          return code;
        }
        else if(countDX == 3){
          if(grid.at(i).get_codeY() == 97 || grid.at(i).get_codeX() == 0 || grid.at(i).get_codeX() == size){
            code = "X" + to_string(grid.at(i + size * count + count).get_codeX()) + grid.at(i + size * count + count).get_codeY(); 
          }
          else{
            code = "X" + to_string(grid.at(i - size * count - count).get_codeX()) + grid.at(i - size * count - count).get_codeY(); 
          }
        }
        countDX--;
      }
      countDX = 0;
      count = 0;
    }
  }
  return code;
}

string check_boardDO(){
  int countDO = 0;
  string code = "";
  for(int i = 0; i < size * size -1;i++){
    if(grid.at(i).get_isSelected() && !grid.at(i).get_isChaos()){
      int traverse = 0;
      int count = 0;
      while(true){
        if(grid.at(traverse).get_codeX() == grid.at(i).get_codeX() + count
      && grid.at(traverse).get_codeY() == grid.at(i).get_codeY() + count){
          if(grid.at(traverse).get_isSelected() && !grid.at(traverse).get_isChaos()){
            countDO++;
            count++;
          }
        }
        traverse++;
        if(traverse == size*size){
          break;
        }
      }
      while(countDO > 0){
        if(countDO >= 5){
          code = "5";
          return code;
        }
        if(countDO == 4){
          if((grid.at(i + size * count + count).get_codeY()) == 97 + size || grid.at(i + size * count + count).get_codeX() == size 
          || grid.at(i + size * count + count).get_codeX() == 0){
            code = "O" + to_string(grid.at(i - size * count - count).get_codeX()) + grid.at(i - size * count - count).get_codeY();
          }
          else{
            code = "O" + to_string(grid.at(i + size * count + count).get_codeX()) + grid.at(i + size * count + count).get_codeY();
          }
          return code;
        }
        else if(countDO == 3){
          if(grid.at(i).get_codeY() == 97 || grid.at(i).get_codeX() == 0 || grid.at(i).get_codeX() == size){
            code = "O" + to_string(grid.at(i + size * count + count).get_codeX()) + grid.at(i + size * count + count).get_codeY(); 
          }
          else{
            code = "O" + to_string(grid.at(i - size * count - count).get_codeX()) + grid.at(i - size * count - count).get_codeY(); 
          }
        }
        countDO--;
      }
      countDO = 0;
      count = 0;
    }
  }
  return code;
}

string check_boardDX2(){
  int countDX2 = 0;
  string code = "";
  for(int i = 0; i < size * size -1;i++){
    if(grid.at(i).get_isSelected() && grid.at(i).get_isChaos()){
      int traverse = 0;
      int count = 0;
      while(true){
        if(grid.at(traverse).get_codeX() == grid.at(i).get_codeX() - count
      && grid.at(traverse).get_codeY() == grid.at(i).get_codeY() + count){
          if(grid.at(traverse).get_isSelected() && grid.at(traverse).get_isChaos()){
            countDX2++;
            count++;
          }
        }
        traverse++;
        if(traverse == size*size){
          break;
        }
      }
      while(countDX2 > 0){
        if(countDX2 >= 5){
          code = "5";
          return code;
        }
        if(countDX2 == 4){
          if((grid.at(i + size * (count-1) - count +1).get_codeY()) == 97 + size || grid.at(i + size * (count-1) - count +1).get_codeX() == 0){
            code = "X" + to_string(grid.at(i - size + 1).get_codeX()) + grid.at(i - size + 1).get_codeY();
          }
          else{
            code = "X" + to_string(grid.at(i + size * count - count).get_codeX()) + grid.at(i + size * count - count).get_codeY();
          }
          return code;
        }
        else if(countDX2 == 3){
          if(grid.at(i).get_codeY() == 97 || grid.at(i).get_codeX() == size){
            code = "X" + to_string(grid.at(i + size * count - count).get_codeX()) + grid.at(i + size * count-1 - count).get_codeY(); 
          }
          else{
            code = "X" + to_string(grid.at(i - size + 1).get_codeX()) + grid.at(i - size + 1).get_codeY(); 
          }
        }

        countDX2--;
      }
      countDX2 = 0;
      count = 0;
    }
  }
  return code;
}

string check_boardDO2(){
  int countDO2 = 0;
  string code = "";
  for(int i = 0; i < size * size -1;i++){
    if(grid.at(i).get_isSelected() && !grid.at(i).get_isChaos()){
      int traverse = 0;
      int count = 0;
      while(true){
        if(grid.at(traverse).get_codeX() == grid.at(i).get_codeX() - count
      && grid.at(traverse).get_codeY() == grid.at(i).get_codeY() + count){
          if(grid.at(traverse).get_isSelected() && !grid.at(traverse).get_isChaos()){
            countDO2++;
            count++;
          }
        }
        traverse++;
        if(traverse == size*size){
          break;
        }
      }
      while(countDO2 > 0){
        if(countDO2 >= 5){
          code = "5";
          return code;
        }
        if(countDO2 == 4){
          if((grid.at(i + size * (count-1) - count +1).get_codeY()) == 97 + size || grid.at(i + size * (count-1) - count +1).get_codeX() == size 
          || grid.at(i + size * (count-1) - count +1).get_codeX() == 0){
            code = "O" + to_string(grid.at(i - size + 1).get_codeX()) + grid.at(i - size + 1).get_codeY();
          }
          else{
            code = "O" + to_string(grid.at(i + size * count - count).get_codeX()) + grid.at(i + size * count - count).get_codeY();
          }
          return code;
        }
        else if(countDO2 == 3){
          if(grid.at(i).get_codeY() == 97 || grid.at(i).get_codeX() == 0 || grid.at(i).get_codeX() == size){
            code = "O" + to_string(grid.at(i + size * (count-1) - count + 1).get_codeX()) + grid.at(i + size * (count-1) - count +1).get_codeY(); 
          }
          else{
            code = "O" + to_string(grid.at(i - size + 1).get_codeX()) + grid.at(i - size + 1).get_codeY(); 
          }
        }
        countDO2--;
      }
      countDO2 = 0;
      count = 0;
    }
  }
  return code;
}

void set_board(){
  for(char i = 97; i < size + 97; i++){
    for(int o = 0; o < size; o++){
      cords a;
      a.set_codeX(o);
      a.set_codeY(i);
      a.set_isSelected(0);
      a.set_isChaos(0);
      grid.push_back(a);
    }
  }
}

void clear_board(){
  for(int i = 0; i < size*size; i++){
    grid.at(i).set_isSelected(0);
    grid.at(i).set_isChaos(0);
  }
}

void random_move(){
  srand(time(nullptr));
  while(true){
    int x = (rand() % (size * size + 1));
    for(int i = 0; i < size *size; i++){
      if(i == x && !grid.at(i).get_isSelected()){
        if(x > size*size/2){
          grid.at(i).set_isChaos(0);
          grid.at(i).set_isSelected(1);
        }
        else{
          grid.at(i).set_isChaos(1);
          grid.at(i).set_isSelected(1);
        }
        return;
      }
    }
  }
}

bool checkChaos(){
  for(int i =0; i < size*size; i++){
    if(!grid.at(i).get_isSelected()){
      return false;
    }
  }
  return true;
}

void print_board(){
  for(int i = 0; i < size; i++){
    if(i == 0){cout << " ";}
    cout << "  " << i;
  }
  cout << endl;
  for(int i = 0; i < size * size; i++){
    if(i % size == 0){
      if(i != 0){
        cout << endl;
      }
      cout << char(i/size + 97);
    }
    if(!grid.at(i).get_isSelected()){
      cout <<  "  *";
    }
    if(grid.at(i).get_isSelected() && grid.at(i).get_isChaos()){
      cout << "  X";
    }
    if(grid.at(i).get_isSelected() && !grid.at(i).get_isChaos()){
      cout << "  O";
    }
  }
  cout << endl;
}

// make it so that the person can edit and their move by searching for code and changing variables

void compute_move(string str){
  if(str.at(0) == 'X'){
    for(int i = 0; i < size * size;i++){
      if(stoi(str.substr(1, 1)) == grid.at(i).get_codeX() && str[2] == grid.at(i).get_codeY()){
        grid.at(i).set_isSelected(1);
        grid.at(i).set_isChaos(0);
      }
    }
  }
  else{
    for(int i = 0; i < size * size;i++){
      if(stoi(str.substr(1, 1)) == grid.at(i).get_codeX() && str[2] == grid.at(i).get_codeY()){
        grid.at(i).set_isSelected(1);
        grid.at(i).set_isChaos(1);
      }
    }
  }
}

bool computer_move(string move){
    for(int i = 0; i < size*size; i++){
      if(check_boardXX() != ""){
        if(check_boardXX() == "5"){return true;}
        if(stoi(check_boardXX().substr(1, 1)) == grid.at(i).get_codeX() && check_boardXX()[2] == grid.at(i).get_codeY()){
          if(!grid.at(i).get_isSelected()){
            compute_move(check_boardXX());
            return false;
          }
        }
      }
      if(check_boardXO() != ""){
        if(check_boardXO() == "5"){return true;}
        if(stoi(check_boardXO().substr(1, 1)) == grid.at(i).get_codeX() && check_boardXO()[2] == grid.at(i).get_codeY()){
          if(!grid.at(i).get_isSelected()){
            compute_move(check_boardXO());
            return false;
          }
        }
      }
      if(check_boardYX() != ""){
        if(check_boardYX() == "5"){return true;}
        if(stoi(check_boardYX().substr(1, 1)) == grid.at(i).get_codeX() && check_boardYX()[2] == grid.at(i).get_codeY()){
          if(!grid.at(i).get_isSelected()){
            compute_move(check_boardYX());
            return false;
          }
        }
      }
      if(check_boardYO() != ""){
        if(check_boardYO() == "5"){return true;}
        if(stoi(check_boardYO().substr(1, 1)) == grid.at(i).get_codeX() && check_boardYO()[2] == grid.at(i).get_codeY()){
          if(!grid.at(i).get_isSelected()){
            compute_move(check_boardYO());
            return false;
          }
        }
      }
      if(check_boardDX() != ""){
        if(check_boardDX() == "5"){return true;}
        if(stoi(check_boardDX().substr(1, 1)) == grid.at(i).get_codeX() && check_boardDX()[2] == grid.at(i).get_codeY()){
          if(!grid.at(i).get_isSelected()){
            compute_move(check_boardDX());
            return false;
          }
        }
      }
      if(check_boardDO() != ""){
        if(check_boardDO() == "5"){return true;}
        if(stoi(check_boardDO().substr(1, 1)) == grid.at(i).get_codeX() && check_boardDO()[2] == grid.at(i).get_codeY()){
          if(!grid.at(i).get_isSelected()){
            compute_move(check_boardDO());
            return false;
          }
        }
      }
      if(check_boardDX2() != ""){
        if(check_boardDX2() == "5"){return true;}
        if(stoi(check_boardDX2().substr(1, 1)) == grid.at(i).get_codeX() && check_boardDX2()[2] == grid.at(i).get_codeY()){
          if(!grid.at(i).get_isSelected()){
            compute_move(check_boardDX2());
            return false;
          }
        }
      }
      if(check_boardDO2() != ""){
        if(check_boardDO2() == "5"){return true;}
        if(stoi(check_boardDO2().substr(1, 1)) == grid.at(i).get_codeX() && check_boardDO2()[2] == grid.at(i).get_codeY()){
          if(!grid.at(i).get_isSelected()){
            compute_move(check_boardDO2());
            return false;
          }
        }
      }
    }
  if(!(move[1] < 97 || move[1] > 97 +size
  ||stoi(move.substr(0,1)) < 0 || stoi(move.substr(0,1)) > size - 1)){
    random_move();}
  return false;
  }
};

int main()
{
  board b;
  string size;
  string move;
  string response;
  bool chaosWon = false;
  cout << "Order versus Chaos ...\n";
  cout << "The instructions to playing order vs chaos" << endl
  << "1. Pick board size (6 - 9)" << endl
  << "2. Enter your move" << endl
  << "3. Type \"exit\" if you would like to resign" << endl
  << "The objective of this game is to either get 5 x's or o's in a row, column or diaganol" << endl
  << "if you are order or try to prevent that from happenning if you are chaos. Good Luck" << endl;
  cout << "Enter size of board" << endl;
  while(true){
    cin >> size;
    if(size == "exit"){return 1;}
    if(stoi(size) > 5 && stoi(size) < 9){
      break;
    }
    cout << "Size of board invalid" << endl;
  }
  while(true){
    int chaosOrder = (rand() % (2));
    if(chaosOrder == 1){
      cout << "You are Chaos" << endl;
    }else{
      cout<< "You are Order" << endl;
    }
    b.clear_board();
    b.set_size(stoi(size));
    b.set_board();
    while(true){
      b.print_board();
      cout << "Enter your move e.g 1bX" << endl;
      cin >> move;
      if(move == "exit"){return 1;}
      b.player_move(move);
      if(chaosOrder == 0){
        if(b.computer_move(move)){
            break;
        }
      }else{
        if(b.check_boardXX() == "5"){break;}
        if(b.check_boardXO() == "5"){break;}
        if(b.check_boardYX() == "5"){break;}
        if(b.check_boardYO() == "5"){break;}
        if(b.check_boardDX() == "5"){break;}
        if(b.check_boardDO() == "5"){break;}
        if(b.check_boardDX2() == "5"){break;}
        if(b.check_boardDO2() == "5"){break;}
        b.random_move();
      }
      if(b.checkChaos()){
        chaosWon = true;
        break;
      }
      cout << endl; 
    }
    b.print_board();
    if(chaosWon){
      cout << "***CHAOS WON***" << endl;
    }else{
      cout << "***ORDER WON***" << endl;
    }
    cout << "Would you like to play again? (y/n)" << endl;
    while(true){
      cin >> response;
      if(response == "n"){return 0;}
      if(response == "y"){break;}
    }
  }
} // main


/*

Assignment 5 Report
===================

Description of Computers Playing Strategy
-----------------------------------------
The computer detects when there are 3 X's or O's in a row and puts a X or O on either end to block it
the computer also detects when there are 4 X's or O's in a row and puts a X or O to block it
the computer does this by using a function that counts and returns a code (for example "X4a"
that tells another function if they need to block, where to block and also to use X or O
The computer has no strategy when it is order, it uses random moves.
(Discuss the strategy your computer player uses to play the game.)


Extra Features
--------------
none
(Describe all extra features your program has that were not required by the
assignment; if there are no extra features, then say that.)


Known Bugs and Limitations
--------------------------
- the program sometimes crashes when the bored is close to being filled up
- the program sometimes has trouble checking the validity of moves
- if the computer is the one that makes the 5 in the row then the win will be detect one turn after
(If your program is perfect and unlimited, then say so!)


Acknowledgements of All Help
----------------------------

(Cite all websites, books, people, etc. that you got help from, including what
sort of help you got. Each citation should be about 1 to 2 lines long.)

*/
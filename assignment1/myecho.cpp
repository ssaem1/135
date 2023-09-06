// myecho.cpp

/////////////////////////////////////////////////////////////////////////
//
// Student Info
// ------------
//
// Name         : Yu Shan <full name, exactly as it appears on your SFU id card> 
// Student ID # : 301573835 <full SFU student number> 
// SFU Email    : sam_shan@sfu.ca <full SFU email address>
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
//
// Notes to the Marker
// -------------------
//
// Tell us something about the assignment you're submitting, for example:
// - are there are any known bugs?
// - are there any missing features?
// - were there any parts you found particularly challenging?
// - did you use any outside sources of help (fully cite them if you did)?
// - what editor and programming tools did you use?
//
/////////////////////////////////////////////////////////////////////////

#include <iostream>    // Do not #include any other files.
#include <vector>      //
#include <string>      // You do not need to use functions from all these
#include <algorithm>   // #includes.
#include <cassert>     //

using namespace std;

string quote(string s){
    bool isWordQuotes = true;
    for(int i = 0; i < s.length(); i++){
        if(s.at(i) != '\"'){
            isWordQuotes = false;
        }
    }
    if(s[0] == '\"' && s[s.length() - 1] == '\"' && !isWordQuotes){
        return s;
    }
    else{
        return "\"" + s + "\"";
    }
}

string quoteWord(string s){
        return "\"" + s + "\"";
}

void quote_test() {
    cout << "testing quote ... ";
    assert(quote("a"      ) == "\"a\""   );
    assert(quote("ab"     ) == "\"ab\""  );
    assert(quote("\"a\""  ) == "\"a\""   );
    assert(quote("\"ab\"" ) == "\"ab\""  );
    assert(quote("a\"b"   ) == "\"a\"b\"");
    assert(quote("\"a"    ) == "\"\"a\"" );
    assert(quote("a\""    ) == "\"a\"\"" );
    assert(quote(""       ) == "\"\""    );
    assert(quote("\""     ) == "\"\"\""  );
    cout << "all tests passed\n";
}


string to_string(const vector<string>& v) {
    string word = "{";
    for(int i = 0; i < v.size(); i++){
        if(i != 0){
            word += ", ";
        }
        word += "\"" + v.at(i) + "\"";     
    }
        word += "}";
    return word;
}

ostream& operator<<(ostream& out, 
                    const vector<string>& v) 
{
    return out << to_string(v);
}

void test_to_string(){
    cout << "testing quote ... ";
    assert(to_string(vector<string>{}) == "{}");
    assert(to_string(vector<string>{"a"}) == "{\"a\"}");
    assert(to_string(vector<string>{"a", "b"}) == "{\"a\", \"b\"}");
    assert(to_string(vector<string>{"a", "b", "c"}) == "{\"a\", \"b\", \"c\"}");
    cout << "all tests passed\n";
}

string reverse_words(vector<string> words){
    string reverseWord;
    for(int i = words.size() - 1; i >= 0; i--){
        reverseWord += words.at(i);
        if (i != 0 && i != 1){
            reverseWord += ' ';
        }
    }
    return reverseWord;
}

void display_help(){
    cout << "\n Usage: ./myecho [-runtests|-(hrs)] [string ...]"
         << "\n   -runtests: run the tests"
         << "\n             over-rides single-character flags"
         << "\n         -h: print this help message"
         << "\n             over-rides other single-character flags"
         << "\n         -r: print the strings in reverse order"
         << "\n         -s: no space between arguments"
         << "\n         -q: quote the printed results"
         << "\n   -rs, -sr: no space between arguments, in reverse order"
         << "\n"
         << "\n  Repeated single-character flags are allowed (and are ignored)."
         << "\n  Unknown flags cause an error. \n"
         << "\n  Examples: \n    ❯ ./myecho -q \n    \"\" \n    ❯ ./myecho x y z"
         << "\n    x y z \n    ❯ ./myecho -q x y z \n    \"x y z\" \n    ❯ ./myecho -sr x y z"
         << "\n    zyx \n    ❯ ./myecho -h \n";
}

string word_space_remover(string word){
    string temp = "";
    int i = 0;
    while(i < word.size()){
        if(word.at(i) != ' '){
            temp += word.at(i);
        }
        i++;
    }
    return temp;
}

void select_flags(string word, vector<string> words){   
    string finalWord = "";
    if(word.size() == 0){
        return;
    }
    if(words.at(0) == "-runtests"){
        quote_test();
        test_to_string();
        return;
    }
    bool checkedOnceQ = false;
    bool checkedOnceR = false;
    bool checkedOnceS = false;
    bool checkedOnceH = false; 
    if(word.at(0) != '-'){
        cout << word << endl;
        return;
    }
    else{       
        words.at(0) = "";
        for(int o = 1; o < words.size(); o++){
            finalWord += words.at(o);
            if (o != words.size() - 1){
                finalWord += ' ';
            }
        }
        for(int i = 1; i < word.size(); i++){
            if(word.at(i) == 'h'){
                checkedOnceH = true;
            }
            else if (word.at(i) == 'r'){
                if(checkedOnceQ == true){
                    finalWord = reverse_words(words);
                    finalWord = quoteWord(finalWord);  
                    checkedOnceR = true;                
                }
                if(checkedOnceS == true){
                    finalWord = reverse_words(words);
                    finalWord = word_space_remover(finalWord);  
                    checkedOnceR = true;                
                }
                if(checkedOnceQ == true && checkedOnceS == true){
                    finalWord = reverse_words(words);
                    finalWord = quote(word_space_remover(finalWord)); 
                    checkedOnceR = true;          
                }
                else if(checkedOnceR != true){
                    finalWord = reverse_words(words);
                }                
                checkedOnceR = true;
            }
            else if (word.at(i) == 'q'){
                if(checkedOnceQ != true){
                    finalWord = quoteWord(finalWord);
                }
                checkedOnceQ = true;
            }           
            else if (word.at(i) == 's'){
                if(checkedOnceS != true){
                    finalWord = word_space_remover(finalWord);
                }
                checkedOnceS = true;
            } 
            else if (word.at(i) == ' '){
                break;
            } 
            else{
                cout << "Error, invalid flag: " << word.at(i) << endl;
                display_help();
                break;
            }
        }
        if(checkedOnceH == true){
            display_help();
            return;
        }
            cout << finalWord << endl;
    }
}

int main(int argc, char *argv[]) {
    vector<string> words;
    string word = "";
    for (int i = 1; i < argc; i++) { 
        word += argv[i];
        word += " ";;
        words.push_back(argv[i]);
        }
    select_flags(word, words);
}   // main
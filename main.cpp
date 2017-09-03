#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <iomanip>

using namespace std;

vector<string> split(const string& s, const char& delim) {
  vector<string> elems;
  stringstream ss(s);
  string item;
  while(getline(ss, item, delim))
    if(!item.empty())
      elems.push_back(item);
  return elems;
}

int main(void) {
  vector<string> sentence;
  vector<string> temp;
  vector<int> nlength;
  ifstream ifs("data.txt");
  string str = "";
  string line = "";
  string t = "";
  string command_title = "FirstDB Test -> ";
  bool during = false;
  if(ifs.fail())
    cerr << "not found data.txt." << endl;
  do {
    line.clear();
    do {
      t.clear();
      if(during)
        line += ' ';
      cout << command_title;
      getline(cin, t);
      line += t;
      during = true;
    } while(line[line.length() - 1] != ';' && line != "quit" && line != "exit");
    during = false;
    sentence = split(line, ' ');
    if(sentence[0] == "select") {
      while(getline(ifs, str)) {
        temp = split(str, ',');
        if(nlength.empty())
          for(int i = 0; i < temp.size(); i++)
            nlength.push_back(temp[i].length());
        else
          for(int i = 0, j = 0; i < nlength.size(); i++, j++)
            if(nlength[i] < temp[j].length())
              nlength[i] = temp[j].length();
      }
      ifstream ifs("data.txt");
      while(getline(ifs, str)) {
        temp = split(str, ',');
        if(temp[0] == "key") {
          for(int i = 1; i <= 3; i++)
            if(i != 3)
              cout << setw(nlength[i] + 2) << temp[i] << '|';
            else
              cout << setw(nlength[i] + 2) << temp[i] << ' ';
          cout << endl;
          for(int i = 1; i <= 3; i++) {
            for(int j = 0; j < nlength[i] + 2; j++)
              cout << "-";
            if(i != 3)
              cout << "+";
          }
          cout << endl;
        }
        else if(temp[0] == "data") {
          for(int i = 1; i <= 3; i++)
            if(i != 3)
              cout << setw(nlength[i] + 2) << right << temp[i] << '|';
            else
              cout << setw(nlength[i] + 2) << right << temp[i];
          cout << endl;
        }
      }
      cout << endl;
    }
    else if(sentence[0] == "exit" || sentence[0] == "quit")
      cout << "bye." << endl;
    else
      cout << "no command." << endl;
  } while(line != "quit" && line != "exit");
  return 0;
}

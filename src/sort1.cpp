/*
 * Lame one using list::sort
 * This is stable! (I thought it wasn't earlier but ok)
 */


// THIS IS THE PROVIDED CODE FOR PROGRAM #2, DSA 1, FALL 2018

#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <cstring>
#include <cctype>
#include <cstdlib>

using namespace std;

// A simple class; each object holds four public fields
class Data {
public:
  unsigned int val1;
  unsigned int val2;
  char val3;
  string val4;
};

// Load the data from a specified input file
void loadDataList(list<Data *> &l, const string &filename) {

  ifstream input(filename.c_str());
  if (!input) {
    cerr << "Error: could not open " << filename << endl;
    exit(1);
  }

  // The first line indicates the size
  string line;
  getline(input, line);
  stringstream ss(line);
  int size;
  ss >> size;

  // Load the data
  for (int i = 0; i < size; i++) {
    getline(input, line);
    stringstream ss2(line);
    Data *pData = new Data();
    ss2 >> pData->val1 >> pData->val2 >> pData->val3 >> pData->val4;
    l.push_back(pData);
  }

  input.close();
}

// Output the data to a specified output file
void writeDataList(const list<Data *> &l, const string &filename) {

  ofstream output(filename.c_str());
  if (!output) {
    cerr << "Error: could not open " << filename << endl;
    exit(1);
  }

  // Write the size first
  int size = l.size();
  output << size << endl;

  // Write the data
  for (list<Data *>::const_iterator ipD = l.begin(); ipD != l.end(); ipD++) {
    output << (*ipD)->val1 << " " 
           << (*ipD)->val2 << " " 
           << (*ipD)->val3 << " " 
           << (*ipD)->val4 << endl;
  }

  output.close();
}

// Sort the data according to a specified field
// (Implementation of this function will be later in this file)
void sortDataList(list<Data *> &, int field);

// The main function calls routines to get the data, sort the data,
// and output the data. The sort is timed according to CPU time.
int main() {
  string filename;
  cout << "Enter name of input file: ";
  cin >> filename;
  list<Data *> theList;
  loadDataList(theList, filename);

  cout << "Data loaded.  Executing sort..." << endl;

  int field = 0;
  cout << "Enter an integer from 1 - 4, representing field to sort: ";
  try {
    cin >> field;
    if (field < 1 || field > 4) {
      cerr << "Error: invalid field" << endl;
      exit(1);
    }
  }
  catch (...) {
    cerr << "Error: invalid field" << endl;
    exit(1);
  }
    
  clock_t t1 = clock();
  sortDataList(theList, field);
  clock_t t2 = clock();
  double timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;

  cout << "Sort finished. CPU time was " << timeDiff << " seconds." << endl;

  cout << "Enter name of output file: ";
  cin >> filename;
  writeDataList(theList, filename);

  return 0;
}

// -------------------------------------------------
// YOU MAY NOT CHANGE OR ADD ANY CODE ABOVE HERE !!!
// -------------------------------------------------

// You may add global variables, functions, and/or
// class defintions here if you wish.

bool cmp2(const Data *a, const Data *b) {
  return a->val2 < b->val2;
}
bool cmp3(const Data *a, const Data *b) {
  return a->val3 < b->val3;
}
bool cmp4(const Data *a, const Data *b) {
  return b->val4.compare(a->val4) > 0;
}

void sortDataList(list<Data *> &l, int field) {
  switch(field) {
    case 1:
      {
        int pos_ind = 0, ind, min_val, check_val;
        list<Data *>::iterator pos_iter = l.begin(),
                               end_iter = l.end(),
                               check_iter,
                               min_iter;
        while(pos_iter != end_iter) {
          check_iter = pos_iter;
          min_iter = pos_iter;
          min_val = 10000000;

          // 18 or 19 or 20?
          for(ind = 0; ind < 18 && check_iter != end_iter; ind++, check_iter++) {
            check_val = (*check_iter)->val1;
            if(check_val < min_val) {
              min_val = check_val;
              min_iter = check_iter;
            }
          }

          if(min_iter != pos_iter) {
            l.insert(pos_iter, *min_iter);
            l.erase(min_iter);
            pos_iter--;
          }

          pos_iter++;
          pos_ind++;
        }
      }
      break;
    case 2:
      l.sort(cmp2);
      break;
    case 3:
      l.sort(cmp3);
      break;
    case 4:
      l.sort(cmp4);
      break;
  }
}

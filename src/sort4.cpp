/*
 * Radix sort for val4
 * Also contains sort for val1 (selection) and val3 (also radix)
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

void rrSort(Data *[], int, int, int);

void sortDataList(list<Data *> &l, int field) {
  switch(field) {
    case 1:
      {
        int pos_ind = 0, ind, check_val, pos_val, min_val;
        list<Data *>::iterator frame_iter,
                               insert_iter,
                               next_pos_iter = l.begin(),
                               pos_iter,
                               end_iter = l.end(),
                               check_iter;
        while(next_pos_iter != end_iter) {
          pos_iter = next_pos_iter;

          check_iter = pos_iter;
          check_iter++;

          pos_val = (*pos_iter)->val1;
          min_val = pos_val;

          for(ind = 0; ind < 19 && check_iter != end_iter; ind++) {
            check_val = (*check_iter)->val1;

            if(check_val <= pos_val) {
              if(check_val == pos_val) {
                next_pos_iter++;
                insert_iter = l.insert(next_pos_iter, *check_iter);

                next_pos_iter = insert_iter;
              } else {
                frame_iter = pos_iter;
                while(check_val >= (*frame_iter)->val1) {
                  frame_iter++;
                }
                insert_iter = l.insert(frame_iter, *check_iter);

                if(check_val < min_val) {
                  min_val = check_val;
                  pos_iter--;
                }
              }

              check_iter = l.erase(check_iter);
              
            } else {
              check_iter++;
            }
          }

          if(check_val > 999000) end_iter = l.end();

          ++next_pos_iter;
        }
      }
      break;
    case 2:
      {
      }
      break;
    case 3:
      {
        int width = 94,
              height = 10620 * 5/4,
              bin_counts[width],
              i,
              j;
        char c;
        static Data *chars[94][10620 * 5/4];
        memset(bin_counts, 0, sizeof(int) * width);
        
        list<Data *>::iterator iter,
                               end_iter = l.end();

        for(iter = l.begin(); iter != end_iter; iter++) {
          c = (*iter)->val3 - 33;
          chars[c][bin_counts[c]++] = *iter;
        }

        for(i = 0, iter = l.begin(); i < width; i++) {
          for(j = 0; j < bin_counts[i]; j++) {
            *iter++ = chars[i][j];
          }
        }
      }
      break;
    case 4:
      {
        int width = 94,
            height = 10620 * 5/4,
            bin_counts[width],
            i, j, k;
        char c;
        static Data *chars[94][10620 * 5/4];

        list<Data *>::iterator iter,
                               end_iter = l.end();

        memset(bin_counts, 0, sizeof(int) * width);
        for(iter = l.begin(); iter != end_iter; iter++) {
          c = (*iter)->val4[0] - 33;
          chars[c][bin_counts[c]++] = *iter;
        }

        for(i = 0, iter = l.begin(); i < width; i++) {
          rrSort(chars[i], 0, bin_counts[i], 1);
          
          for(j = 0; j < bin_counts[i]; j++) {
            *iter++ = chars[i][j];
          }
        }
      }
      break;
  }

}

/*
 * Recursive radix sort
 */
void rrSort(Data *array[], int start, int end, int radix) {
  int width = 94,
      height = (end - start) * 2 / 94 + 10,
      bin_counts[width],
      i, j, ind;
  char c;
  Data *chars[width][height];

  memset(bin_counts, 0, sizeof(int) * width);
  for(i = start; i < end; i++) {
    c = array[i]->val4[radix] - 33;
    chars[c][bin_counts[c]++] = array[i];
  }
  
  for(i = 0, ind = start; i < width; i++) {
    if(radix < 5 && bin_counts[i] > 1) {
      rrSort(chars[i], 0, bin_counts[i], radix + 1);
    }

    for(j = 0; j < bin_counts[i]; j++, ind++) {
      array[ind] = chars[i][j];
    }
  }
}

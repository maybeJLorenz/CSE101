#define MAX_LINES 100
#define MAX_INTS 100

#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

// checks if a queen can be placed at position (row, col)
bool isSafe(const vector<int>& queens, int row, int col){
  for(int i = 0; i < row; ++i){
    if(queens[i] == col ||
       queens[i] - i == col - row ||
       queens[i] + i == col + row){
      return false;
    }
  }
  return true;
} // end of isSafe function


// solves n-queens iteratively and print one solution that
// contains all pre-existing queens
bool solveNQueens(int n, vector<pair<int, int>>& preQueens, vector<int>& solution){
  vector<int> queens(n, -1); // queens[i] indicates col position, index indicates row position

  int row = 0, col = 0;

  bool solutionFound = false; // will change to true if all preQueens are found

  // start of iterative algorithm that mimics recursion
  while(row < n && !solutionFound){

    // backtracking code
    if(col == n){
      if(row == 0){
        break;
      }
      --row;
      col = queens[row] + 1;
      queens[row] = -1;
      continue;
    }

    if(isSafe(queens, row, col)){
      queens[row] = col;
      if(row == n - 1){ // we found a solution

        // checking if all pre-existing queens are in this solution
        bool valid = true;
        for(const auto& pq : preQueens){
          if(queens[pq.first - 1] != pq.second - 1){
            valid = false;
            break;
          }
        }
        if(valid){
          solution = queens;
          solutionFound = true;
        }
        col = queens[row] + 1;
        queens[row] = -1;
        continue;
      }
      ++row;
      col = 0;
    }// end of isSafe statement
    else{
      ++col;
    }
  } // end of while loop

  return solutionFound;
} // end of solveNQueens function



// ======= beginning of int main() ========
int main(int argc, char *argv[]){

  FILE *infile;
  FILE *outfile;
  char line[MAX_LINES];
  int num;

  // initializing input file
  infile = fopen(argv[1], "r");
  if(infile == NULL){
    printf("Error opening input file.\n");
    return 1;
  }

  // initializing output file
  outfile = fopen(argv[2], "w");
  if(outfile == NULL){
    printf("Error opening output file.\n");
    return 0;
  }
  
  // reads each line until EOF
  while(fgets(line, sizeof(line), infile) != NULL){

    char *ptr = line;
    int n = 0;
    
    // getting the board size, reading the first int of the line
    if(n == 0){
      sscanf(line, "%d", &n);
      ptr += sprintf(ptr, "%d", n) + 1;
    }

    // vector to store all the pre-existing queens
    vector<pair<int, int>> preQueens;
    
    // beginning on the second int of the line, it reads every pair of 
    // numbers, the first number = row and second number = col. These will represent
    // our pre-existing queens
    while(sscanf(ptr, "%d", &num) == 1){
  
        preQueens.emplace_back(num, 0); // gets the row position
        ptr += sprintf(ptr, "%d", num) + 1;

        if(sscanf(ptr, "%d", &num) == 1){
          preQueens.back().second = num; // gets the col position
          ptr += sprintf(ptr, "%d", num) + 1;
        }
    }

    // creating a vector that will store our solution (if found)
    // it will be initialized as an empty vector
    vector<int> solution;

    if(solveNQueens(n, preQueens, solution)){
      
      for(int i = 0; i < n; ++i){
        int r = 0;
        bool isThereQueen = false;
        for(int j = 0; j < n; ++j){
          if(solution[i] == j){
            r++;
            isThereQueen = true;
          }
          else{
            if(!isThereQueen){
              r++;
            }
          }
        }
        fprintf(outfile, "%d %d ", i+1, r);

      }// end of outside for loop

    }
    else{
      fprintf(outfile, "No solution");
    }
    fprintf(outfile, "\n");
      
  } // end of reading each line while loop

  fclose(outfile);
  fclose(infile);
  return 0;

}
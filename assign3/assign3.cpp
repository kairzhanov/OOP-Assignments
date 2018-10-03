// Kairzhanov Damir 20152010

#include <iostream>
#include <cstdio>
#include <stdio.h>
#include <vector>
#include <string>
#include <cstddef>
#include <algorithm>
using namespace std;
// sorting by number of solved problems, penalty time and contestant number
bool sortFunction (const vector<int>& param1, const vector<int>& param2) {
    if (param1[1] == param2[1]) { // if number of solved problems is equal
        if (param1[2] == param2[2]) // if penalty time is equal
            return param1[0] < param2[0]; // sort by contestant number
        return param1[2] < param2[2]; // if penalty time is not equal, sort by penalty time
    }
    return param1[1] > param2[1]; // if everything okay, sort by solved problems
}
// checking if this problem was already solved
bool checkIfCorrect (int problem_number, int contestant , const vector< vector<int> > correct_problems) {
    for (int i = 0; i < correct_problems[contestant-1].size(); i++) {
        if (correct_problems[contestant-1][i] == problem_number) return true; // if yes, return true
    }
    return false; // if no, return false
}
// counting the number of incorrect solutions before
int checkHowMuchTimeWasIncorrect
        (int problem_number, int contestant, const vector< vector<int> > incorrect_problems) {
    int count = 0; // if not return 0
    for (int i = 0; i < incorrect_problems[contestant-1].size(); i++) {
        if (incorrect_problems[contestant - 1][i] == problem_number)
            count++;
    }
    return count;
}

int main()
{
    const int ROWS = 100; // number of contestants
    const int COLUMNS = 3; // number of elements, which we will store
    vector < vector<int> > scoreboard(ROWS, vector<int>(COLUMNS,0)); // 2D array for all contestants
    vector < vector<int> > correct_problems(ROWS, vector<int>()); // 2D array for correct problems
    vector < vector<int> > incorrect_problems(ROWS, vector<int>()); // 2D array for incorrect problems

    int n; // number of cases
    int contestant_number, problem_number, penalty_time;
    char status, line[40]; // status of problem, char to read line by line
    int count = 0; // counts the number of tests

    cin >> n; // reading the number of cases
    cin.ignore(); // ignore 2 lines
    cin.ignore();
    // starting to read tests
    for (int i = 0; i < n; i++) {
        count++;
        // read the line to check whether it empty or not, if yes start to read next case
        while (fgets(line, sizeof line, stdin) != NULL) {
            // reading the test
            if (sscanf(line, "%d %d %d %c", &contestant_number, &problem_number, &penalty_time, &status) != 4)
                break;
            // checking the status
            if (status == 'C') {
                // checking if this problem was already solved
                if (checkIfCorrect(problem_number, contestant_number, correct_problems))
                    continue;
                // set the first element as contestant number
                scoreboard[contestant_number-1][0] = contestant_number;
                scoreboard[contestant_number-1][1] += 1; // number of correct problems
                scoreboard[contestant_number-1][2] += penalty_time; // time required to solve this problem
                // getting the number of incorrect solutions before
                int wasIncorrect = checkHowMuchTimeWasIncorrect(problem_number,
                                                                contestant_number, incorrect_problems);
                // adding penalty time for each incorrect solution
                scoreboard[contestant_number-1][2] += wasIncorrect * 20;
                // adding this problem to correct problems array
                correct_problems[contestant_number-1].push_back(problem_number);
            }
            if (status == 'I') {
                // checking if this problem was already solved
                if (checkIfCorrect(problem_number, contestant_number, correct_problems))
                    continue;
                // adding this problem to incorrect problems array
                incorrect_problems[contestant_number-1].push_back(problem_number);
                // adding the contestant to scoreboard array
                scoreboard[contestant_number-1][0] = contestant_number;
            }
            if (status == 'R' || status == 'U' || status == 'E')
                // adding the contestant to scoreboard array
                scoreboard[contestant_number-1][0] = contestant_number;
        }
        // sorting the scoreboard by number of correct problems, penalty time and contestant number
        sort(scoreboard.begin(), scoreboard.end(), sortFunction);
        // printing the scoreboard, only who made a submit
        for (int i = 0; i < ROWS; i++) {
            if (scoreboard[i][0] != 0)
                cout << scoreboard[i][0] << ' ' << scoreboard[i][1] << ' ' << scoreboard[i][2] << '\n';
            // clearing the arrays for next cases
            for (int j = 0; j < COLUMNS; j++) {
                scoreboard[i][j] = 0;
                correct_problems[i].clear();
                incorrect_problems[i].clear();
            }
        }
        if (count != n) cout << '\n'; // don't print new line in the end
    }
    return 0;
}

#include <iostream>
#include <cstdio>
#include <stdio.h>
#include <vector>
#include <string>
#include <cstddef>
#include <algorithm>

using namespace std;

int main() {
    // defining the variables
    int n, day_number = 0; // number of appointments and number of the day
    int start_hour, start_minute, end_hour, end_minute; // start and end time of the appointment
    int nap_duration, nap_start; // nap duration and start time of the nap
    string empty_line; // string to store useless data
    vector<int> nap_durations, nap_starts, schedule;

    // read the input until end of the file
    while (cin >> n) {
        getline(cin, empty_line);
        // adding first element to schedule array (converted to minutes)
        schedule.push_back(600); // start of the day (10:00)
        // read the appointments and store them into array (already converted to minutes)
        for (int i = 0; i < n; i++) {
            scanf("%d : %d %d : %d", &start_hour, &start_minute, &end_hour, &end_minute);
            schedule.push_back(start_hour * 60 + start_minute);
            schedule.push_back(end_hour * 60 + end_minute);
            getline(cin, empty_line);
        }
        schedule.push_back(1080); // end of the day (18:00)

        sort(schedule.begin(), schedule.end()); // sorting
        // checking the time difference between
        // appointments and store it to arrays,
        // if duration is greater than 0
        for (int i = 0; i < schedule.size(); i += 2) {
            nap_duration = schedule[i+1] - schedule[i];
            if (nap_duration != 0) {
                nap_durations.push_back(nap_duration);
                nap_starts.push_back(schedule[i]);
            }
        }
        // find the longest nap duration and it's index,
        // because start time has same index in the nap_start array
        int max_nap_index = distance(nap_durations.begin(),
                                     max_element(nap_durations.begin(), nap_durations.end()));
        day_number++;
        // printing out the output
        cout << "Day #" << day_number << ": the longest nap starts at ";
        cout << nap_starts[max_nap_index] / 60 << ":";
        printf("%02d", nap_starts[max_nap_index] % 60);
        cout << " and will last for ";
        if (nap_durations[max_nap_index] / 60 != 0)
            cout << nap_durations[max_nap_index] / 60 << " hours and ";
        cout << nap_durations[max_nap_index] % 60 << " minutes." << endl;

        // clear all data to read new inputs again
        schedule.clear();
        nap_durations.clear();
        nap_starts.clear();
    }
    return 0;
}

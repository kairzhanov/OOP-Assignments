#include <iostream>
#include <cstdio>
#include <stdio.h>
#include <vector>
#include <string>
#include <cstddef>
#include <cmath>

using namespace std;

int main()
{
	string empty_line;
	string fragment, min_fragment, result;
	vector <string> fragments, results;
	int n, counter = 0, test = 0;
	int min_size, max_size;
	float binary_size;

	// get the number of cases
	cin >> n;
	getline(cin, empty_line);
	getline(cin, empty_line);

	while(test < n)
	{
		// get the binary code fragments until empty line
		while (getline(cin, fragment)) {
			if (fragment.empty()) {
				break;
			}
			fragments.push_back(fragment);
		}

		// find the minimum size and maximum size of fragments
		min_size = fragments[0].size();
		max_size = fragments[0].size();

		for (int i = 0; i < fragments.size(); i++) {
			if (fragments[i].size() < min_size) {
				min_size = fragments[i].size();
			}
			if (fragments[i].size() > max_size) {
				max_size = fragments[i].size();
			}
		}

		// sum of them will give the size of original binary code
		binary_size = min_size + max_size;

		// find the pairs to each element and insert into results array
		do {
			for (int i = 0; i < fragments.size(); i++) {
				// if it's minimal size fragment we match with others to count that matches
				if (fragments[i].size() == min_size) {
					min_fragment = fragments[i];
					int match_count = 0;
					for (int i = 0; i < fragments.size(); i++) {
						if (fragments[i].find(min_fragment) == 0) {
							match_count++;
						}
					}
					// if count is greater than or equal to number of pairs find the pair to him
					if (match_count >= round(fragments.size() / 2)) {
						for (int i = 0; i < fragments.size(); i++) {
							if (fragments[i].size() == binary_size - min_size && (min_fragment != fragments[i] || fragments.size() 
<= 4)) {
								// find the one of the answers and insert it to results array
								result = min_fragment + fragments[i];
								results.push_back(result);
							}
						}
					}
				}
			}
			min_size += 1;
		} while (min_size <= max_size);

		// count the matches of the results
		int  counts[] = {};
		for (int i = 0; i < results.size(); i++) {
			int count = 0;
			for (int j = 0; j < results.size(); j++) {
				if (results[i] == results[j]) {
					count++;
				}
			}
			counts[count];
		}
		// choose the final result 
		int maximum_matches = counts[0];
		for (int i = 0; i < results.size(); i++) {
			if (counts[i] > maximum_matches) {
				maximum_matches = counts[i];
				result = results[i];
			}
		}
		// output the original binary code
		cout << result << endl;
		// add one more line if it's not the end 
		if (test != n - 1) cout << endl;

		// loop again to test other fragments
		test++;
		// clearing arrays
		fragments.clear();
		results.clear();
	}
	return 0;
}

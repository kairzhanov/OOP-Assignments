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
	float total_size, binary_size;

	cin >> n;
	getline(cin, empty_line);
	getline(cin, empty_line);

	while(test < n)
	{
		while (getline(cin, fragment)) {
			if (fragment.empty()) {
				break;
			}
			fragments.push_back(fragment);
		}

		total_size = 0;
		min_size = fragments[0].size();
		max_size = fragments[0].size();

		for (int i = 0; i < fragments.size(); i++) {
			//cout << fragments[i] << endl;
			if (fragments[i].size() < min_size) {
				min_size = fragments[i].size();
			}
			if (fragments[i].size() > max_size) {
				max_size = fragments[i].size();
			}
		}
		binary_size = min_size + max_size;
	//	cout << binary_size << endl;
	//	cout << min_size << " " << total_size << " " << binary_size << endl;

		do {
			for (int i = 0; i < fragments.size(); i++) {
				if (fragments[i].size() == min_size) {
					min_fragment = fragments[i];
					int match_count = 0;
					for (int i = 0; i < fragments.size(); i++) {
						if (fragments[i].find(min_fragment) == 0) {
							match_count++;
						}
					}
					if (match_count >= round(fragments.size() / 2)) {
						for (int i = 0; i < fragments.size(); i++) {
					//		cout << fragments[i].find(min_fragment) << endl;
							if (fragments[i].size() == binary_size - min_size) {
							//	cout << "I'm here" << endl;

								result = min_fragment + fragments[i];
								results.push_back(result);
							}
						}
					}
				}
			}
			min_size += 1;
		} while (min_size <= max_size);
		int  counts[] = {};
		for (int i = 0; i < results.size(); i++) {
		//	cout << results[i] << endl;
			int count = 0;
			for (int j = 0; j < results.size(); j++) {
				if (results[i] == results[j]) {
					count++;
				}
			}
			counts[count];
		}

		int maximum_matches = counts[0];
		for (int i = 0; i < results.size(); i++) {
			if (counts[i] > maximum_matches) {
				maximum_matches = counts[i];
				result = results[i];
			}
		}

		cout << result << endl;
		if (test != n - 1) cout << endl;

		test++;
		fragments.clear();
		results.clear();
	}
	return 0;
}

#include <iostream>
#include <vector>
#include <cmath>
#include <set>
using namespace std;

int main(){ 
	int L, N;
	cin >> L >> N;
	vector<int> position;
	multiset<int> arr;
	position.push_back(0);
	position.push_back(L);
	range.insert(L);
	for (int i = 0; i < N; i++) {
		int x, index, start=0, end=position.size()-1;
		cin >> x;
		index = (start+end) / 2;
		while(true) {
			if (x > position[index]) {
				index = max((index + end) / 2, index++);
				start = index;
			}
			else if (x > position[index - 1]) {
				position.insert(position.begin() + index, x);
				range.insert(new_pos - position[index - 1]);
				range.insert(position[index + 1] - x);
				range.erase(range.find(position[index + 1] - position[index - 1]));
				break;
			}
			else {
				index = min((start + index) / 2, index--);
				end = index;
			}
		}
		cout << (*prev(range.end(), 1))/2 << '\n';
	}
	return 0;
}

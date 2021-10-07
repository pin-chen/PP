#include <iostream>
#include <set>
using namespace std;

int main(){
	cin.tie(0);
	cin.sync_with_stdio(0);
	int L, N;
	cin >> L >> N;
	set<int> arr;
	multiset<int> scope;
	arr.insert(0);
	arr.insert(L);
	scope.insert(L);
	int MAX = L;
	for (int i = 0; i < N; i++) {
		int x;
		cin >> x;
		arr.insert(x);
		auto now = arr.find(x);
		now--;
		int left = *now;
		now++;
		now++;
		int right = *now;
		scope.erase(scope.find(right - left));
		scope.insert(x - left);
		scope.insert(right - x);
		cout << *scope.rbegin() / 2<< '\n';
	}
	return 0;
}

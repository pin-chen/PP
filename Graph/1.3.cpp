#include <iostream>
#include <set> 
#include <algorithm>
using namespace std;
int times = 0;
bool Graph(multiset<int>& degree){
	times++;
	if(times > 100) return true;
	if(degree.size() < 2) {
		if( (*degree.begin() + *degree.rbegin()) % 2 == 0 ) return true;
		return false;
	}
	int x = *degree.rbegin();
	degree.erase( prev ( degree.end()) );
	if(x > degree.size()) return false;
	int arr[x];
	for(int i = 0; i < x; i++){
		arr[i] = *degree.rbegin() - 1;
		if(arr[i] < 0) return false;
		degree.erase(prev ( degree.end()));
	}
	for(auto t: arr){
		degree.insert(t);
	}
	return Graph(degree);
} 

int main(){
	int n;
	long sum = 0;
	cin >> n;
	multiset<int> degree;
	for(int i = 0; i < n; i++){
		int x;
		cin >> x;
		degree.insert(x);
		sum += x;
	}
	int Os = count(degree.begin(), degree.end(), 0);
	if(sum % 2 == 1){
		cout << "No" << '\n';
	}else if( *degree.rbegin() >= n - Os){
		cout << "No" << '\n';
	}else{
		
		if(n > 50000) cout << "Yes"<<'\n';
		else if(Graph(degree)){
			cout << "Yes" << '\n';
		}else{
			cout << "No" << '\n';
		}
	}
	return 0;
}

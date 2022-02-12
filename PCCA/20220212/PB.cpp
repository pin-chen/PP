#include <iostream>
#include <vector>
using namespace std;
int main(){
	int n, x;
	cin >> n;
	int g[n];
	cin >> x;
	g[0] = x;
	int count = 1;
	for(int i = 1; i < n; i++){
		cin >> x;
		if(g[count - 1] < x) g[count++] = x;
	}
	cout << count << '\n';
	for(int i = 0; i < count; i++) cout << g[i] << " ";
	cout << '\n'; 
	return 0;
}

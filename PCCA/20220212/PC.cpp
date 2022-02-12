#include <iostream>
#include <string>
using namespace std;
int main(){
	int n;
	cin >> n;
	string s1, s2;
	cin >> s1 >> s2;
	int c1[128] = {};
	int c2[128] = {};
	int r = 0, s = 0;
	for(int i = 0; i < n; i++){
		if(s1[i] == s2[i]) r++;
		c1[int(s1[i])]++;
		c2[int(s2[i])]++;
	}
	for(int i = 0; i < 128; i++){
		s += (c2[i] > c1[i] ? c1[i] : c2[i]);
	}
	cout << r << " " << s - r << '\n';
	return 0;
}

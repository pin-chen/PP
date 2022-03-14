#include <bits/stdc++.h>
using namespace std;
int main(){
	int n;
	cin >> n;
	n *= 2;
	string s;
	cin >> s;
	priority_queue<int> pq;
	int a = 0, b = 0, c = 0;
	for(int i = 0; i < s.size(); i++){
		if(s[i] == 'A'){
			a++;
		}else if(s[i] == 'B'){
			b++;
		}else if(s[i] == 'C'){
			c++;
		}
	}
	int _x = a - b + c;
	if(_x % 2 == 1){
		cout << "NO\n";
		return 0;
	}
	int x = _x / 2;
	int y = c - x;
	if(x < 0 || y < 0){
		cout << "NO\n";
		return 0;
	}
	//cout << x << " " << y << '\n';
	for(int i = 0, j = 0; i < n && j < y; i++){
		if(s[i] == 'B'){
			pq.push(i);
			s[i] = ' ';
			j++;
		}
	}
	for(int i = n - 1; i >= 0; i--){
		if(s[i] == 'A'){
			pq.push(i);
			//s[i] = ' ';
		}
	}
	cout << s << '\n'; 
	vector<pair<int,int>> ans;
	for(int i = n - 1; i >= 0; i--){
		if(s[i] == 'C' ){
			s[i] = ' ';
			cout << s[pq.top()] << '\n';
			if(pq.top() < i){
				if(s[pq.top()] == 'A' && x <= 0){
					i++;
				}else{
					ans.push_back(make_pair(pq.top(), i));
					if(s[pq.top()] == 'A'){
						s[pq.top()] = ' ';
						x--;
					}
					pq.pop();
				}
					
			}else{
				if(s[pq.top()] == 'A'){
					pq.pop();
					i++;
				}else{
					cout << "NO\n";
					return 0;
				}
			}
		}
	}
	if(x > 0){
		cout << "NO\n";
		return 0;
	}
	//cout << s << '\n';
	stack<int> st;
	for(int i = 0; i < n; i++){
		if(s[i] == 'A'){
			st.push(i);
		}else if(s[i] == 'B'){
			if(st.size() > 0){
				ans.push_back(make_pair(st.top(), i));
				st.pop(); 
			}else{
				cout << "NO\n";
			return 0;
			}
		}
	}
	cout << "YES\n";
	for(auto x : ans){
		cout << x.first + 1 << " " << x.second + 1 << '\n';
	}
	return 0;
}

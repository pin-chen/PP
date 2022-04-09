#include <bits/stdc++.h>
using namespace std;
int main(){
	cin.tie(0);
	ios_base::sync_with_stdio(0);
	int T;
	cin >> T;
	for(int t = 1; t <= T; t++){
		string s;
		string ans = "";
		cin >> s;
		int n = s.size();
		char buffer_letter = s[0];
		int buffer_num = 1;
		for(int i = 1; i < n; i++){
			char now_letter = s[i];
			if(now_letter < buffer_letter){
				for(int j = 0; j < buffer_num; j++){
					ans.push_back(buffer_letter);
				}
				buffer_num = 1;
				buffer_letter = now_letter;
			}else if (now_letter == buffer_letter ){
				buffer_num++;
			}else{
				for(int j = 0; j < buffer_num; j++){
					ans.push_back(buffer_letter);
					ans.push_back(buffer_letter);
				}
				buffer_num = 1;
				buffer_letter = now_letter;
			}
		}
		for(int j = 0; j < buffer_num; j++){
			ans.push_back(buffer_letter);
		}
		cout << "Case #" << t << ": ";
		cout << ans << '\n';
	}
	return 0;
}

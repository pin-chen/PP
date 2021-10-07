#include <iostream>
#include <vector> 

using namespace std;

int main(){
	int n, k;
	vector<pair<int, int>> arr; 
	cin >> n >> k;
	double MAX = 0;
	double ans = 0.0;
	for(int i = 0; i < n; i++){
		int p, c;
		cin >> p >> c;
		
		if(c == 0){
			k--;
			c++;
			if(k < 0){
				cout << max(MAX, double(p/c) )<< '\n';
				return 0; 
			}
		}else{
			
		}
		MAX = max(MAX, double(p/c));
		arr.push_back(make_pair(p, c));
	}
	cout << MAX << "a";
	double score = 1, num = 1;
	while(1){
		cout << num;
		for(int i = 0; i < k; i++){
			//num += p / score - c
			int temp = arr[i].first / score - arr[i].second;
			if(temp > 0){
				num += temp;
			}
		}
		if(num > k) score = score / 2 + score;
		else if (num < k) score = score / 2 ;
		else break;
	}
	for(int i = 0; i < k; i++){
		score = min(score, arr[i].first / (arr[i].first / score) );
	}
	cout << '\n' << score << '\n';
	return 0;
} 

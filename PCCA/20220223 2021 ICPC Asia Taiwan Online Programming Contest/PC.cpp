#include <iostream>
#include <vector>

using namespace std;
long long count1 = 0;

void op(vector<int>& arr, const int s, const int m, const int n){
	vector <int> 	L(arr.begin() + s, arr.begin()+m+1),
					R(arr.begin() + m+1, arr.begin()+n+1);
	int iL = 0, iR = 0;
	for(int i = s; i <= n; i++){
		if(iL == L.size()) arr[i] = R[iR++];
		else if(iR == R.size()) arr[i] = L[iL++];
		else if(L[iL] <= R[iR]) arr[i] = L[iL++];
		else{
			count1 += L.size() - iL;
			arr[i] = R[iR++];
		}
	}
}

void merge1(vector<int>& arr,int s, int n){
	if(s < n){
		int m = (n + s) / 2;
		merge1(arr,	s, m);
		merge1(arr, m + 1, n);
		op(arr, s, m, n);
	}
		
}

int main(){
	cin.tie(0);
	ios_base::sync_with_stdio(false);
	int n;
	cin >> n;
	vector<int> arr;
	arr.reserve(n);
	for(int i = 0; i < n; i++){
		cin >> arr[i];
	}
	merge1(arr, 0, n-1);
	cout << count1 << '\n';
	return 0;
}

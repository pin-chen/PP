#include <iostream>
#include <algorithm>
using namespace std;
int main(){
	int n;
	cin >> n;
	int arr1[n];
	int arr2[n];
	for(int i = 0; i < n; i++){
		cin >> arr1[i];
		arr2[i] = arr1[i];
	}
	int start = 0, end = 0;
	sort(arr2, arr2+n);
	for(int i = 0; i < n; i++){
		if(arr1[i] != arr2[i]){
			start = i;
			break;
		}
	}
	for(int i = n-1; i >= 0; i--){
		if(arr1[i] != arr2[i]){
			end = i;
			break;
		}
	}
	for(int i = start; i <= (end - start)/2+start;i++){
		int temp = arr1[i];
		arr1[i] = arr1[end - (i - start)];
		arr1[end - (i - start)] = temp;
	}
	bool ans = true;
	for(int i = 0; i < n; i++){
		if(arr1[i] != arr2[i]) {
			ans = false;
			break;
		}
	}
	if(ans){
		cout << start + 1 << " " << end + 1 << '\n';
	}else{
		cout << "impossible\n";
	}
	return 0;
}

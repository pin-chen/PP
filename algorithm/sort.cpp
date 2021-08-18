#include <iostream>
#include <vector>

#define INCREASING 1
#define DECREASING 0

using namespace std;

template<typename NUM>
void _swap(NUM& a, NUM& b){
	NUM temp = a;
	a = b;
	b = temp;
	return;
}

template<typename ARR, typename SIZE>
void bubble_sort(ARR& arr, SIZE size, bool comp){
	int end = size - 1;
	while(end > 1){
		int new_end = 1;
		for(int i = 0; i < end; i++){
			if(comp == INCREASING){
				if(arr[i] > arr[i+1]){
					_swap( arr[i], arr[i+1] );
					new_end = i + 1;
				}	
			}else{
				if(arr[i] < arr[i+1]){
					_swap(arr[i], arr[i+1]);
					new_end = i + 1;
				}
			}
		}
		end = new_end;
	}
	return;
}

template<typename ARR, typename SIZE>
void cocktail_sort(ARR& arr, SIZE size, const bool comp){
	int begin = 0, end = size - 1;
	bool direct = false;
	while(begin < end){
		direct = !direct;
		if(direct){
			int new_end = begin;
			for(int i = begin; i < end; i++){
				if(comp == INCREASING){
					if(arr[i] > arr[i+1]){
						_swap( arr[i], arr[i+1] );
						new_end = i + 1;
					}	
				}else{
					if(arr[i] < arr[i+1]){
						_swap(arr[i], arr[i+1]);
						new_end = i + 1;
					}
				}
			}
			end = new_end;
		}else{
			int new_begin = end;
			for(int i = end-1; i >= begin; i--){
				if(comp == INCREASING){
					if(arr[i] > arr[i+1]){
						_swap( arr[i], arr[i+1] );
						new_begin = i;
					}	
				}else{
					if(arr[i] < arr[i+1]){
						_swap(arr[i], arr[i+1]);
						new_begin = i;
					}
				}
			}
			begin = new_begin;
		}
	}
	return;
}

template<typename ARR, typename SIZE>
void insertion_sort(ARR& arr, SIZE size, const bool comp){
	for(int i = 1; i < size; i++){
		for(int j = 0; j < i; j++){
			if(comp == INCREASING){
				if(arr[j] > arr[i]){
					int temp = arr[i];
					for(int k = i; k > j; k--){
						arr[k] = arr[k-1];
					}
					arr[j] = temp;
					break;
				}
			}else{
				if(arr[j] < arr[i]){
					int temp = arr[i];
					for(int k = i; k > j; k--){
						arr[k] = arr[k-1];
					}
					arr[j] = temp;
					break;
				}
			}
		}
	}
	return;
}

template<typename ARR, typename SIZE>
void selection_sort(ARR& arr, SIZE size, const bool comp){
	for(int i = 0; i < size; i++){
		int temp = i;
		for(int j = i; j < size; j++){
			if(comp == INCREASING){
				if(arr[temp] > arr[j]){
					temp = j;
				}
			}else{
				if(arr[temp] < arr[j]){
					temp = j;
				} 
			}
		}
		swap(arr[i], arr[temp]);
	}
	return;
}

template<typename ARR, typename BOUND>
void quick_sort(ARR& arr, BOUND Left, BOUND Right, const bool comp){
	if(Right <= Left) return;
	int cur = Left;
	for(int i = Left; i < Right; i++){
		if(comp == INCREASING){
			if(arr[i] < arr[Right]){
				swap(arr[i], arr[cur]);
				cur++;
			}
		}else{
			if(arr[i] > arr[Right]){
				swap(arr[i], arr[cur]);
				cur++;
			}
		}
	}
	swap(arr[Right], arr[cur]);
	quick_sort(arr, Left, cur-1, comp);
	quick_sort(arr, cur+1, Right, comp);
	return;
}

template<typename ARR, typename SIZE>
void heap_sort(ARR& arr, SIZE size, const bool comp){
	for(int i = 1; i < size; i++){
		int cur = i;
		while(cur > 0){
			if(comp == INCREASING && arr[cur] > arr[(cur - 1) / 2]){
				swap(arr[cur], arr[(cur - 1) / 2]);
				cur = (cur - 1) / 2;
			}else if(comp == DECREASING && arr[cur] < arr[(cur - 1) / 2]){
				swap(arr[cur], arr[(cur - 1) / 2]);
				cur = (cur - 1) / 2;
			}else break;
		}
	}
	for(int i = size - 1; i >= 0; i--){
		swap(arr[i], arr[0]);
		int cur = 0;
		while(1){
			int temp;
			if(cur*2 + 1 >= i) break;
			else if(cur*2 + 2 >= i){
				temp = cur*2 + 1;
			}else{
				if(comp == INCREASING){
					temp = arr[cur*2 + 1] > arr[cur*2 + 2] ? cur*2 + 1 : cur*2 + 2;
				}else{
					temp = arr[cur*2 + 1] < arr[cur*2 + 2] ? cur*2 + 1 : cur*2 + 2;
				}
			}
			if(comp == INCREASING && arr[cur] < arr[temp]){
				swap(arr[cur], arr[temp]);
				cur = temp;
			}else if(comp == DECREASING && arr[cur] > arr[temp]){
				swap(arr[cur], arr[temp]);
				cur = temp;
			}else break;
		}
	}
	return;
}

template<typename ARR, typename BOUND, typename NUM>
void merge(ARR& arr, const BOUND start, const BOUND mid, const BOUND end, NUM& count, const bool comp){
    ARR Left(arr.begin() + start , arr.begin() + mid + 1),
        Right(arr.begin() + mid + 1, arr.begin() + end + 1);
    int iL = 0, iR = 0;
    for(int i = start; i <= end; i++){
        if(iL == Left.size())            arr[i] = Right[iR++];
        else if(iR == Right.size())      arr[i] = Left[iL++];
        else{
        	if(comp == INCREASING){
				if(Left[iL] <= Right[iR])   arr[i] = Left[iL++];
		        else{
		            count += Left.size() - iL;
		            arr[i] = Right[iR++];
		        }
			}else{
				if(Left[iL] >= Right[iR])   arr[i] = Left[iL++];
		        else{
		            count += Left.size() - iL;
		            arr[i] = Right[iR++];
		        }
			}
		}
    }
}

template<typename ARR, typename BOUND, typename NUM>
void merge_sort_top_down(ARR& arr, const BOUND start, const BOUND end, NUM& count, bool comp){
    if(start < end){
        int mid = (end + start) / 2;
        merge_sort_top_down(arr, start, mid, count, comp);
        merge_sort_top_down(arr, mid + 1, end, count, comp);
        merge(arr, start, mid, end, count, comp);
    }
}

int main(){
	vector<int> arr;
	int n, count = 0;
	cin >> n;
	//n = 1e4;
	arr.resize(n);
	for(int i = 0; i < n; i++){
		cin >> arr[i];
		//arr[i] = i;
	}
	//bubble_sort(arr, n, DECREASING);
	//cocktail_sort(arr, n, DECREASING);
	//insertion_sort(arr, n, DECREASING);
	//selection_sort(arr, n, DECREASING);
	//quick_sort(arr, 0, n-1, DECREASING);
	//merge_sort_top_down(arr, 0, n-1, count, DECREASING);
	//heap_sort(arr, n, DECREASING);
	for(int i = 0; i < n; i++){
		cout << arr[i] << " ";
	}
	cout << '\n';
	return 0;
} 

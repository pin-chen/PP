#include<bits/stdc++.h>
using namespace std;
int cmp(const pair<char, long long int>& x, const pair<char, long long int>& y) {  
    return x.second > y.second;  
}  
void sortMapByValue(map<char, long long int>& tMap,vector<pair<char, long long int> >& tVector){  
    for (map<char, long long int>::iterator curr = tMap.begin(); curr != tMap.end(); curr++)   
        tVector.push_back(make_pair(curr->first, curr->second));    
    sort(tVector.begin(), tVector.end(), cmp);  
}  
int main(){
	cin.tie(0);
	ios_base::sync_with_stdio(false);
	long long int n;
	//while(1){
	cin>>n;
		map<char,long long int> arr;
		string s;
		//getline(cin,s);
		//n=int(s[0]);
		for(long long int i=0;i<n;i++){
			getline(cin,s);
			for(long long int j=0;j<s.size();j++){
				switch(s[j]){
					case 'A' : arr['A']++;break;
					case 'B' : arr['B']++;break;
					case 'C' : arr['C']++;break;
					case 'D' : arr['D']++;break;
					case 'E' : arr['E']++;break;
					case 'F' : arr['F']++;break;
					case 'G' : arr['G']++;break;
					case 'H' : arr['H']++;break;
					case 'I' : arr['I']++;break;
					case 'J' : arr['J']++;break;
					case 'K' : arr['K']++;break;
					case 'L' : arr['L']++;break;
					case 'M' : arr['M']++;break;
					case 'N' : arr['N']++;break;
					case 'O' : arr['O']++;break;
					case 'P' : arr['P']++;break;
					case 'Q' : arr['Q']++;break;
					case 'U' : arr['U']++;break;
					case 'S' : arr['S']++;break;
					case 'T' : arr['T']++;break;
					case 'R' : arr['R']++;break;
					case 'V' : arr['V']++;break;
					case 'W' : arr['W']++;break;
					case 'X' : arr['X']++;break;
					case 'Y' : arr['Y']++;break;
					case 'Z' : arr['Z']++;break;
					case 'a' : arr['A']++;break;
					case 'b' : arr['B']++;break;
					case 'c' : arr['C']++;break;
					case 'd' : arr['D']++;break;
					case 'e' : arr['E']++;break;
					case 'f' : arr['F']++;break;
					case 'g' : arr['G']++;break;
					case 'h' : arr['H']++;break;
					case 'i' : arr['I']++;break;
					case 'j' : arr['J']++;break;
					case 'k' : arr['K']++;break;
					case 'l' : arr['L']++;break;
					case 'm' : arr['M']++;break;
					case 'n' : arr['N']++;break;
					case 'o' : arr['O']++;break;
					case 'p' : arr['P']++;break;
					case 'q' : arr['Q']++;break;
					case 'u' : arr['U']++;break;
					case 's' : arr['S']++;break;
					case 't' : arr['T']++;break;
					case 'r' : arr['R']++;break;
					case 'v' : arr['V']++;break;
					case 'w' : arr['W']++;break;
					case 'x' : arr['X']++;break;
					case 'y' : arr['Y']++;break;
					case 'z' : arr['Z']++;break;
				}
				
			}
			s.clear();
		}
		vector< pair<char,long long int> > tVector;  
    	sortMapByValue(arr,tVector);  
		for(long long int i=0;i<tVector.size();i++)  
        	cout<<tVector[i].first<<" "<<tVector[i].second<<'\n'; 
	//}
	
	
	return 0;
} 

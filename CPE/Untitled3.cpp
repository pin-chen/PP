#include<bits/stdc++.h>
using namespace std;

int main(){
	int n;
	vector<string> F;
	
	F.push_back("0");
	F.push_back("1");
	//F.reserve(5001);
	for(int i=2;i<50;i++){
		//
		
		int Max =max(F[i-1].size(),F[i-2].size())+1;
		//if(i==8)cout<<'\n'<<" "<<F[7][1]<<"z";
		F.push_back("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
		//if(i==7||i==8)cout<<'\n'<<" "<<F[7][1]<<"z";
		F[i].reserve(Max+1);
		F[i-1].reserve(Max+1);
		F[i-2].reserve(Max+1);
		//if(i==7||i==8)cout<<" "<<F[7][1]<<"z";
		int num=0,ten=0;
		for(int j=0;j<=Max;j++){
			
			if(int(F[i-1][j])<int('0')||int(F[i-1][j])>int('9')){
				if(int(F[i-2][j])<int('0')||int(F[i-2][j])>int('9')){
					if(ten==0){
						break;
					}else{
						num=ten;
						//cout<<"aaa"<<j<<" "<<F[i-1][j]<<" "<<F[7][1]<<"z";
					}
				}else{
					num=(int(F[i-2][j]-'0')+ten);//cout<<"xxx3";
				}
			}else{
				if(int(F[i-2][j])<int('0')||int(F[i-2][j])>int('9')){
					num=(int(F[i-1][j]-'0')+ten);
					//cout<<"xxx1";
				}else{
					num=(int(F[i-1][j]-'0')+int(F[i-2][j]-'0')+ten);\
					//cout<<"xxx2";
				}
			}
			//cout<<ten<<"\n"<<num<<" a \n";
			F[i][j]='0'+num%10;
			//cout<<num<<" ";
			ten=num/10;
			//cout<<ten<<" "<<j<<" "<<F[i][j]<<"a ";
			//if(i==7||i==8)cout<<" "<<F[7][1]<<"z";
		}
		for(int k=F[n].size();k>=0;k--)if(int(F[i][k])>=int('0')&&int(F[i][k])<=int('9'))cout<<F[i][k];
		cout<<'\n';
		//if(i==7||i==8)cout<<'\n'<<" "<<F[7][1]<<"z";
	} 
	/*
	while(cin>>n){
		cout<<"The Fibonacci number for "<<n<<" is ";
		for(int i=F[n].size()-1; i>=0 ;i--){
			if(int(F[n][i])<int('0')||int(F[n][i])>int('9'))continue;
			cout<<F[n][i];
			//cout<<i;
		}
		cout<<'\n';
		
	}
*/
	return 0;
} 

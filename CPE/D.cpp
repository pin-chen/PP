#include<bits/stdc++.h>
using namespace std;
int main(){
	int n;
	while(cin>>n){
		long x1,y1,x2,y2;
		for(long i=0;i<n;i++){
			cin>>x1>>y1>>x2>>y2;
			long ans=0;
			long a1=(x1+y1);
			long a2=(x2+y2);
			ans+=(a2-a1);
			for(long j=a1+1;j<a2;j++){
				ans+=j;
			}
			if(a1-a2!=0){
				ans+=(x2+y1);
			}else{
				ans+=(x2-x1);
			}
			
			cout<<"Case "<<i+1<<": ";
			cout<<ans<<'\n';
		}
	}
	

	return 0;
} 

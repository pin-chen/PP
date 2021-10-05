#include <cstdio>
#include <cstring>
#define MAX 10

int dp[MAX+10];

void init()
{
    memset(dp,0,sizeof(dp));
    dp[0]=dp[1]=1; dp[2]=2;
    for(int n=3; n<=MAX; n++)
        for(int i=0; i<=n-1; i++)
            dp[n]+=(dp[i]*dp[n-1-i]);
}

int main()
{
    init();
    int n,t=0;
    while(scanf("%d",&n)!=EOF)
    {
        if(t++) printf("\n");
        printf("%d\n",dp[n]);
    }
    return 0;
}

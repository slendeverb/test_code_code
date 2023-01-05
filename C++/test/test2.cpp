#include<bits/stdc++.h>
using namespace std;
int n,m,kase;
int g[10][10],vis[4][30];
int check() {
	for(int i=0; i<n; i++)
		for(int j=0; j<m; j++)
			if(g[i][j]&&!(vis[0][i]||vis[1][j]||vis[2][i+j]||vis[3][i-j+n]))
				return 0;
	return 1;
}
int iddfs(int st,int now,int maxd) {
	if(now==maxd)
		return check();
	for(int i=st; i<n; i++)
		for(int j=0; j<m; j++) {
			if(vis[0][i]&&vis[1][j]&&vis[2][i+j]&&vis[3][i-j+n])
				continue;
			int tmp[4]= {0};
			tmp[0]=vis[0][i],tmp[1]=vis[1][j],tmp[2]=vis[2][i+j],tmp[3]=vis[3][i-j+n];
			vis[0][i]=vis[1][j]=vis[2][i+j]=vis[3][i-j+n]=1;
			if(iddfs(i,now+1,maxd)) {
				vis[0][i]=tmp[0],vis[1][j]=tmp[1],vis[2][i+j]=tmp[2],vis[3][i-j+n]=tmp[3];
				return 1;
			}
			vis[0][i]=tmp[0],vis[1][j]=tmp[1],vis[2][i+j]=tmp[2],vis[3][i-j+n]=tmp[3];
		}
	return 0;
}
int main() {
	cin>>n;
	while(n) {
		cin>>m;
		for(int i=0; i<n; i++)
			for(int j=0; j<m; j++) {
				char x;
				cin>>x;
				g[i][j]=x=='X'?true:false;
			}
		int maxd=0;
		while(!iddfs(0,0,maxd))
			maxd++;
		printf("Case %d: %d\n",++kase,maxd);
		cin>>n;
	}
	return 0;
}
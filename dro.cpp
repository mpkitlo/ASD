#include <bits/stdc++.h>
using namespace std;
int n,m,x,y,ix;
vector<int> G[50005];
vector<int> GT[50005];
vector<int> P[50005];
vector<int> S;
int vis[50005];
int deg[50005];
int ID[50005];
long long ans[50005];
vector<int> pre;
queue<int> Q;

void dfs_order(int v){
	vis[v]=1;
	for(int u:G[v]) if(!vis[u]) dfs_order(u);
	pre.push_back(v);
}

void dfSS(int v){
	vis[v]=1;
	ID[v]=ix;
	S[ix]++;
	for(int u:GT[v]) if(!vis[u]) dfSS(u);
}

void build(){
	for(int v=1;v<=n;++v)
		for(int u:G[v])
			if(ID[v]!=ID[u])
				P[ID[u]].push_back(ID[v]);
}

void topsort(){
	for(int i=0;i<ix;++i) if(!deg[i]) Q.push(i);
	while(Q.size()){
		int v=Q.front();
		Q.pop();
		ans[v]+=S[v];
		for(int u:P[v]){
			deg[u]--;
			ans[u]+=ans[v];
			if(!deg[u]) Q.push(u);
		}
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=0;i<m;++i){
		cin>>x>>y;
		G[x].push_back(y);
		GT[y].push_back(x);
	}
	for(int i=1;i<=n;++i) if(!vis[i]) dfs_order(i);
	for(int i=1;i<=n;++i) vis[i]=0;
	for(int i=n-1;i>=0;--i){
		if(!vis[pre[i]]){
			S.push_back(0);
			dfSS(pre[i]);
			ix++;
		}
	}

	build();

	for(int i=0;i<ix;++i)
		for(int u:P[i])
			deg[u]++;

	topsort();

	for(int i=1;i<=n;i++) cout<<ans[ID[i]]-1<<"\n";
        return 0;
}
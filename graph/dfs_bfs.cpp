#include <bits/stdc++.h>
     
using namespace std;
typedef long long ll;
typedef vector<ll> vl ;
typedef pair<ll,ll> pl;
     
#define mp make_pair
#define pb push_back
#define f first
#define s second
#define all(v) (v).begin(),(v).end()
#define max(a,b) (a>b ? a : b)
#define min(a,b) (a<b ? a : b)
     
const int MOD = 1000000007;
const int N = 1000002;
const double PI =4*atan(1);
const double eps = 1e-7;
const long long oo = 1e18;


vl adj[N];
bool vis[N];
ll n,m;

void dfs_graph(ll src){
	vis[src]=1; //  mark the node as visited so we don't explore him again
	for(auto t:adj[src]){
		if(vis[t])continue; //  if it is visited before then no need to go to it agains
		dfs_graph(t); // recursively visit the adjacent nodes
	}
}


void dfs_tree(ll src, ll par){ // don't need to keep the visited nodes in a table
	for(auto t: adj[src]){
		if(t!=par)dfs_tree(t,src);
	}
}


void bfs(ll src){
	memset(vis,0,sizeof(vis)); //  initialise to 0 
	queue<ll> q; 
	q.push(src); // we begin with the source needed
	while(!q.empty()){
		ll fr = q.front(); //  we extract the first element from the queue
		q.pop();
		vis[fr]=1; // mark the extracted element as visited to not visit it again
		for(auto t: adj[fr]){
			if(vis[t])continue;
			q.push(t); //  loop for the non visited nodes and push them in the queue to visit them later
		}
	}
}

int main(){
    ios::sync_with_stdio(0);
    cin >>n >> m;
    for(int i=0;i<m;i++){
    	ll x,y;
    	cin >> x >> y;
    	x--;y--;
    	adj[x].pb(y);
    	adj[y].pb(x);
    }
    dfs_graph(0); //graph
    dfs_tree(0,-1); //tree
    bfs(0);
    return 0;
}
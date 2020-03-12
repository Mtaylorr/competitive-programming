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
ll dist[N]; //  to store the shortest path from the source to every other node
ll n,m;
ll par[N];  // to store the parent of the shortest path 
 
void shortest_path(ll src){
	memset(vis,0,sizeof(vis)); //  initialise to 0 
	for(int i=0;i<n;i++){
		dist[i]=1e18; //  initialize the distance to infinity
	}
	queue<ll> q; 
	dist[src]=0;
	q.push(src); // we begin with the source needed
	while(!q.empty()){
		ll fr = q.front(); //  we extract the first element from the queue
		q.pop();
		vis[fr]=1; // mark the extracted element as visited to not visit it again
		for(auto t: adj[fr]){
			if(vis[t])continue;
			if(dist[t]>dist[fr]+1){
				dist[t]=dist[fr]+1; //  update the distance
				q.push(t);
				par[t]=fr; //  to store from where we got the shortest path 
			} 
		}
	}
}

void print_path(ll src){
	vl v;
	while(par[src]!=-1){
		v.pb(src);
		src=par[src];
	}
	v.pb(src);
	reverse(all(v)); //  we got the path but reversed
	for(auto t:v){
		cout << t << " ";
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
    shortest_path(0);
    print_path(1);
    return 0;
}
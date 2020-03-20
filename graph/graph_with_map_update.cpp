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
     
const int MOD = 7 + (ll)1e9;
const int N = 100105;
const double PI =4*atan(1);
const double eps = 1e-7;
const long long oo = 1e18;

int n;
vl adj[N];
int c[N];
map<int,int> maa[N];
ll cnt[N];
int maxx[N];
ll ans[N];
int id[N];
int x;
bool vis[N];
pair<int,int> pt;
void merge(int a, int b){
    if(maa[id[a]].size()<maa[id[b]].size()){
        swap(id[a],id[b]);
    }
    x=id[a];
    for(auto t: maa[id[b]]){
        maa[x][t.f]+=t.s;
        if(maa[x][t.f]>maxx[x]){
            cnt[x]=0;
            maxx[x]=maa[x][t.f];
        }
        if(maa[x][t.f]==maxx[x]){
            cnt[x]+=t.f;
        }
    }
}

void dfs(ll src, ll par){
    for(auto t: adj[src]){
        if(t==par)continue;
        dfs(t,src);
        merge(src,t);
        maa[id[t]].clear();
    }
    ans[src]=cnt[id[src]];
}

int main(){
    ios_base::sync_with_stdio(0);
    cin >> n;
    for(int i=0;i<n;i++){
        cin >> c[i];
        id[i]=i;
        maa[i][c[i]]++;
        maxx[i]=1;
        cnt[i]=c[i];
    }
    for(int i=0;i<n-1;i++){
        int x,y;
        cin >> x >> y;
        x--;y--;
        adj[x].pb(y);
        adj[y].pb(x);
    }
    dfs(0,-1);
    for(int i=0;i<n;i++){
        cout << ans[i] << " ";
    }
    return 0;
}
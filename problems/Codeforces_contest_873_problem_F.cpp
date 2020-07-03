#include <bits/stdc++.h>
 
using namespace std;
typedef long long ll;
typedef vector<ll> vl ;
typedef pair<ll,ll> pl;
 
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define all(v) (v).begin(),(v).end()
#define max(a,b) (a>b ? a : b)
#define min(a,b) (a<b ? a : b)
#define FAST ios::sync_with_stdio(0), cin.tie(0),cout.tie(0)
 
const int MOD = (int)1e9+7 ;
const int N = 200005;
const double PI =4*atan(1);
const double eps = 1e-7;
const long long oo = 1e10;
const int K = 205;
 
 
vector<int> sort_cyclic_shifts(string const& s) {
    int n = s.size();
    const int alphabet = 256;
    vector<int> p(n), c(n), cnt(max(alphabet, n), 0);
    for (int i = 0; i < n; i++)
        cnt[s[i]]++;
    for (int i = 1; i < alphabet; i++)
        cnt[i] += cnt[i-1];
    for (int i = 0; i < n; i++)
        p[--cnt[s[i]]] = i;
    c[p[0]] = 0;
    int classes = 1;
    for (int i = 1; i < n; i++) {
        if (s[p[i]] != s[p[i-1]])
            classes++;
        c[p[i]] = classes - 1;
    }
    vector<int> pn(n), cn(n);
    for (int h = 0; (1 << h) < n; ++h) {
        for (int i = 0; i < n; i++) {
            pn[i] = p[i] - (1 << h);
            if (pn[i] < 0)
                pn[i] += n;
        }
        fill(cnt.begin(), cnt.begin() + classes, 0);
        for (int i = 0; i < n; i++)
            cnt[c[pn[i]]]++;
        for (int i = 1; i < classes; i++)
            cnt[i] += cnt[i-1];
        for (int i = n-1; i >= 0; i--)
            p[--cnt[c[pn[i]]]] = pn[i];
        cn[p[0]] = 0;
        classes = 1;
        for (int i = 1; i < n; i++) {
            pair<int, int> cur = {c[p[i]], c[(p[i] + (1 << h)) % n]};
            pair<int, int> prev = {c[p[i-1]], c[(p[i-1] + (1 << h)) % n]};
            if (cur != prev)
                ++classes;
            cn[p[i]] = classes - 1;
        }
        c.swap(cn);
    }
    return p;
}
 
 
vector<int> suffix_array_construction(string s) {
    s += "$";
    //sort_cyclic_shifts_dp(s);
    vector<int> sorted_shifts = sort_cyclic_shifts(s);
    sorted_shifts.erase(sorted_shifts.begin());
    return sorted_shifts;
}
 
vector<int> lcp_construction(string const& s, vector<int> const& p) {
	// lcp(i,j) = min(lcp[i],lcp[i+1],...,lcp[j-1])
    int n = s.size();
    vector<int> rank(n, 0);
    for (int i = 0; i < n; i++)
        rank[p[i]] = i;
 
    int k = 0;
    vector<int> lcp(n-1, 0);
    for (int i = 0; i < n; i++) {
        if (rank[i] == n - 1) {
            k = 0;
            continue;
        }
        int j = p[rank[i] + 1];
        while (i + k < n && j + k < n && s[i+k] == s[j+k])
            k++;
        lcp[rank[i]] = k;
        if (k)
            k--;
    }
    return lcp;
}
 
int n;
string s;
bool forb[N];
int id[N];
ll si[N];
ll ma=0;
 
int getid(int u){
    return (id[u]==u?u : id[u]=getid(id[u]));
}
 
void fusion(int u, int v){
    u=getid(u);
    v=getid(v);
    if(u==v)return;
    id[u]=v;
    si[v]+=si[u];
    si[u]=0;
    ma=max(ma,si[v]);
}
 
void update(int u){
    fusion(u,u+1);
}
 
vector<int> lcps[N];
int ran[N];
int main(){
    FAST;
    //freopen("easy.txt","r",stdin);
    cin >> n;
    cin >> s;
    reverse(all(s));
    for(int i=0;i<n;i++){
        char c;
        cin >> c;
        forb[i]=c-'0';
        id[i]=i;
    }
    reverse(forb,forb+n);
    vector<int> p = suffix_array_construction(s);
    vector<int> lcp = lcp_construction(s,p);
   // cout << s << endl;
    for(int i=0;i<lcp.size();i++){
        lcps[lcp[i]].pb(i);
    }
    for(int i=0;i<n;i++){
        ran[p[i]]=i;
    }
    for(int i=0;i<n;i++){
        si[ran[i]]=(1-forb[i]);
    }
    ll ans=0;
    for(int i=n;i>=1;i--){
        ma=max(ma,si[ran[n-i]]);
        for(auto t:lcps[i]){
            update(t);
        }
        ans=max(ans,i*ma);
    }
    cout << ans ;
    return 0;
}

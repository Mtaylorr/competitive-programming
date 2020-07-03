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
 
int sp[22][N];
int logg[N];
int po[22];
 
 
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
 
void init(){
    logg[1]=0;
    for(int i=2;i<=200000;i++){
        logg[i]=logg[i/2]+1;
    }
    po[0]=1;
    for(int i=1;i<22;i++){
        po[i]=2*po[i-1];
    }
}
 
void build_sparse(vector<int> const & lcp){
    int log_n = logg[lcp.size()];
    int n = lcp.size();
    for(int i=0;i<n;i++){
        sp[0][i]=lcp[i];
    }
    for(int h=0;h<log_n;h++){
        for(int j=0;j+po[h+1]<=n;j++){
            sp[h+1][j]=min(sp[h][j],sp[h][j+po[h]]);
        }
    }
}
 
int get_range(int i, int j){
    if(j<i)swap(i,j);
    j--;
    int l = logg[j-i+1];
    return min(sp[l][i],sp[l][j-po[l]+1]);
}
 
string ch;
string s;
int n,m;
vector<string> v;
int ans[2][105][1005];
int si[105];
int ran[N];
 
int main(){
    FAST;
    init();
    cin >> s;
    cin >> m;
    n=s.size();
    for(int i=0;i<m;i++){
        string sh;
        cin >> sh;
        v.pb(sh);
        si[i]=sh.size();
    }
    for(int i=0;i<m;i++){
        for(int j=0;j<=si[i];j++)
            ans[0][i][j]=ans[1][i][j]=(int)1e7;
    }
    for(int bit=0;bit<2;bit++){
        ch=s;
        for(int i=0;i<m;i++){
            ch+=v[i];
        }
       // cout << ch << endl;
        vector<int> p = suffix_array_construction(ch);
        vector<int> lcp = lcp_construction(ch,p);
        build_sparse(lcp);
        int sum=0;
        for(int i=0;i<p.size();i++){
            ran[p[i]]=i;
        }
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                int x = min(si[i],get_range(ran[n+sum],ran[j]));
                ans[bit][i][x]=min(ans[bit][i][x],j);
                //cout << i  << " " << j << " " << x <<" "<<ran[n+sum]<<" "<<ran[j]<<" "<<ans[bit][i][x]<< endl;
            }
            sum+=si[i];
        }
        reverse(all(s));
        for(int i=0;i<m;i++){
            reverse(all(v[i]));
        }
    }
    for(int i=0;i<m;i++){
        for(int j=si[i]-1;j>=0;j--){
            ans[0][i][j]=min(ans[0][i][j],ans[0][i][j+1]);
            ans[1][i][j]=min(ans[1][i][j],ans[1][i][j+1]);
        }
    }
    int res=0;
    for(int i=0;i<m;i++){
        for(int j=1;j<si[i];j++){
            int left = ans[0][i][j];
            int right = n-ans[1][i][si[i]-j]-1;
            //cout << i << " " << j << " " << left << " " << right << endl;
            if(left>=n || right>=n || left<0 || right<0)continue;
            if(right-left+1>=si[i]){
                res++;
                break;
            }
        }
    }
    cout << res;
 
    return 0;
}

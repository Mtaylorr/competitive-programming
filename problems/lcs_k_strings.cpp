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
const int N = 100005;
const double PI =4*atan(1);
const double eps = 1e-7;
const long long oo = 1e10;
const int K = 205;

int sp[19][N]; // sparse table

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
int logg[N];
int po[20];
void build_sparse(vector<int>const& lcp){
    int n=lcp.size();
    int log_n = logg[n];
    po[0]=1;
    for(int i=1;i<=log_n+1;i++){
        po[i]=2*po[i-1];
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<=log_n;j++){
            sp[j][i]=0;
        }
    }
    for(int i=0;i<n;i++){
        sp[0][i]=lcp[i];
    }
    for(int j=0;j<log_n;j++){
        for(int i=0;i+po[j+1]<=n;i++){
            sp[j+1][i]=min(sp[j][i],sp[j][i+po[j]]);
        }
    }
}

int get_range(int i ,int j){
    if(j<i)swap(i,j);
    j--;
    int l = (j-i+1);
    int k = logg[l];
    return min(sp[k][i],sp[k][j-(po[k])+1]);
}

int k; // number of strings
string s; 
int si[10];
int n;
int t;//test cases
int ran[N];
string ch;


int main(){
    FAST;
    cin >> t;
    while(t--){
        cin >> k;
        ch="";
        for(int i=0;i<k;i++){
            cin >> s;
            si[i]=s.size();
            ch+=s;
        }
        if(ch.size()==1){
            cout << 1 << endl;
            continue;
        }
        logg[1]=0;
        for(int i=2;i<=ch.size();i++){
            logg[i]=logg[i/2]+1;
        }

        vector<int> p =  suffix_array_construction(ch);
        vector<int> lcp = lcp_construction(ch,p);

        for(int i=0;i<p.size();i++){
            ran[p[i]]=i;
        }
        build_sparse(lcp);
        //cout << get_range(ran[1],ran[8]) << endl;
        int ans=0;
        for(int i=0;i<si[0];i++){
            int sum=si[0];
            int res=1e7;
            for(int j=1;j<k;j++){
                int anoth=0;
                for(int o=0;o<si[j];o++){
                    int left = min(si[j]-o,si[0]-i);
                    anoth=max(anoth,min(left,get_range(ran[i],ran[sum+o])));
                }
                sum+=si[j];
                res=min(res,anoth);
            }
            ans=max(ans,res);
        }
        cout << ans << endl;

    }
    return 0;
}

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
const int K = 26;

struct state {
    int len, link;
    map<char, int> next;
};

state st[N * 2];
int sz, last;

void sa_init() {
    st[0].len = 0;
    st[0].link = -1;
    sz++;
    last = 0;
}

void sa_extend(char c) {
    int cur = sz++;
    st[cur].len = st[last].len + 1;
    int p = last;
    while (p != -1 && !st[p].next.count(c)) {
        st[p].next[c] = cur;
        p = st[p].link;
    }
    if (p == -1) {
        st[cur].link = 0;
    } else {
        int q = st[p].next[c];
        if (st[p].len + 1 == st[q].len) {
            st[cur].link = q;
        } else {
            int clone = sz++;
            st[clone].len = st[p].len + 1;
            st[clone].next = st[q].next;
            st[clone].link = st[q].link;
            while (p != -1 && st[p].next[c] == q) {
                st[p].next[c] = clone;
                p = st[p].link;
            }
            st[q].link = st[cur].link = clone;
        }
    }
    last = cur;
}

void build_SA(string s){
     sa_init();
     for(int i=0;i<s.size();i++){
        sa_extend(s[i]);
     }
}
ll dp[N * 2];

ll  diff_substr(int v){
    if(dp[v]>=0)return dp[v];
    ll to=0;
    for(auto p: st[v].next){
        to +=diff_substr(p.se);
    }
    return dp[v]= 1 + to;

}

string lexicographically_k_th(ll k){
    ll res = diff_substr(0);
    int v=0;
    string to_return ="";
    bool cond=true;
    while(cond){
        if(k==0)break;
        cond=false;
        ll sum=0;
        ll last_sum=0;
        for(char c='a';c<='z';c++){
            if(st[v].next.count(c)==0)continue;
            last_sum=sum;
            sum+=dp[st[v].next[c]];
            if(sum>=k){
                k-=(last_sum+1);
                v=st[v].next[c];
                to_return+=c;
                cond=true;
                break;
            }
        }
    }
    if(k!=0){
        return "";
    }
    return to_return;
}


string s;
ll k;



int main(){
    FAST;
    memset(dp,-1,sizeof(dp));
    cin >> s;
    build_SA(s);
    cin >> k;
    string res = lexicographically_k_th(k);
    cout << res;

    return 0;
}

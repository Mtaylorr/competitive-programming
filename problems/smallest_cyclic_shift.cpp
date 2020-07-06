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

state st[N * 4];
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

string smallest_cyclic_shift(string s){
    int n=s.size();
    s+=s;
    build_SA(s);
    string ans="";
    int v=0;
    for(int i=0;i<n;i++){
        for(char c='a';c<='z';c++){
            if(st[v].next.count(c)==0)continue;
            ans+=c;
            v=st[v].next[c];
            break;
        }
    }
    return ans;
}

string s;
ll k;



int main(){
    FAST;
    cin >> s;
    cout << smallest_cyclic_shift(s) << endl;

    return 0;
}

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
    int firstpos;
    bool is_clone;
    map<char, int> next;
    vector<int> inv_link;
};

state st[N * 2];
int sz, last;

void sa_init() {
    st[0].len = 0;
    st[0].link = -1;
    st[0].firstpos=-1;
    st[0].is_clone = 0;
    sz++;
    last = 0;
}


void sa_extend(char c) {
    int cur = sz++;
    st[cur].len = st[last].len + 1;
    st[cur].firstpos = st[cur].len-1;
    st[cur].is_clone = 0;
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
            st[clone].firstpos = st[q].firstpos;
            st[clone].is_clone = 1;
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

void preprocess_all_occ(){
    for (int v = 1; v < sz; v++) {
        st[st[v].link].inv_link.pb(v);
    }
}

void output_all_occurrences(int v, int P_length) {
    if (!st[v].is_clone)
        cout << st[v].firstpos - P_length + 1 << endl;
    for (int u : st[v].inv_link)
        output_all_occurrences(u, P_length);
}


void all_occur(string p){
    preprocess_all_occ();
    int v=0;
    for(int i=0;i<p.size();i++){
        if(st[v].next.count(p[i])==0)return;
        v=st[v].next[p[i]];
    }
    output_all_occurrences(v,p.size());
}


string s;
string p;



int main(){
    FAST;
    cin >> s;
    build_SA(s);
    cin >> p;
    all_occur(p);


    return 0;
}

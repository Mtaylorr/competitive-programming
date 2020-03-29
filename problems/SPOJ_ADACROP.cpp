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
  
const int MOD = 998244353;
const int N = 1000005;
const double PI =4*atan(1);
const double eps = 1e-7;
const long long oo = 1e18;
 
const int AlPHA = 26, B = 30;
const ll MAXN = 100005;




ll getr(ll po){
    ll to_return =0;
    ll ten=1;
    for(int i=0;i<po;i++){
        to_return +=(rand()%10)*ten;
        ten*=10;
    }
    return to_return;
}
ll ra(ll x){
    ll y=getr(10);
    return y%(x)+1 ;
}

struct item {
    int key, prior;
    item * l, * r;
    int cnt;
};
typedef item * pitem;

pitem getnew(int prior,int key){
    pitem to = new item ;
    to->prior=prior;
    to->key=key;
    to->cnt=0;
    to->l=to->r=NULL;
    return to;
}
int cnt (pitem it) {
    return it ? it->cnt : 0;
}

void upd_cnt (pitem it) {
    if (it)
        it->cnt = cnt(it->l) + cnt(it->r) + 1;
}


void split (pitem t, int key, pitem & l, pitem & r) {
    if (!t)
        l = r = NULL;
    else if (key < t->key)
        split (t->l, key, l, t->l),  r = t;
    else
        split (t->r, key, t->r, r),  l = t;
    upd_cnt(t);
}

void insert (pitem & t, pitem it) {
    if (!t)
        t = it;
    else if (it->prior > t->prior)
        split (t, it->key, it->l, it->r),  t = it;
    else
        insert (it->key < t->key ? t->l : t->r, it);
    upd_cnt(t);
}

void merge (pitem & t, pitem l, pitem r) {
    if (!l || !r)
        t = l ? l : r;
    else if (l->prior > r->prior)
        merge (l->r, l->r, r),  t = l;
    else
        merge (r->l, l, r->l),  t = r;
    upd_cnt(t);
}

void erase (pitem & t, int key) {
    if (t->key == key)
        merge (t, t->l, t->r);
    else
        erase(key < t->key ? t->l : t->r, key);
    upd_cnt(t);
}


ll getval(pitem t, ll val){
    if(!t)return 0;
    if(t->key <= val){
        if(t->l){
            return 1+cnt(t->l)+getval(t->r,val);
        }else{
            return 1+getval(t->r,val);
        }
    }
    return getval(t->r,val);
}


ll n,q;
ll a[N];
ll x,y;
pitem numbers[N];
map<ll,ll> maa;
set<ll> ss;
ll cntt=0;
vector<pl> v;
ll res;


int main(){
    //ios::sync_with_stdio(0);
    freopen("easy.txt","r",stdin);
    cin >> n >> q;
    for(int i=0;i<n;i++){
        scanf("%lld",&a[i+1]);
        ss.insert(a[i+1]);
    }
    for(int i=0;i<q;i++){
        scanf("%lld %lld",&x,&y);
        x++;
        v.pb({x,y});
        ss.insert(y);
    }
    cntt=0;
    for(auto t:ss){
        maa[t]=cntt++;
    }
    ss.clear();
    for(int i=0;i<n;i++){
        a[i+1]=maa[a[i+1]];
    }
    for(int i=0;i<q;i++){
        v[i].s=maa[v[i].s];
    }
    maa.clear();
    for(int i=0;i<cntt;i++){
        numbers[i]=getnew(ra(1<<31),10000000);
    }
    for(int i=0;i<n;i++){
        insert(numbers[a[i+1]],getnew(ra(1<<31),a[i+1]));
    }
    for(int i=0;i<q;i++){
        x=v[i].f;
        y=v[i].s;
        erase(numbers[a[x]],x);
        a[x]=y;
        res = getval(numbers[a[x]],x);
        insert(numbers[a[x]],getnew(ra(1<<31),x));
        cout << res << endl;
    }
    
    return 0;
}
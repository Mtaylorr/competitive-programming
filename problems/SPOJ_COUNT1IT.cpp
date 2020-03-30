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
const int N = 700105;
const double PI =4*atan(1);
const double eps = 1e-7;
const long long oo = 1e18;
 
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
    ll y=getr(10);;
    return y%(x)+1 ;
}
 
struct item {
    ll key, prior;
    ll cnt;
    item * l, * r;
 
};
typedef item * pitem;
 
pitem getnew(ll prior, ll key){
    pitem to = new item ;
    to->prior=prior;
    to->cnt=0;
    to->key=key;
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
    else if (key <= t->key)
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
        insert (it->key <= t->key ? t->l : t->r, it);
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
 
 
void split1 (pitem t, pitem & l, pitem & r, int key, int add = 0) {
    if (!t)
        return void( l = r = 0 );
    int cur_key = add + cnt(t->l);
    if (key <= cur_key)
        split1 (t->l, l, t->l, key, add),  r = t;
    else
        split1 (t->r, t->r, r, key, add + 1 + cnt(t->l)),  l = t;
    upd_cnt (t);
}
 
ll getless(pitem t, ll x){
    if(!t)return 0;
    if(t->key<=x){
        if(t->l){
            return cnt(t->l)+1+getless(t->r,x);
        }else{
            return 1+getless(t->r,x);
        }
    }else{
        return getless(t->l,x);
    }
}
ll getzth(pitem t, ll x){
    pitem t1,t2,t3;
    split1(t,t1,t2,x);
    split1(t2,t2,t3,1);
    ll to = t2->key;
    merge(t,t1,t2);
    merge(t,t,t3);
    return to;
}
 
ll n,q;
pitem t;
ll x;
ll ty;
ll o;
int main(){
    //ios::sync_with_stdio(0);
    //freopen("easy.txt","r",stdin);
    srand (time(NULL));
    scanf("%lld %lld",&n,&q);
    scanf("%lld",&x);
    t= getnew(ra(1<<31),x);
    for(int i=1;i<n;i++){
        scanf("%lld",&x);
        insert(t,getnew(ra(1<<31),x));
    }
    ll cn=0;
    for(int i=0;i<q;i++){
        scanf("%lld %lld",&ty,&x);
        if(ty==1){
            o  = getless(t,x);
            insert(t,getnew(ra(1<<31),x+o));
            cn++;
        }else if(ty==2){
            o= getless(t,x);
            printf("%lld\n",o);
        }else{
            if(x>n+cn){
                printf("invalid\n");
                continue;
            }
            //cout << "why " << endl;
            o =getzth(t,x-1);
            printf("%lld\n",o);
        }
    }
    return 0;
}
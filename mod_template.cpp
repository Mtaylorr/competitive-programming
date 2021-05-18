#include <bits/stdc++.h>
     
using namespace std;
typedef long long ll;
typedef vector<ll> vl ;
typedef pair<ll,ll> pl;
     
#define mp make_pair
#define pb push_back
#define fi first
#define si second
#define all(v) (v).begin(),(v).end()
#define max(a,b) (a>b ? a : b)
#define min(a,b) (a<b ? a : b)
     
const int MOD = 998244353;
const int N = 1000005;
const double PI =4*atan(1);
const double eps = 1e-7;
const long long oo = 1e18;

ll fact[N];
ll invfact[N];

ll mul(ll u , ll v, ll mod=MOD){
	return ((u%mod)*(v%mod))%mod;
}
ll add(ll u, ll v, ll mod=MOD){
	return ((u%mod)+(v%mod)+mod)%mod;
}

ll sub(ll u, ll v , ll mod=MOD){
	return ((u%mod)-(v%mod)+mod)%mod;
}

ll powe(ll u, ll v, ll mod=MOD){
	ll ans=1;
	ll acc=u;	
	while(v){
		if(v%2){
			ans=mul(ans,acc,mod);
		}
		acc = mul(acc,acc,mod);
		v/=2;
	}
	return ans;
}
ll  inv(ll u,ll mod=MOD){
	return powe(u,mod-2,mod);
}

void init_fact(ll n, ll mod=MOD){
	fact[0]=fact[1]=1;
	for(int i=2;i<=n;i++){
		fact[i]=mul(i,fact[i-1],mod);
	}
}

ll cnk (ll n , ll k){
    if(k>n)return 0;
    if(n==0)return 0;
    ll ans = mul(fact[n],invfact[k]);
    ans= mul(ans,invfact[n-k]);
    return ans;
}

void init_inv_fact(ll n, ll mod=MOD){
	for(int i=0;i<=n;i++){
		invfact[i]=powe(fact[i],mod-2,mod);
	}
}
void init(ll n, ll mod=MOD){
	init_fact(n,mod);
	init_inv_fact(n,mod);
}


int main(){
    ios::sync_with_stdio(0);
    freopen("easy.txt","r",stdin);
    
    return 0;
}







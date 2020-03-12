#include <bits/stdc++.h>
 
    using namespace std;
    typedef long long ll;
    typedef vector<ll> vl ;
 
    #define mp make_pair
    #define pb push_back
    #define f first
    #define s second
    #define all(v) (v).begin(),(v).end()
 
    const int MOD = 998244353;
    const int N = 10000005;
    const double PI =4*atan(1);
    
    ll a,b,c,d,m,x,y;
    ll tab[N];
    ll u[N];
 
    ll _sieve_size;bitset<10000010> bs;
    void sieve(ll upperbound) {
        _sieve_size = upperbound + 1;bs.set();bs[0] = bs[1] = 0;
        u[1]=1;
        for (ll i = 2; i <= _sieve_size; i++) if (bs[i]) {
        u[i]=-1;
        for (ll j = 2*i; j <= _sieve_size; j += i) {
			bs[j]=0;
	        if(j%(i*i)==0)u[j]=0;
	        u[j]*=u[i];}
        	
        }
    }
  
    int main(){
        ios::sync_with_stdio(0);
        cin >> a >> b >> c >> d;
        for(int i=1;i<=10000000;i++){
        	u[i]=1;
        }
        sieve(10000001);
        ll ans;
        ans=0;
        for(int i=1;i<=b;i++){
        	ll x=b/i;
        	ll y=(a-1)/i;
        	ans += (y-x)*u[i] *((c-1)/i-(d)/i);
        }
        cout << ans;
        return 0;
    }
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

struct point{
	ll x,y;
	int id;
};
struct cmp_x{
	bool operator()(const point & a, const point & b)const{
		return (a.x<b.x) ||( a.x==b.x && a.y<b.y);
	}
};

struct cmp_y{
	bool operator()(const point & a , const point & b)const{
		return a.y<b.y;
	}
};

int n;
vector<point> a;
vector<point> t;

long double minper ;
pair<int,pair<int,int> > besttriplet;

long double get_dist(const point & a, const point & b){
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

void update(const point & a, const point & b, const point & c){
	long double per = get_dist(a,b)+get_dist(a,c)+get_dist(b,c);
	if(per<minper){
		minper = per;
		besttriplet={a.id, {b.id,c.id}};
	}
}

void rec(int l , int r){
	if(r-l<=3){
		for(int i=l;i<r;i++){
			for(int j=i+1;j<r;j++){
				for(int k=j+1;k<r;k++)
					update(a[i],a[j],a[k]);
			}
		}
		sort(a.begin()+l, a.begin()+r, cmp_y());
		return ;
	}
	int mid=(l+r)/2;
	ll midx = a[mid].x;
	rec(l,mid);
	rec(mid,r);

	merge(a.begin()+l,a.begin()+mid, a.begin()+mid, a.begin()+r, t.begin(),cmp_y());
	copy(t.begin(),t.begin()+(r-l), a.begin()+l);

	int tsz=0;
	for(int i=l;i<r;i++){
		if(abs(a[i].x-midx)<minper/2){
			for(int j=tsz-2;j>=0 && a[i].y-t[j].y<minper/2;j--){
				for(int k=tsz-1;k>j;k--){
					update(a[i],t[j],t[k]);
				}
			}
			t[tsz++]=a[i];
		}
	}

}

void init(){
	t.resize(n);
	sort(a.begin(),a.end(),cmp_x());
	minper = 4e18;
}


int main(){
    FAST;
    cin >> n;
    a.resize(n);
    for(int i=0;i<n;i++){
        ll x,y;
        cin >> x >> y;
        a[i]={x,y,i};
    }
    init();
    rec(0,n);
    cout << besttriplet.fi+1 << " " << besttriplet.se.fi+1 << " " << besttriplet.se.se +1 << endl;
    cout << fixed <<  setprecision(3) <<  minper << endl;
    return 0;
}

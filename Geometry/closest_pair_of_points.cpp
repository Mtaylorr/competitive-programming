// source  https://cp-algorithms.com/geometry/nearest_points.html
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

long double mindist ;
pair<int,int> bestpair;

void update(const point & a, const point & b){
	long double dist = sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
	if(dist<mindist){
		mindist = dist;
		bestpair={a.id, b.id};
	}
}

void rec(int l , int r){
	if(r-l<=3){
		for(int i=l;i<r;i++){
			for(int j=i+1;j<r;j++){
				update(a[i],a[i]);
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
		if(abs(a[i].x-midx)<mindist){
			for(int j=tsz-1;j>=0 && a[i].y-t[j].y<mindist;j--){
				update(a[i],t[j]);
			}
			t[tsz++]=a[i];
		}
	}

}

void init(){
	t.resize(n);
	sort(a.begin(),a.end(),cmp_x());
	mindist = 4e18;
	bestpair={-1,-1};
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
    cout << bestpair.fi+1 << " " << bestpair.se+1 << endl;
    return 0;
}

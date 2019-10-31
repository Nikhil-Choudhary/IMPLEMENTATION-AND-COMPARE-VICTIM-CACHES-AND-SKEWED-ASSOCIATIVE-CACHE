    #include <bits/stdc++.h>
using namespace std;

typedef long long int ll;
typedef long double ld;
typedef unsigned long long int ull;

#define FOR(i,vv,n) for(ll i=vv;i<n;i++)
#define FORR(i,n,vv) for(ll i=n-1;i>=vv;i--)
#define ve vector
#define maxe(v) *max_element(v.begin(),v.end())
#define mine(v) *min_element(v.begin(),v.end())
#define pb push_back
#define pf push_front
#define ppb pop_back
#define ppf pop_front
#define FAST ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define mp make_pair
#define M 1000000007
#define precise cout.precision(18)

ve<ll> next(ve<ll> v,ll m){
	ll k=0;
	FOR(i,0,v.size()){
		k+=v[i]*pow(2,i);
	}
	k=k+1;
	ve<ll> d;
	while(k>0){
		d.pb(k%2);
		k=k/2;
	}
	ll p=d.size();
	FOR(i,0,m-p)
	d.pb(0);
	return d;
}


int main(){
 
	#ifndef ONLINE_JUDGE
    // for getting input from input.txt
    freopen("input.txt", "r", stdin);
    // for writing output to output.txt
    freopen("output.txt", "w", stdout);
	#endif
    FAST

ll m;
cin>>m;
ll r=0;
ve <ll> ini;

FOR(i,0,m)
{ini.pb(0);
}
FOR(i,0,10000){
	ve <ll> ini1;
	ll r=rand()%3;
	if(r==0){
		FORR(j,ini.size(),0)
		cout<<ini[j];
	}
	else if(r==1){
		FOR(j,0,ini.size())
		ini1.pb(rand()%2);
		ini=ini1;
		FORR(j,ini.size(),0)
		cout<<ini[j];
	}
	else{

		ini=next(ini,m);
		FORR(j,ini.size(),0)
		cout<<ini[j];
	}
	cout<<endl;

}


return 0;
}
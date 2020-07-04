#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
typedef long double ld;
typedef pair<ld, ll> pii; 

#define sc(n) scanf("%lld",&n)
#define scc(n,m) scanf("%lld %lld",&n,&m)
#define sccc(x,y,z) scanf("%lld %lld %lld",&x,&y,&z)
#define pf(n) printf("%lld\n",n)
#define pff(n,m) printf("%lld %lld\n",n,m)
#define pfn printf("\n")
#define pb push_back
#define fi first
#define se second
#define mem(n,m) memset(n,m,sizeof(n))
#define inf 1e18

vector<ll> mp[110005];                                  //Stores The Graph
pair<ll,ll> cord[110005];                               //Stored The Cordinates
unordered_map<ll,unordered_map<ll,ll>> wt{};            //Stores Edge Weights
ld pi[110005];                                          //Stores Potential Of Each Vertex
ld dist[110005];                                        //Stores Distance Estimate Of Each Vertex
bool visit[110005];                                     //Stores The Status Of The Vertex
ll prevv[110005];                                       //Storing The Parent
priority_queue<pii, vector<pii>, greater<pii>> pq;      //Extract-Min Data-Structure


int main()
{
	ll n{},m{};
	scc(n,m);
	for(ll i=1;i<=n;i++)
	{
		ll x{},y{};
		scc(x,y);
		cord[i]=make_pair(x,y);
	}
	for(ll i=1;i<=m;i++)
	{
		ll x{},y{},l{};
		sccc(x,y,l);
		mp[x].push_back(y);
		wt[x][y]=l;
	}
	ll q{};
	sc(q);
	while(q--)
	{
		ll x{},y{};
		scc(x,y);
		while(!pq.empty())
		{
			pq.pop();
		}
		for(ll i=1;i<=n;i++)
		{
			visit[i]=false;
			prevv[i]=-1;
			ld xx=(ld)abs(cord[y].fi-cord[i].fi);
			ld yy=(ld)abs(cord[y].se-cord[i].se);
			pi[i]=(ld)sqrt(xx*xx + yy*yy);
			dist[i]=inf+pi[i];
		}
		dist[x]=0.0;
		for(ll i=1;i<=n;i++)
		{
			pq.push(make_pair(dist[i],i));
		}
		while(!pq.empty())
		{
			ll p=pq.top().se;
			pq.pop();

			if(visit[p])
				continue;
			visit[p]=true;
			
			for(auto w:mp[p])
			{
				if(dist[p]<inf)    
				if(dist[w]>dist[p]+wt[p][w])
				{
					dist[w]=dist[p]+wt[p][w];
					prevv[w]=p;
					pq.push({dist[w],w});
				}
			}

			if(p==y)
				break;
		}
		ll ans{};
		while(prevv[y]!=-1 && x!=y)
		{
			ans+=wt[prevv[y]][y];
			y=prevv[y];
		}
		if(x==y)
			pf(ans);
		else
			printf("-1\n");
	}
	return 0;
}


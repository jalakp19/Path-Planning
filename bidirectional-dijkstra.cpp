#include<bits/stdc++.h>
using namespace std;

typedef unsigned long long int ull;
typedef long long int ll;
typedef long double ld;
typedef pair<ll, ll> pi; 

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

vector<ll> mp[1000005];
vector<ll> mpr[1000005];
unordered_map<ll,unordered_map<ll,ll>> wt{};
unordered_map<ll,unordered_map<ll,ll>> wtr{};
ll dist[1000005];
ll distr[1000005];
bool visit[1000005];
bool visitr[1000005];

priority_queue<pi, vector<pi>, greater<pi> > pq; 
priority_queue<pi, vector<pi>, greater<pi> > pqr; 

int main()	
{
	ll n{},m{},x{},y{},l{},q{};
	scc(n,m);
	for(ll i=0;i<m;i++)
	{
		sccc(x,y,l);
		mp[x].push_back(y);
		mpr[y].push_back(x);
		wt[x][y]=l;
		wtr[y][x]=l;
	}
	sc(q);
	while(q--)
	{
		while(!pq.empty())
		{
			pq.pop();
		}
		while(!pqr.empty())
		{
			pqr.pop();
		}
		scc(x,y);
		for(ll i=1;i<=n;i++)
		{
			visit[i]=false;
			visitr[i]=false;
			dist[i]=LLONG_MAX;
			distr[i]=LLONG_MAX;
		}
		dist[x]=0;
		distr[y]=0;
		set<ll> proc{};
		set<ll> procr{};
		bool flag=true;

		for(ll i=1;i<=n;i++)
		{
			pq.push({dist[i],i});
			pqr.push({distr[i],i});
		}

		while(!pq.empty() && !pqr.empty())
		{
			ll p=pq.top().se;
			pq.pop();
			if(!visit[p])
			{
				visit[p]=true;

				for(auto w:mp[p])
				{
					if(dist[p]!=LLONG_MAX)    
					if(dist[w]>dist[p]+wt[p][w])
					{
						dist[w]=dist[p]+wt[p][w];
						pq.push({dist[w],w});
					}
				}
				proc.insert(p);

				if(procr.find(p)!=procr.end())
				{
					flag=false;
					break;
				}
			}

			p=pqr.top().se;
			pqr.pop();
			if(!visitr[p])
			{
				visitr[p]=true;

				for(auto w:mpr[p])
				{
					if(distr[p]!=LLONG_MAX)    
					if(distr[w]>distr[p]+wtr[p][w])
					{
						distr[w]=distr[p]+wtr[p][w];
						pqr.push({distr[w],w});
					}
				}
				procr.insert(p);

				if(proc.find(p)!=proc.end())
				{
					flag=false;
					break;
				}
			}
		}

		if(!flag)
		{
			ll ans=LLONG_MAX;
			for(auto u:proc)
			{
				if(dist[u]!=LLONG_MAX && distr[u]!=LLONG_MAX)
				if(dist[u]+distr[u]<ans)
					ans=dist[u]+distr[u];
			}
			for(auto u:procr)
			{
				if(dist[u]!=LLONG_MAX && distr[u]!=LLONG_MAX)
				if(dist[u]+distr[u]<ans)
					ans=dist[u]+distr[u];
			}
			if(ans==LLONG_MAX)
				printf("-1\n");
			else
				pf(ans);
		}
		else
		{
			printf("-1\n");
		}
	}
	return 0;
}


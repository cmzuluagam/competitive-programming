#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MAXN = 1005; // maximo numero de vertices
const int INF = 1000000000; // infinito
struct edge {
    int a, b, cap, flow;
};

int n, s, t, d[MAXN], ptr[MAXN], q[MAXN], ngroup[MAXN];
vector<edge> e;
vector<int> g[MAXN];

void add_edge (int a, int b, int cap) {
		edge e1 = { a, b, cap, 0 };
    edge e2 = { b, a, 0, 0 };
    g[a].push_back ((int) e.size());
    e.push_back (e1);
    g[b].push_back ((int) e.size());
    e.push_back (e2);
}

bool bfs() {
    int qh=0, qt=0;
    q[qt++] = s;
    memset (d, -1, n * sizeof d[0]);
    d[s] = 0;
    while (qh < qt && d[t] == -1) {
        int v = q[qh++];
        for (size_t i=0; i<g[v].size(); ++i) {
            int id = g[v][i],
                to = e[id].b;
            if (d[to] == -1 && e[id].flow < e[id].cap) {
                q[qt++] = to;
                d[to] = d[v] + 1;
            }
        }
    }
    return d[t] != -1;
}

int dfs (int v, int flow) {
    if (!flow)  return 0;
    if (v == t)  return flow;
    for (; ptr[v]<(int)g[v].size(); ++ptr[v]) {
        int id = g[v][ptr[v]],
            to = e[id].b;
        if (d[to] != d[v] + 1)  continue;
        int pushed = dfs (to, min (flow, e[id].cap - e[id].flow));
        if (pushed) {
            e[id].flow += pushed;
            e[id^1].flow -= pushed;
            return pushed;
        }
    }
    return 0;
}

int dinic() {
    int flow = 0;
    for (;;) {
				if (!bfs())  break;
        memset (ptr, 0, n * sizeof ptr[0]);
        while (int pushed = dfs (s, INF))
            flow += pushed;
		}
    
    return flow;
}

int main(){
 // freopen("vodka.in", "r", stdin);
  int m, a;
  while(~scanf("%d%d", &n, &m)){
		s = 0;
		t = n + m + 1;
		for(int i = 0; i < MAXN; i ++)
      g[i].clear();
    e.clear();
		int sum = 0, w;
		for(int i = 0; i < n; i ++){
			scanf("%d", &w);
			add_edge(i + 1, t, w);
		}
		
		for(int i = 0; i < m; i ++)
			scanf("%d", &ngroup[i]);
		
		for(int i = 0; i < m; i ++){
			scanf("%d", &w);
			sum += w;
			add_edge(s, i + n + 1, w);
			for(int j = 0; j < ngroup[i]; j ++){
				scanf("%d", &a);
				add_edge(i + n + 1, a, INF);
			}
		}
		n = n + m + 2;
    
    int ans = dinic();
    
    printf("%d\n", sum - ans);
  }
  return 0;
}


/**
 * Author: Matheus Leal
 * Date: 2020-01-15
 * Description: Achar um Euler TOur
 * Time: O(N + M)
 * Usage: 
 * Status:tested
 */

/*
  grafo[x] guarda um pair (v, w) indicando que uma aresta liga (x, v) e possui id = w
  g[x] = grau do vertice x
  tour = ciclo do tipo [comeco] ... [comeco]
  del[x] = (1, se aresta ja foi utilizada. 0 caso contrário)
  tour_e = ids das arestas usadas . se necessário, trocar vector<int> pilha para vector<pii> pilha
  ver comentarios para isso ^
  caso seja um tour incompleto ([comeco] ... [fim]) lembrar de dar reverse no tour
  funciona com self loop (mas deve aumentar em 2 o grau/botar 2 vezes no grafo) -> tested on 527E - #296 div2
  Se for incompleto e direcionado lembrar de ver que degOut[incio] - degIn[inicio] == 1, degIn[fim] - getOut[fim]==1
  E degIn[i] == degOut[i] para todo o resto. 
  Tested on https://codeforces.com/gym/102411/problem/C and https://cses.fi/problemset/task/1693
*/

template<int direcionado>
struct EulerTour{
	int n,m;
	EulerTour(){}
	EulerTour(int N,int M){
		n = N,m = M;
    g = vi(n+10,0);
		grafo = vector<vector<pii>>(n + 10);
		del = vi(m + 10,0);
	}
	vi g; 
	vi del;
	vector<vector<pii>> grafo;
	vi tour;
	vi tour_e;
	inline void find(int u){
	    vector<pii>pilha;
	    pilha.pb(pii(u,-1));
	    while(!pilha.empty()){
	        int x = pilha.back().ff;
	        int e = pilha.back().ss;
	        while(!grafo[x].empty() and del[grafo[x].back().ss]){
	            g[x]--;
	            grafo[x].pop_back();
	        }
	        if(!g[x]){
	            tour.pb(x);
	            tour_e.pb(e);
	            pilha.pop_back();
	            continue;
	        }
	        auto v = grafo[x].back();
	        grafo[x].pop_back();
	        g[x] --;
	        del[v.ss] = 1;
	        pilha.pb(v);
	    }
	}

	// USAGE:
	int ID = 0;

	void addEdge(int a,int b){
	  ID++;
	  grafo[a].pb(pii(b,ID));
	  g[a]++;
	  if(!direcionado){
	    grafo[b].pb(pii(a,ID));
	    g[b]++;
	  }
	}

  // ASSUME que existe um tour
	vi get_tour(int ini){
		// destroi o grafo
		tour.clear();
		tour_e.clear();
		find(ini);
    if(direcionado)reverse(all(tour)),reverse(all(tour_e));
  	return tour;
	}

};

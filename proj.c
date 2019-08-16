/*Projeto 2 ASA*/
/*2015/2016*/
/*81186 - Stéphane Duarte*/
/*81858 - João Oliveira*/
 
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
 
/*-----------------------------------------------------------
                         Grafo e arcos
-------------------------------------------------------------*/
 
struct edge{
    int u, v, w;
};
 
typedef struct edge *Edge;
 
 
struct graph{
    int V, E;
     
    Edge edges;
};
 
typedef struct graph *Graph;
  
 
Graph graphInit(int V, int E){
    Graph g = malloc(sizeof(struct graph));
    g->V = V;
    g->E = E;
  
    g->edges = (Edge) malloc(E*sizeof(struct edge));
  
    return g;
}
 
/*-----------------------------------------------------------
                     Algoritmo Bellman-Ford
-------------------------------------------------------------*/
 
int *custo;
 
void BellmanFord(Graph g, int src){
    int V = g->V;
    int E = g->E;
     
    int i, j, u, v, peso, relaxado = 1;
    
    for (i = 0; i < V; i++){
        custo[i] = INT_MAX;
    }
    custo[src] = 0;
 
    for (i = 1; i <= V-1; i++){
        if(relaxado){
            relaxado = 0;
            for (j = 0; j < E; j++){
                u = g->edges[j].u;
                v = g->edges[j].v;
                peso = g->edges[j].w;
                if (custo[u] != INT_MAX && custo[u] + peso < custo[v]){
                    custo[v] = custo[u] + peso;
                    relaxado = 1;
                }
            }
        }
        else{
            break;
        }
    }
}
 
/*-----------------------------------------------------------
                            MAIN
-------------------------------------------------------------*/
 
int main(){
    int n, f, c, fi, u, v, w, i, j;
    Graph g;
     
    scanf("%d %d %d", &n, &f, &c);
    g = graphInit(n, c);
    
    int *filiais = (int*)malloc(sizeof(int)*f);
     
    for (i=0; i<f; i++){
    	scanf("%d", &fi);
    	filiais[i] = fi;
    }
    
    custo = (int*)malloc(sizeof(int)*n);
    
    int matriz[f][n];
    
    int *custototal = (int*)malloc(sizeof(int)*n);
    
    for(i=0; i<c; i++){
        scanf("%d %d %d", &u, &v, &w);
        g->edges[i].u = u-1;
        g->edges[i].v = v-1;
        g->edges[i].w = w;
    }
    
    for(i=0; i<f; i++){
      BellmanFord(g, (filiais[i]-1));
      for (j=0; j<n; j++){
	  matriz[i][j] = custo[j];
      }
    }
    
    
    /* IMPRIMIR RESULTADOS */
    int localidade = -1, custoatual = INT_MAX;
    
    for (i = 0; i < n; i++){
      custototal[i] = 0;
      for (j = 0; j < f; j++){
		if (matriz[j][i] == INT_MAX){
	  	custototal[i] = INT_MAX;
	  	break;
		}
		custototal[i] += matriz[j][i] ;
      }
      if (custototal[i] < custoatual){
		custoatual = custototal[i];
		localidade = i;
      }
    }
    
    if (localidade == -1){
      printf("N\n");
    }

    else{
      printf("%d %d\n", (localidade+1), custoatual);
      for (i = 0; i < f; i++){
		printf("%d ", matriz[i][localidade]);
      }
      printf("\n");
    }
     
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define WHITE 2
#define GRAY 1
#define BLACK 0
#define NIL -1
#define myPositiveInfinite 2147483647
#define MAXV 1000

struct edge
{
    int vertex;
    // int weight;
    struct edge *next;
};

struct graph
{
    int n_vertex;
    int m_edges;
    struct edge *Adj[MAXV + 1];
};

struct graph *readGraph (int vertices, int edges) {
    int idVertex, idEdge, u, v;
    struct graph *G;
    struct edge *tempEdge;

    G = (struct graph *) malloc(sizeof(struct graph));
    G->n_vertex = vertices;
    G->m_edges = edges;

    for(idVertex = 1; idVertex <= G->n_vertex; idVertex++)
        G->Adj[idVertex] = NULL;

    for(idEdge = 1; idEdge <= G->m_edges; idEdge++) {
        scanf("%d %d", &u, &v);
        tempEdge = (struct edge *) malloc(sizeof(struct edge));
        tempEdge->vertex = v;
        tempEdge->next = G->Adj[u];
        G->Adj[u] = tempEdge;
    }
    return G;
}


void printGraph (struct graph *G) {
    int idVertex;
    struct edge *tempEdge;

    if (G != NULL)
    {
        printf("Representation for graph's adjacent lists: \n");
        for(idVertex = 1; idVertex <= G->n_vertex; idVertex++)
        {
            printf("[%d]: ", idVertex);
            tempEdge = G->Adj[idVertex];
            while(tempEdge != NULL)
            {
                printf(" -> %d", tempEdge->vertex);
                tempEdge = tempEdge->next;
            }
            printf(" -> NULL\n");
        }
    }
    else
        printf("Empty Graph.\n");
}


struct graph *deleteGraph (struct graph *G) {
    int idVertex;
    struct edge *actualEdge, *nextEdge;

    for (idVertex = 1; idVertex <= G->n_vertex; idVertex++) {
        actualEdge = G->Adj[idVertex];
        while(actualEdge != NULL)
        {
            nextEdge = actualEdge->next;
            free (actualEdge);
            actualEdge = nextEdge;
        }
    }
    free (G);
    G = NULL;
    return G;
}

void BFS (struct graph *G, int s, int color[], int d[], int pi[]) {
    int u, v, Q[MAXV + 1], head = 1, tail = 1;
    struct edge *tempEdge;
    
    for (u = 1; u <= G->n_vertex; u++) {
        color[u] = WHITE;
        d[u] = myPositiveInfinite;
        pi[u] = NIL;
    }
    
    color[s] = GRAY;
    d[s] = 0;
    pi[s] = NIL;
    Q[tail] = s;
    tail++;
    
    while (head < tail) {
        u = Q[head];
        head++;
        tempEdge = G->Adj[u];
        
        while (tempEdge != NULL) {
            v = tempEdge->vertex;
            
            if (color[v] == WHITE) {
                color[v] = GRAY;
                d[v] = d[u] + 1;
                pi[v] = u;
                Q[tail] =v;
                tail++;
            }
            tempEdge = tempEdge->next;
        }
        color[u] = BLACK;
    }
}

void solver (struct graph *G, int s) {
    int color[MAXV + 1], d[MAXV + 1], pi [MAXV + 1], idVertex;
    int answer = 0;
    
    BFS (G, s, color, d, pi);
    
    for (idVertex = 1; idVertex <= G->n_vertex; idVertex++) {
        if (d[idVertex] != myPositiveInfinite && d[idVertex] != 0)
            answer++;
    }
    printf ("%d\n", answer);
}

int main () {
    int vertices, edges, q, s;
    struct graph *G;

    scanf ("%d %d", &vertices, &edges);
    G = readGraph (vertices, edges);
    scanf ("%d", &q);
    while (q--) {
        scanf ("%d", &s);
        solver(G, s);
    }
    G = deleteGraph (G);
    return 0;
}
#pragma once
typedef struct edge {
    int startEdge;
    int endEdge;
    struct edge* next;
}edge_t;
typedef struct {
    int Weight;
    int isVisited;
}vertex;
vertex* vertexes;
edge_t* creatFirstEdge(int startEdge, int endEdge);
edge_t* addEdge(edge_t* head, int startEdge, int endEdge);
void removeList(edge_t* head);
void dfs(edge_t* head, int number1);
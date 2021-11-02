#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include "graph.h"
#define TRUE 1
#define FALSE 0
int numEdges = 0;
int numVertex = 0;
vertex* vertexes;
edge_t* creatFirstEdge(int startEdge, int endEdge) {
    edge_t* tmp = (edge_t*)malloc(sizeof(edge_t));
    if (!tmp) {
        printf("Error allocating memory\n");
        exit(1);
    }
    tmp->next = NULL;
    tmp->startEdge = startEdge;
    tmp->endEdge = endEdge;
    return tmp;
}
edge_t* addEdge(edge_t* head, int startEdge, int endEdge) {
    if (!head) {
        printf("Error the pointer was NULL\n\n");
        exit(1);
    }
    edge_t* curNode = head;
    edge_t* tmp = (edge_t*)malloc(sizeof(edge_t));
    if (!tmp) {
        printf("Error allocating memory\n");
        exit(1);
    }
    tmp->next = NULL;
    tmp->startEdge = startEdge;
    tmp->endEdge = endEdge;
    while (curNode->next != NULL) {
        curNode = curNode->next;
    }
    curNode->next = tmp;
    return head;
}
void removeList(edge_t* head) {
    while (head != NULL) {
        edge_t* p;
        p = head;
        head = head->next;
        free(p);
    }
}
void dfs(edge_t* head, int weight) {
    edge_t* curEdge = head;
    fprintf(stdout, "%d ", weight);
    int minVertexNum = numVertex;
    vertexes[weight].isVisited = TRUE;
    int j = 0;
    while (1) {
        if (j == 1) {
            break;
        }
        curEdge = head;
        minVertexNum = numVertex;
        for (int i = 0; i < numEdges; i++) {
            if (curEdge->startEdge == weight) {
                if (vertexes[curEdge->endEdge].isVisited == FALSE) {
                    if (minVertexNum > curEdge->endEdge) {
                        minVertexNum = curEdge->endEdge;
                    }
                }
            }
            if (curEdge->endEdge == weight) {
                if (vertexes[curEdge->startEdge].isVisited == FALSE) {
                    if (minVertexNum > curEdge->startEdge) {
                        minVertexNum = curEdge->startEdge;
                    }
                }
            }
            curEdge = curEdge->next;
        }
        j++;
        if (minVertexNum != numVertex) {
            dfs(head, minVertexNum);
            j = 0;
        }
    }
}
int main(void) {
    edge_t* head = NULL;
    int startEdge;
    int endEdge;
    scanf("%d", &numVertex);
    vertexes = (vertex*)malloc(numVertex * sizeof(vertex));
    if (!vertexes) {
        printf("Error allocating memory\n");
        exit(1);
    }
    for (int i = 0; i < numVertex; i++) {
        vertexes[i].Weight = i;
        vertexes[i].isVisited = FALSE;
    }
    if (fscanf(stdin, "%d %d", &startEdge, &endEdge) != EOF) {
        head = creatFirstEdge(startEdge, endEdge);
        numEdges++;
    }
    while (fscanf(stdin, "%d %d", &startEdge, &endEdge) != EOF) {
        head = addEdge(head, startEdge, endEdge);
        numEdges++;
    }
    dfs(head, 0);
    removeList(head);
    free(vertexes);
    return 0;
}
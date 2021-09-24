#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_ARRAY_SIZE 50

typedef struct List {
    char* firstname;
    char* lastname;
    char* middlename;
    struct List* next;
}List_t;
List_t* newNode();
void dataStructureSwap(List_t* node_1, List_t* node_2);
void printNode(List_t* node);
void printList(List_t* root);
void addInfo(List_t* node, char* info, const char* structFieldName);
int InsertInPos(char* nodeName, char* nodeInListName, List_t** node, List_t** nodeInList);
void sortNode(List_t* root, List_t* node);
void findNode(List_t* root);
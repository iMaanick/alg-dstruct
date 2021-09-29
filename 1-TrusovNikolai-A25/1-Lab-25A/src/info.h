#pragma once
#define MAX_ARRAY_SIZE 50
#define POS_WAS_FOUND 1 
#define ANOTHER_POS_WAS_FOUND 2
#define POS_WAS_NOT_FOUND 0
typedef struct List {
    char* firstname;
    char* lastname;
    char* middlename;
    struct List* next;
}List_t;
List_t* newNode();
void printNode(List_t* node);
void printList(List_t* root);
void addInfo(List_t* node, char* info, const char* structFieldName);
int insertInPos(char* nodeName, char* nodeInListName, List_t** node, List_t** nodeInList, List_t** head);
List_t* insertInFrontOfNode(List_t** node, List_t** nodeInList, List_t* head);
List_t* sortNode(List_t* root, List_t* node);
void findNode(List_t* root);
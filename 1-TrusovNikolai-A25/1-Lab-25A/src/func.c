#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include"info.h"
List_t* newNode() {
    List_t* tmp = (List_t*)malloc(sizeof(List_t));
    if (!tmp) {
        printf("Error allocating memory\n");
        exit(1);
    }
    tmp->next = NULL;
    return tmp;
}
void printNode(List_t* node) {
    if (node != NULL) {
        printf("%s ", node->lastname);
        printf("%s ", node->firstname);
        printf("%s\n", node->middlename);
    }
}
void printList(List_t* root) {
    while (root != NULL) {
        printNode(root);
        root = root->next;
    }
}
void addInfo(List_t* node, char* info, const char* structFieldName) { // F-firstname, L-Lastname, M-Middlename
    if ((structFieldName != "F") && (structFieldName != "L") && (structFieldName != "M")) {
        printf("There are only three structure fields where you can write data: lastname - 'L' firstname - 'F' middlename - 'M'");
        exit(2);
    }
    if (!node) {
        printf("Error the pointer was NULL\n");
        exit(3);
    }
    if (structFieldName == "F") {
        node->firstname = (char*)malloc(strlen(info) + 1);
        strcpy(node->firstname, info);
    }
    if (structFieldName == "L") {
        node->lastname = (char*)malloc(strlen(info) + 1);
        strcpy(node->lastname, info);
    }
    if (structFieldName == "M") {
        node->middlename = (char*)malloc(strlen(info) + 1);
        strcpy(node->middlename, info);
    }
}
List_t* insertInFrontOfNode(List_t** node, List_t** nodeInList, List_t* head) {
    List_t* tmp;
    tmp = head;
    if (*nodeInList == head) {
        (*node)->next = head;
        head = *(node);
        return head;
    }
    else {
        while (tmp->next != *(nodeInList)) {
            tmp = tmp->next;
        }
        (*node)->next = tmp->next;
        tmp->next = *node;
    }
    return head;
}
int insertInPos(char* nodeName, char* nodeInListName, List_t** node, List_t** nodeInList, List_t** head) {
    if (strcmp(nodeName, nodeInListName) < 0) {
        *head = insertInFrontOfNode(node, nodeInList, *head);
        return posWasFound;//position was found
    }
    else {
        if ((*nodeInList)->next == NULL) {
            (*nodeInList)->next = (*node);
            return anotherPosWasFound;//position was found
        }
        else {
            (*nodeInList) = (*nodeInList)->next;
            return posWasNotFound;//position was not found
        }
    }
}
List_t* sortNode(List_t* root, List_t* node) {
    int resCmpFirst;
    int resCmpLast;
    int resCmpMiddle;
    int resInsertInPos;
    List_t* head;
    head = root;
    while (1) {
        resCmpFirst = strcmp(node->firstname, root->firstname);
        resCmpLast = strcmp(node->lastname, root->lastname);
        resCmpMiddle = strcmp(node->middlename, root->middlename);
        if ((resCmpFirst == 0) && (resCmpLast == 0) && (resCmpMiddle == 0)) {
            node->next = root->next;
            root->next = node;
            break;
        }

        if ((resCmpFirst == 0) && (resCmpLast == 0)) {
            resInsertInPos = insertInPos(node->middlename, root->middlename, &node, &root, &head);
            if (resInsertInPos == posWasFound || resInsertInPos == anotherPosWasFound) {
                break;
            }
            else {
                continue;
            }
        }
        if (resCmpLast == 0) {
            resInsertInPos = insertInPos(node->firstname, root->firstname, &node, &root, &head);
            if (resInsertInPos == posWasFound || resInsertInPos == anotherPosWasFound) {
                break;
            }
            else {
                continue;
            }
        }
        resInsertInPos = insertInPos(node->lastname, root->lastname, &node, &root, &head);
        if (resInsertInPos == posWasFound || resInsertInPos == anotherPosWasFound) {
            break;
        }
        else {
            continue;
        }
    }
    return head;
}
void findNode(List_t* root) {
    char strLast[MAX_ARRAY_SIZE];
    char strFirst[MAX_ARRAY_SIZE];
    char strMid[MAX_ARRAY_SIZE];
    gets_s(strLast, MAX_ARRAY_SIZE);
    gets_s(strFirst, MAX_ARRAY_SIZE);
    gets_s(strMid, MAX_ARRAY_SIZE);
    int resCmpFirst;
    int resCmpLast;
    int resCmpMiddle;
    while (root != NULL) {
        resCmpFirst = strncmp(strFirst, root->firstname, strlen(strFirst));
        resCmpLast = strncmp(strLast, root->lastname, strlen(strLast));
        resCmpMiddle = strncmp(strMid, root->middlename, strlen(strMid));
        if ((resCmpLast == 0) && (resCmpFirst == 0) && (resCmpMiddle == 0)) {
            printNode(root);
        }
        root = root->next;
    }

}
int main(void) {
    char buffer[MAX_ARRAY_SIZE];// max(len(firstname, lastname, middlename))<buffer
    List_t* root = (List_t*)malloc(sizeof(List_t));
    root->next = NULL;
    List_t* newNod;
    int s;
    FILE* f;
    if ((f = fopen("file.txt", "rb")) == NULL)
        printf("The file 'file' was not opened\n");
    else {
        s = fscanf(f, "%s", buffer);
        addInfo(root, buffer, "L");
        fscanf(f, "%s", buffer);
        addInfo(root, buffer, "F");
        fscanf(f, "%s", buffer);
        addInfo(root, buffer, "M");
        s = fscanf(f, "%s", buffer);
        while (s != EOF) {
            newNod = newNode();
            addInfo(newNod, buffer, "L");
            fscanf(f, "%s", buffer);
            addInfo(newNod, buffer, "F");
            fscanf(f, "%s", buffer);
            addInfo(newNod, buffer, "M");
            root = sortNode(root, newNod);
            s = fscanf(f, "%s", buffer);
        }
        printList(root);
        findNode(root);
    }
    return 0;
}

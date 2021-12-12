#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 0

typedef enum {
    NONE = 0,
    LEFT = 1,
    RIGHT = 2
}way_t;

typedef struct tree_t {
    char* word;
    int len;
    struct tree_t* left;
    struct tree_t* right;
    struct tree_t* parent;
    int WigthOfSubtree;
} tree_t;

void Append(tree_t** tree, char* buff) {
    tree_t* tmp;
    tree_t* new;
    tree_t* ptr = (*tree);
    int subtreelength;
    new = (tree_t*)malloc(sizeof(tree_t));
    if (!new)
        return;
    new->left = NULL;
    new->right = NULL;
    new->parent = NULL;
    new->WigthOfSubtree = 0;
    new->len = strlen(buff);
    new->word = (char*)malloc((new->len + 1) * sizeof(char));
    if (!new->word)
        return;
    strcpy(new->word, buff);
    if (!(*tree)) {
        (*tree) = new;
        return;
    }
    while (ptr) {
        if (new->len < ptr->len) {
            if (ptr->left)
                ptr = ptr->left;
            else
                break;
        }
        else if (new->len > ptr->len) {
            if (ptr->right)
                ptr = ptr->right;
            else
                break;
        }
        else {
            free(new);
            return;
        }
    }
    if (new->len < ptr->len)
        ptr->left = new;
    else
        ptr->right = new;
    new->parent = ptr;
    subtreelength = 0;
    tmp = new;
    while (tmp->parent) {
        tmp = tmp->parent;
        tmp->WigthOfSubtree += new->len;
    }
}


tree_t* Find(tree_t* tree, char* buff) {
    tree_t* tmp = tree;
    int len = strlen(buff);
    while (tmp) {
        if (len < tmp->len)
            tmp = tmp->left;
        else if (len > tmp->len)
            tmp = tmp->right;
        else {
            if (strcmp(tmp->word, buff) != TRUE) {
                return NULL;
            }
            else
                return tmp;
        }
    }
    return NULL;
}
void Delete(tree_t** tree, tree_t* vert) {
    if (!vert)
        return;
    tree_t* max = vert;
    tree_t* parent;
    tree_t* child;
    tree_t* tmp;
    way_t pway;
    char* tmpbuff;
    if (vert->left == NULL && vert->right == NULL) {
        if ((vert == (*tree))) {
            free(vert->word);
            free(vert);
            (*tree) = NULL;
            return;
        }
        parent = vert->parent;
        if (parent->left == vert)
            pway = LEFT;
        else
            pway = RIGHT;
        if (pway == LEFT)
            parent->left = NULL;
        else
            parent->right = NULL;
        tmp = vert;
        while (tmp->parent) {
            tmp = tmp->parent;
            tmp->WigthOfSubtree -= vert->len;
        }
        free(vert->word);
        free(vert);

        return;
    }
    if ((vert->left != NULL && vert->right == NULL) || (vert->left == NULL && vert->right != NULL)) {

        if (vert == (*tree)) {
            if (vert->left)
                (*tree) = vert->left;
            else
                (*tree) = vert->right;
            (*tree)->parent = NULL;
            free(vert);
            return;
        }
        parent = vert->parent;
        if (parent->left == vert)
            pway = LEFT;
        else
            pway = RIGHT;
        if (vert->left)
            child = vert->left;
        else
            child = vert->right;
        child->parent = vert->parent;
        if (pway == LEFT)
            parent->left = child;
        else
            parent->right = child;
        tmp = vert;
        while (tmp->parent) {
            tmp = tmp->parent;
            tmp->WigthOfSubtree -= vert->len;
        }
        free(vert->word);
        free(vert);
        return;
    }
    max = max->right;
    while (max->left)
        max = max->left;
    int tmplen;
    tmplen = max->len;
    max->len = vert->len;
    vert->len = tmplen;
    tmpbuff = (char*)realloc(vert->word, (vert->len + 1) * sizeof(char));
    if (tmpbuff) {
        vert->word = tmpbuff;
        tmpbuff = NULL;
    }
    else {
        free(vert->word);
        return;
    }
    strcpy(vert->word, max->word);
    tmp = max;
    while (tmp->parent != vert->parent) {
        tmp = tmp->parent;
        tmp->WigthOfSubtree += (max->len - vert->len);
    }
    if (max->right) {
        child = max->right;
        parent = max->parent;
        if (parent->left == max)
            pway = LEFT;
        else
            pway = RIGHT;
        if (pway == LEFT)
            parent->left = child;
        else
            parent->right = child;
        child->parent = parent;
    }
    else {
        parent = max->parent;
        if (parent->left == max)
            pway = LEFT;
        else
            pway = RIGHT;

        if (pway == LEFT)
            parent->left = NULL;
        else
            parent->right = NULL;
    }
    tmp = max;
    while (tmp->parent) {
        tmp = tmp->parent;
        tmp->WigthOfSubtree -= max->len;
    }
    free(max->word);
    free(max);
    return;
}


void Print(tree_t* tree, int level) {
    if (tree) {
        Print(tree->left, level + (tree->len));
        for (int i = 0; i < level; i++)
            printf("   ");
        for (int i = 0; i < tree->len; ++i)
            printf("%c", tree->word[i]);
        printf("\n");
        for (int i = 0; i < level; i++)
            printf("   ");
        printf("%i\n", tree->len);
        for (int i = 0; i < level; i++)
            printf("   ");
        printf("%i\n", tree->WigthOfSubtree);
        Print(tree->right, level + (tree->len));
    }
}


void DestroyTree(tree_t* tree) {
    if (tree) {
        DestroyTree(tree->left);
        DestroyTree(tree->right);
        free(tree->word);
        free(tree);
    }
}

int main(void) {
    tree_t* tree = NULL;
    const int ONE = 1;
    Append(&tree, "55555");
    Append(&tree, "333");
    Append(&tree, "4444");
    Append(&tree, "2");
    Delete(&tree, Find(tree, "333"));
    Append(&tree, "666666");
    Print(tree, ONE);
    DestroyTree(tree);
    return 0;
}
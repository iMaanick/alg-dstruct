#pragma once
#define TRUE 1
#define FALSE 0
typedef struct treap {
	int key, priority;
	struct treap* left;
	struct treap* right;
} treap;
treap* MergeTrees(treap* leftTree, treap* rightTree);
void SplitTree(treap* tree, int key, treap** leftTree, treap** rightTree);
int AddNode(treap** tree, int key);
int RemoveNode(treap** tree, int key);
int FindNode(treap* tree, int key);
void PrintTree(treap* tree, int level);
int DestroyTree(treap* tree);
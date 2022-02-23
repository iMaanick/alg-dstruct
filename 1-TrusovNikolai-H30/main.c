#include <stdio.h>
#include <stdlib.h>
#include"treaps.h"

treap* MergeTrees(treap* leftTree, treap* rightTree) {
	if (!leftTree)
		return rightTree;
	if (!rightTree)
		return leftTree;
	if (leftTree->priority > rightTree->priority) {
		leftTree->right = MergeTrees(leftTree->right, rightTree);
		return leftTree;
	}
	else {
		rightTree->left = MergeTrees(leftTree, rightTree->left);
		return rightTree;
	}
}

void SplitTree(treap* tree, int key, treap** leftTree, treap** rightTree) {
	if (!tree) {
		(*leftTree) = NULL;
		(*rightTree) = NULL;
		return;
	}
	if (tree->key <= key) {
		SplitTree(tree->right, key, &(tree->right), rightTree);
		(*leftTree) = tree;
		return;
	}
	else {
		SplitTree(tree->left, key, leftTree, &(tree->left));
		(*rightTree) = tree;
		return;
	}
}

int AddNode(treap** tree, int key) {
	treap* leftTree, * rightTree;
	treap* newNode = (treap*)malloc(sizeof(treap));
	if (newNode == NULL)
		return FALSE;
	newNode->key = key;
	newNode->priority = rand();
	newNode->left = NULL;
	newNode->right = NULL;
	if ((*tree) == NULL) { //if tree is empty
		(*tree) = newNode;
		return TRUE;
	}
	SplitTree(*tree, key, &leftTree, &rightTree);
	if (leftTree && leftTree->key == key) { //if key is already in the tree
		(*tree) = MergeTrees(leftTree, rightTree);
		return FALSE;
	}
	(*tree) = MergeTrees(MergeTrees(leftTree, newNode), rightTree);
	return TRUE;
}

int FindNode(treap* tree, int key) {
	treap* node = tree;
	while (node) {
		if (key < node->key)
			node = node->left;
		else if (key > node->key)
			node = node->right;
		else
			return TRUE;
	}
	return FALSE;
}
int RemoveNode(treap** tree, int key) {
	treap* leftTree, * node, * rightTree;
	SplitTree(*tree, key, &leftTree, &rightTree);
	SplitTree(leftTree, key - 1, &leftTree, &node);
	(*tree) = MergeTrees(leftTree, rightTree);
	if (!node)
		return FALSE;
	else {
		free(node);
		return TRUE;
	}
}

int DestroyTree(treap* tree) {
	if (!tree)
		return FALSE;
	else {
		DestroyTree(tree->left);
		DestroyTree(tree->right);
		free(tree);
	}
	return TRUE;
}

void PrintTree(treap* tree, int level) {
	int i;
	if (tree == NULL)
		return;
	PrintTree(tree->right, level + 1);
	for (i = 0; i < level; i++)
		printf("           ");
	printf("%d(%d)\n", tree->key, tree->priority);
	PrintTree(tree->left, level + 1);
}

int main() {
	treap* tree = NULL;
	int key;
	char operation;
	while (TRUE) {
		operation = getchar();
		if (operation == EOF || operation == '\n')
			break;
		scanf("%d", &key);
		if (operation == 'a')
			AddNode(&tree, key);
		else if (operation == 'r')
			RemoveNode(&tree, key);
		else if (operation == 'f') {
			if (FindNode(tree, key) == TRUE)
				printf("yes\n");
			else
				printf("no\n");
		}
		operation = getchar();
	}
	DestroyTree(tree);
	return 0;
}
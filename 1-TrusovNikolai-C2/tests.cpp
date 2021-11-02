#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include "gtest/gtest.h"
extern "C" {
#include "graph.h"
}
TEST(creatFirstEdge, adding_data) {
	edge_t* head;
	int data1 = 1;
	int data2 = 2;
	head = creatFirstEdge(data1, data2);
	ASSERT_EQ(data1, head->startEdge);
	ASSERT_EQ(data2, head->endEdge);
	free(head);
}
TEST(addEdge, adding_data_to_the_created_node_when_1_node_in_list) {
	edge_t* head = (edge_t*)malloc(sizeof(edge_t));
	if (!head) {
		printf("Error allocating memory\n");
		exit(1);
	}
	head->next = NULL;
	int dataHead1 = 1;
	int dataHead2 = 2;
	head->startEdge = dataHead1;
	head->endEdge = dataHead2;
	int addedNodeData1 = 3;
	int addedNodeData2 = 4;
	head = addEdge(head, addedNodeData1, addedNodeData2);
	ASSERT_EQ(dataHead1, head->startEdge);
	ASSERT_EQ(dataHead2, head->endEdge);
	ASSERT_EQ(addedNodeData1, (head->next)->startEdge);
	ASSERT_EQ(addedNodeData2, (head->next)->endEdge);
	free(head->next);
	free(head);
}
TEST(addEdge, adding_data_to_the_created_node_when_more_than_1_node_in_list) {
	edge_t* head = (edge_t*)malloc(sizeof(edge_t));
	if (!head) {
		printf("Error allocating memory\n");
		exit(1);
	}
	edge_t* node1 = (edge_t*)malloc(sizeof(edge_t));
	if (!node1) {
		printf("Error allocating memory\n");
		exit(1);
	}
	head->next = node1;
	int dataHead1 = 1;
	int dataHead2 = 2;
	head->startEdge = dataHead1;
	head->endEdge = dataHead2;
	int node1Data1 = 3;
	int node1Data2 = 4;
	node1->startEdge = node1Data1;
	node1->endEdge = node1Data2;
	node1->next = NULL;
	int addedNodeData1 = 5;
	int addedNodeData2 = 6;
	head = addEdge(head, addedNodeData1, addedNodeData2);
	edge_t* tmp = head;
	ASSERT_EQ(dataHead1, tmp->startEdge);
	ASSERT_EQ(dataHead2, tmp->endEdge);
	tmp = tmp->next;
	ASSERT_EQ(node1Data1, tmp->startEdge);
	ASSERT_EQ(node1Data2, tmp->endEdge);
	tmp = tmp->next;
	ASSERT_EQ(addedNodeData1, tmp->startEdge);
	ASSERT_EQ(addedNodeData2, tmp->endEdge);
	free((head->next)->next);
	free(head->next);
	free(head);
}
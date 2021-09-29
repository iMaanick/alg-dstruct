#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include "gtest/gtest.h"
extern "C" {
#include "info.h"
}
TEST(addInfo, adding_new_data_in_firstname) {
	List_t* tmp = (List_t*)malloc(sizeof(List_t));
	if (!tmp) {
		printf("Error allocating memory\n");
		exit(1);
	}
	char buffer[] = { "Ivan" };
	addInfo(tmp, buffer, "F");
	ASSERT_STRCASEEQ(buffer, tmp->firstname);
	free(tmp);
}
TEST(addInfo, adding_new_data_in_lastname) {
	List_t* tmp = (List_t*)malloc(sizeof(List_t));
	if (!tmp) {
		printf("Error allocating memory\n");
		exit(1);
	}
	char buffer[] = { "Ivanov" };
	addInfo(tmp, buffer, "L");
	ASSERT_STRCASEEQ(buffer, tmp->lastname);
	free(tmp);
}
TEST(addInfo, adding_new_data_in_middlename) {
	List_t* tmp = (List_t*)malloc(sizeof(List_t));
	if (!tmp) {
		printf("Error allocating memory\n");
		exit(1);
	}
	char buffer[] = { "Ivanovich" };
	addInfo(tmp, buffer, "M");
	ASSERT_STRCASEEQ(buffer, tmp->middlename);
	free(tmp);
}
TEST(insertInFrontOfNode, checking_that_node_2_is_inserted_in_front_of_the_head) {
	List_t* head_node_1 = (List_t*)malloc(sizeof(List_t));
	List_t* node_2 = (List_t*)malloc(sizeof(List_t));
	if (!head_node_1 || !node_2) {
		printf("Error allocating memory\n");
		exit(1);
	}
	char strA[] = { "A" };
	char strB[] = { "B" };
	char strC[] = { "C" };
	char strD[] = { "D" };
	char strE[] = { "E" };
	char strF[] = { "F" };
	head_node_1->firstname = strA;
	head_node_1->lastname = strB;
	head_node_1->middlename = strC;
	node_2->firstname = strD;
	node_2->lastname = strE;
	node_2->middlename = strF;
	head_node_1 = insertInFrontOfNode(&node_2, &head_node_1, head_node_1);
	ASSERT_STRCASEEQ(head_node_1->firstname, strD);
	ASSERT_STRCASEEQ(head_node_1->lastname, strE);
	ASSERT_STRCASEEQ(head_node_1->middlename, strF);
	ASSERT_STRCASEEQ(head_node_1->next->firstname, strA);
	ASSERT_STRCASEEQ(head_node_1->next->lastname, strB);
	ASSERT_STRCASEEQ(head_node_1->next->middlename, strC);
	free(head_node_1->next);
	free(head_node_1);
}
TEST(insertInFrontOfNode, checking_that_node_2_is_inserted_in_front_of_the_node_1_which_is_not_the_head) {
	List_t* head = (List_t*)malloc(sizeof(List_t));
	List_t* node_1 = (List_t*)malloc(sizeof(List_t));
	List_t* node_2 = (List_t*)malloc(sizeof(List_t));
	if (!head || !node_1 || !node_2) {
		printf("Error allocating memory\n");
		exit(1);
	}
	head->next = node_1;
	char strA[] = { "A" };
	char strB[] = { "B" };
	char strC[] = { "C" };
	char strD[] = { "D" };
	char strE[] = { "E" };
	char strF[] = { "F" };
	head->firstname = strA;
	head->lastname = strA;
	head->middlename = strA;
	node_1->firstname = strA;
	node_1->lastname = strB;
	node_1->middlename = strC;
	node_2->firstname = strD;
	node_2->lastname = strE;
	node_2->middlename = strF;
	head = insertInFrontOfNode(&node_2, &node_1, head);
	List_t* p;
	p = head;
	head = head->next;
	free(p);
	ASSERT_STRCASEEQ(head->firstname, strD);
	ASSERT_STRCASEEQ(head->lastname, strE);
	ASSERT_STRCASEEQ(head->middlename, strF);
	ASSERT_STRCASEEQ(head->next->firstname, strA);
	ASSERT_STRCASEEQ(head->next->lastname, strB);
	ASSERT_STRCASEEQ(head->next->middlename, strC);
	free(head->next);
	free(head);
}

TEST(insertInPos, checking_that_POS_WAS_FOUND_is_returned_if_nodeName_is_less_than_nodeInListName) {
	List_t* node_1 = (List_t*)malloc(sizeof(List_t));
	List_t* node_2 = (List_t*)malloc(sizeof(List_t));
	if (!node_1 || !node_2) {
		printf("Error allocating memory\n");
		exit(1);
	}
	char strA[] = { "A" };
	char strB[] = { "B" };
	char strC[] = { "C" };
	char strD[] = { "D" };
	char strE[] = { "E" };
	char strF[] = { "F" };
	node_1->firstname = strA;
	node_1->lastname = strB;
	node_1->middlename = strC;
	node_2->firstname = strD;
	node_2->lastname = strE;
	node_2->middlename = strF;
	ASSERT_EQ(insertInPos(node_1->firstname, node_2->firstname, &node_1, &node_2, &node_2), POS_WAS_FOUND);
	free(node_1->next);
	free(node_1);
}

TEST(insertInPos, checking_that_ANOTHER_POS_WAS_FOUND_is_returned_if_nodeName_is_bigger_than_nodeInListName_and_nodeInList_next_is_NULL) {
	List_t* node_1 = (List_t*)malloc(sizeof(List_t));
	List_t* node_2 = (List_t*)malloc(sizeof(List_t));
	if (!node_1 || !node_2) {
		printf("Error allocating memory\n");
		exit(1);
	}
	node_2->next = NULL;
	char strA[] = { "A" };
	char strB[] = { "B" };
	char strC[] = { "C" };
	char strD[] = { "D" };
	char strE[] = { "E" };
	char strF[] = { "F" };
	node_1->firstname = strD;
	node_1->lastname = strB;
	node_1->middlename = strC;
	node_2->firstname = strA;
	node_2->lastname = strE;
	node_2->middlename = strF;
	ASSERT_EQ(insertInPos(node_1->firstname, node_2->firstname, &node_1, &node_2, &node_2), ANOTHER_POS_WAS_FOUND);
	free(node_1);
	free(node_2);
}
TEST(insertInPos, checking_that_ANOTHER_POS_WAS_FOUND_is_returned_if_nodeName_is_equal_to_nodeInListName_and_nodeInList_next_is_NULL) {
	List_t* node_1 = (List_t*)malloc(sizeof(List_t));
	List_t* node_2 = (List_t*)malloc(sizeof(List_t));
	if (!node_1 || !node_2) {
		printf("Error allocating memory\n");
		exit(1);
	}
	node_2->next = NULL;
	char strA[] = { "A" };
	char strB[] = { "B" };
	char strC[] = { "C" };
	char strE[] = { "E" };
	char strF[] = { "F" };
	node_1->firstname = strA;
	node_1->lastname = strB;
	node_1->middlename = strC;
	node_2->firstname = strA;
	node_2->lastname = strE;
	node_2->middlename = strF;
	ASSERT_EQ(insertInPos(node_1->firstname, node_2->firstname, &node_1, &node_2, &node_2), ANOTHER_POS_WAS_FOUND);
	free(node_1);
	free(node_2);
}

TEST(insertInPos, checking_that_POS_WAS_NOT_FOUND_is_returned_if_nodeName_is_bigger_than_nodeInListName_and_nodeInList_next_is_not_NULL) {
	List_t* node_1 = (List_t*)malloc(sizeof(List_t));
	List_t* node_2 = (List_t*)malloc(sizeof(List_t));
	if (!node_1 || !node_2) {
		printf("Error allocating memory\n");
		exit(1);
	}
	char strA[] = { "A" };
	char strB[] = { "B" };
	char strC[] = { "C" };
	char strD[] = { "D" };
	char strE[] = { "E" };
	char strF[] = { "F" };
	node_1->firstname = strD;
	node_1->lastname = strB;
	node_1->middlename = strC;
	node_2->firstname = strA;
	node_2->lastname = strE;
	node_2->middlename = strF;
	List_t* p;
	p = node_2;
	ASSERT_EQ(insertInPos(node_1->firstname, node_2->firstname, &node_1, &node_2, &node_2), POS_WAS_NOT_FOUND);
	free(node_1);
	free(p);
}
TEST(insertInPos, checking_that_POS_WAS_NOT_FOUND_is_returned_if_nodeName_is_equal_to_nodeInListName_and_nodeInList_next_is_not_NULL) {
	List_t* node_1 = (List_t*)malloc(sizeof(List_t));
	List_t* node_2 = (List_t*)malloc(sizeof(List_t));
	if (!node_1 || !node_2) {
		printf("Error allocating memory\n");
		exit(1);
	}
	char strA[] = { "A" };
	char strB[] = { "B" };
	char strC[] = { "C" };
	char strE[] = { "E" };
	char strF[] = { "F" };
	node_1->firstname = strA;
	node_1->lastname = strB;
	node_1->middlename = strC;
	node_2->firstname = strA;
	node_2->lastname = strE;
	node_2->middlename = strF;
	List_t* p;
	p = node_2;
	ASSERT_EQ(insertInPos(node_1->firstname, node_2->firstname, &node_1, &node_2, &node_2), POS_WAS_NOT_FOUND);
	free(node_1);
	free(p);
}
TEST(insertInPos, checking_that_nodeInList_points_to_next_node_if_nodeName_is_bigger_than_nodeInListName_and_nodeInList_next_is_not_NULL) {
	List_t* node_1 = (List_t*)malloc(sizeof(List_t));
	List_t* node_2 = (List_t*)malloc(sizeof(List_t));
	List_t* node_2_next = (List_t*)malloc(sizeof(List_t));
	if (!node_1 || !node_2 || !node_2_next) {
		printf("Error allocating memory\n");
		exit(1);
	}
	node_2->next = node_2_next;
	char strA[] = { "A" };
	char strB[] = { "B" };
	char strC[] = { "C" };
	char strD[] = { "D" };
	char strE[] = { "E" };
	char strF[] = { "F" };
	char strH[] = { "H" };
	char strI[] = { "I" };
	char strJ[] = { "J" };
	node_1->firstname = strD;
	node_1->lastname = strB;
	node_1->middlename = strC;
	node_2->firstname = strA;
	node_2->lastname = strE;
	node_2->middlename = strF;
	node_2_next->firstname = strH;
	node_2_next->lastname = strI;
	node_2_next->middlename = strJ;
	List_t* tmp1;
	List_t* tmp2;
	List_t* tmp3;
	tmp1 = node_1;
	tmp2 = node_2;
	tmp3 = node_2_next;
	insertInPos(node_1->firstname, node_2->firstname, &node_1, &node_2, &node_2);
	ASSERT_STRCASEEQ(node_2->firstname, strH);
	ASSERT_STRCASEEQ(node_2->lastname, strI);
	ASSERT_STRCASEEQ(node_2->middlename, strJ);
	free(tmp1);
	free(tmp2);
	free(tmp3);
}
TEST(insertInPos, checking_that_nodeInList_points_to_next_node_if_nodeName_is_equal_to_nodeInListName_and_nodeInList_next_is_not_NULL) {
	List_t* node_1 = (List_t*)malloc(sizeof(List_t));
	List_t* node_2 = (List_t*)malloc(sizeof(List_t));
	List_t* node_2_next = (List_t*)malloc(sizeof(List_t));
	if (!node_1 || !node_2 || !node_2_next) {
		printf("Error allocating memory\n");
		exit(1);
	}
	node_2->next = node_2_next;
	char strB[] = { "B" };
	char strC[] = { "C" };
	char strD[] = { "D" };
	char strE[] = { "E" };
	char strF[] = { "F" };
	char strH[] = { "H" };
	char strI[] = { "I" };
	char strJ[] = { "J" };
	node_1->firstname = strD;
	node_1->lastname = strB;
	node_1->middlename = strC;
	node_2->firstname = strD;
	node_2->lastname = strE;
	node_2->middlename = strF;
	node_2_next->firstname = strH;
	node_2_next->lastname = strI;
	node_2_next->middlename = strJ;
	List_t* tmp1;
	List_t* tmp2;
	List_t* tmp3;
	tmp1 = node_1;
	tmp2 = node_2;
	tmp3 = node_2_next;
	insertInPos(node_1->firstname, node_2->firstname, &node_1, &node_2, &node_2);
	ASSERT_STRCASEEQ(node_2->firstname, strH);
	ASSERT_STRCASEEQ(node_2->lastname, strI);
	ASSERT_STRCASEEQ(node_2->middlename, strJ);
	free(tmp1);
	free(tmp2);
	free(tmp3);
}
TEST(sortNode, checking_node_addition_if_data_root_is_equal_to_data_node) {
	List_t* root = (List_t*)malloc(sizeof(List_t));
	List_t* node = (List_t*)malloc(sizeof(List_t));
	if (!root || !node) {
		printf("Error allocating memory\n");
		exit(1);
	}
	root->next = NULL;
	char firstname[] = { "A" };
	char lastname[] = { "B" };
	char middlename[] = { "C" };
	root->firstname = firstname;
	root->lastname = lastname;
	root->middlename = middlename;
	node->firstname = firstname;
	node->lastname = lastname;
	node->middlename = middlename;
	root = sortNode(root, node);
	ASSERT_STRCASEEQ(root->firstname, firstname);
	ASSERT_STRCASEEQ(root->lastname, lastname);
	ASSERT_STRCASEEQ(root->middlename, middlename);
	ASSERT_STRCASEEQ(root->next->firstname, firstname);
	ASSERT_STRCASEEQ(root->next->lastname, lastname);
	ASSERT_STRCASEEQ(root->next->middlename, middlename);
	free(root);
	free(node);
}
TEST(sortNode, checking_sorting_by_lastnames) {
	List_t* root = (List_t*)malloc(sizeof(List_t));
	List_t* node = (List_t*)malloc(sizeof(List_t));
	if (!root || !node) {
		printf("Error allocating memory\n");
		exit(1);
	}
	root->next = NULL;
	char strA[] = { "A" };
	char strB[] = { "B" };
	char strC[] = { "C" };
	char strD[] = { "D" };
	char strE[] = { "E" };
	char strF[] = { "F" };
	node->firstname = strA;
	node->lastname = strB;
	node->middlename = strC;
	root->firstname = strD;
	root->lastname = strE;
	root->middlename = strF;
	root = sortNode(root, node);
	ASSERT_STRCASEEQ(root->firstname, strA);
	ASSERT_STRCASEEQ(root->lastname, strB);
	ASSERT_STRCASEEQ(root->middlename, strC);
	ASSERT_STRCASEEQ(root->next->firstname, strD);
	ASSERT_STRCASEEQ(root->next->lastname, strE);
	ASSERT_STRCASEEQ(root->next->middlename, strF);
	free(root->next);
	free(root);
}
TEST(sortNode, checking_sorting_by_firstnames) {
	List_t* root = (List_t*)malloc(sizeof(List_t));
	List_t* node = (List_t*)malloc(sizeof(List_t));
	if (!root || !node) {
		printf("Error allocating memory\n");
		exit(1);
	}
	root->next = NULL;
	char strA[] = { "A" };
	char strB[] = { "B" };
	char strC[] = { "C" };
	char strD[] = { "D" };
	char strE[] = { "E" };
	node->firstname = strA;
	node->lastname = strB;
	node->middlename = strC;
	root->firstname = strD;
	root->lastname = strB;
	root->middlename = strE;

	root = sortNode(root, node);
	ASSERT_STRCASEEQ(root->firstname, strA);
	ASSERT_STRCASEEQ(root->lastname, strB);
	ASSERT_STRCASEEQ(root->middlename, strC);
	ASSERT_STRCASEEQ(root->next->firstname, strD);
	ASSERT_STRCASEEQ(root->next->lastname, strB);
	ASSERT_STRCASEEQ(root->next->middlename, strE);
	free(root->next);
	free(root);
}
TEST(sortNode, checking_sorting_by_middlenames) {
	List_t* root = (List_t*)malloc(sizeof(List_t));
	List_t* node = (List_t*)malloc(sizeof(List_t));
	if (!root || !node) {
		printf("Error allocating memory\n");
		exit(1);
	}
	root->next = NULL;
	char strA[] = { "A" };
	char strB[] = { "B" };
	char strC[] = { "C" };
	char strD[] = { "D" };
	node->firstname = strA;
	node->lastname = strB;
	node->middlename = strC;
	root->firstname = strA;
	root->lastname = strB;
	root->middlename = strD;
	root = sortNode(root, node);
	ASSERT_STRCASEEQ(root->firstname, strA);
	ASSERT_STRCASEEQ(root->lastname, strB);
	ASSERT_STRCASEEQ(root->middlename, strC);
	ASSERT_STRCASEEQ(root->next->firstname, strA);
	ASSERT_STRCASEEQ(root->next->lastname, strB);
	ASSERT_STRCASEEQ(root->next->middlename, strD);
	free(root->next);
	free(root);
}
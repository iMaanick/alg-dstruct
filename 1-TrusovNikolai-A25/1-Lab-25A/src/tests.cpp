#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include "gtest/gtest.h"
extern "C" {
#include "info.h"
}
TEST(addInfo, adding_new_data_in_firstname) {
	List_t* tmp = (List_t*)malloc(sizeof(List_t));
	char buffer[] = { "Ivan" };
	addInfo(tmp, buffer, "F");
	ASSERT_STRCASEEQ(buffer, tmp->firstname);
}
TEST(addInfo, adding_new_data_in_lastname) {
	List_t* tmp = (List_t*)malloc(sizeof(List_t));
	char buffer[] = { "Ivanov" };
	addInfo(tmp, buffer, "L");
	ASSERT_STRCASEEQ(buffer, tmp->lastname);
}
TEST(addInfo, adding_new_data_in_middlename) {
	List_t* tmp = (List_t*)malloc(sizeof(List_t));
	char buffer[] = { "Ivanovich" };
	addInfo(tmp, buffer, "M");
	ASSERT_STRCASEEQ(buffer, tmp->middlename);
}
TEST(insertInFrontOfNode, checking_that_node_2_is_inserted_in_front_of_the_head) {
	List_t* head_node_1 = (List_t*)malloc(sizeof(List_t));
	List_t* node_2 = (List_t*)malloc(sizeof(List_t));
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
}
TEST(insertInFrontOfNode, checking_that_node_2_is_inserted_in_front_of_the_node_1_which_is_not_the_head) {
	List_t* head = (List_t*)malloc(sizeof(List_t));
	List_t* node_1 = (List_t*)malloc(sizeof(List_t));
	List_t* node_2 = (List_t*)malloc(sizeof(List_t));
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
	head = head->next;
	ASSERT_STRCASEEQ(head->firstname, strD);
	ASSERT_STRCASEEQ(head->lastname, strE);
	ASSERT_STRCASEEQ(head->middlename, strF);
	ASSERT_STRCASEEQ(head->next->firstname, strA);
	ASSERT_STRCASEEQ(head->next->lastname, strB);
	ASSERT_STRCASEEQ(head->next->middlename, strC);
}

TEST(insertInPos, checking_that_posWasFound_is_returned_if_nodeName_is_less_than_nodeInListName) {
	List_t* node_1 = (List_t*)malloc(sizeof(List_t));
	List_t* node_2 = (List_t*)malloc(sizeof(List_t));
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
	ASSERT_EQ(insertInPos(node_1->firstname, node_2->firstname, &node_1, &node_2, &node_2), posWasFound);
}

TEST(insertInPos, checking_that_anotherPosWasFound_is_returned_if_nodeName_is_bigger_than_nodeInListName_and_nodeInList_next_is_NULL) {
	List_t* node_1 = (List_t*)malloc(sizeof(List_t));
	List_t* node_2 = (List_t*)malloc(sizeof(List_t));
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
	ASSERT_EQ(insertInPos(node_1->firstname, node_2->firstname, &node_1, &node_2, &node_2), anotherPosWasFound);
}
TEST(insertInPos, checking_that_anotherPosWasFound_is_returned_if_nodeName_is_equal_to_nodeInListName_and_nodeInList_next_is_NULL) {
	List_t* node_1 = (List_t*)malloc(sizeof(List_t));
	List_t* node_2 = (List_t*)malloc(sizeof(List_t));
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
	ASSERT_EQ(insertInPos(node_1->firstname, node_2->firstname, &node_1, &node_2, &node_2), anotherPosWasFound);
}

TEST(insertInPos, checking_that_posWasNotFound_is_returned_if_nodeName_is_bigger_than_nodeInListName_and_nodeInList_next_is_not_NULL) {
	List_t* node_1 = (List_t*)malloc(sizeof(List_t));
	List_t* node_2 = (List_t*)malloc(sizeof(List_t));
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
	ASSERT_EQ(insertInPos(node_1->firstname, node_2->firstname, &node_1, &node_2, &node_2), posWasNotFound);
}
TEST(insertInPos, checking_that_posWasNotFound_is_returned_if_nodeName_is_equal_to_nodeInListName_and_nodeInList_next_is_not_NULL) {
	List_t* node_1 = (List_t*)malloc(sizeof(List_t));
	List_t* node_2 = (List_t*)malloc(sizeof(List_t));
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
	ASSERT_EQ(insertInPos(node_1->firstname, node_2->firstname, &node_1, &node_2, &node_2), posWasNotFound);
}
TEST(insertInPos, checking_that_nodeInList_points_to_next_node_if_nodeName_is_bigger_than_nodeInListName_and_nodeInList_next_is_not_NULL) {
	List_t* node_1 = (List_t*)malloc(sizeof(List_t));
	List_t* node_2 = (List_t*)malloc(sizeof(List_t));
	List_t* node_2_next = (List_t*)malloc(sizeof(List_t));
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
	insertInPos(node_1->firstname, node_2->firstname, &node_1, &node_2, &node_2);
	ASSERT_STRCASEEQ(node_2->firstname, strH);
	ASSERT_STRCASEEQ(node_2->lastname, strI);
	ASSERT_STRCASEEQ(node_2->middlename, strJ);
}
TEST(insertInPos, checking_that_nodeInList_points_to_next_node_if_nodeName_is_equal_to_nodeInListName_and_nodeInList_next_is_not_NULL) {
	List_t* node_1 = (List_t*)malloc(sizeof(List_t));
	List_t* node_2 = (List_t*)malloc(sizeof(List_t));
	List_t* node_2_next = (List_t*)malloc(sizeof(List_t));
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
	insertInPos(node_1->firstname, node_2->firstname, &node_1, &node_2, &node_2);
	ASSERT_STRCASEEQ(node_2->firstname, strH);
	ASSERT_STRCASEEQ(node_2->lastname, strI);
	ASSERT_STRCASEEQ(node_2->middlename, strJ);
}
TEST(sortNode, checking_node_addition_if_data_root_is_equal_to_data_node) {
	List_t* root = (List_t*)malloc(sizeof(List_t));
	root->next = NULL;
	List_t* node = (List_t*)malloc(sizeof(List_t));
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
}
TEST(sortNode, checking_sorting_by_lastnames) {
	List_t* root = (List_t*)malloc(sizeof(List_t));
	root->next = NULL;
	List_t* node = (List_t*)malloc(sizeof(List_t));
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
}
TEST(sortNode, checking_sorting_by_firstnames) {
	List_t* root = (List_t*)malloc(sizeof(List_t));
	root->next = NULL;
	List_t* node = (List_t*)malloc(sizeof(List_t));
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
}
TEST(sortNode, checking_sorting_by_middlenames) {
	List_t* root = (List_t*)malloc(sizeof(List_t));
	root->next = NULL;
	List_t* node = (List_t*)malloc(sizeof(List_t));
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
}
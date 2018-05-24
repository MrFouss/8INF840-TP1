#pragma once
#include "Genealogy.h"

// print all members of a vector of nodes
void printNodeVector(vector<Node>* n);

// print all members of a vector of node ptrs
void printNodePtrVector(vector<Node*>* n);

// ask the user to choose an eye color
int getChosenColor();

// ask the user to choose a member of the family
int getChosenMemberId(Genealogy* memberId);
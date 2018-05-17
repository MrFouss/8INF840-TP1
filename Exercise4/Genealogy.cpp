#include "Genealogy.h"

void Genealogy::getDescendanceIN(int node){}

void Genealogy::getDescendancePRE(int node){}

void Genealogy::getDescendancePOST(int node){}

Genealogy::Genealogy()
{
	nextIndex = 0;

	//init internal struct
}

Genealogy::~Genealogy(){}

Node* Genealogy::getNode(int id)
{
	Node* result = NULL;

	//tree traversal

	return result;
}

Node* Genealogy::getNode(string name, string firstname)
{
	Node* result = NULL;

	//tree traversal

	return result;
}

int Genealogy::getSize()
{
	int count = 0;

	//tree traversal

	return count;
}

void Genealogy::getDescendance(int node, TreeTraversal type)
{
	switch (type) {
	case INORDER:
		getDescendanceIN(node);
		break;
	case PREORDER:
		getDescendancePRE(node);
		break;
	case POSTORDER:
		getDescendancePOST(node);
		break;
	default:
		cout << "ERROR : incorrect type of tree path ; must be INORDER, PREORDER or POSTORDER";
	}
}

int Genealogy::addMember(string name, string firstname, int birthyear, EyeColor eyes, int idmother, int idfather)
{
	Node* newMember = new Node(nextIndex++, name, firstname, birthyear, eyes);

	//tree traversal to look for its position

	return 0;
}

void Genealogy::getGenealogyByEyes(EyeColor color){}

void Genealogy::getAncestorsByEyes(EyeColor color, int nodeId){}

float Genealogy::meanAge()
{
	int membersCount = 0;
	int sumAges = 0;

	//tree traversal

	if (membersCount != 0)
		return (sumAges / membersCount);
	else
		return 0;
}

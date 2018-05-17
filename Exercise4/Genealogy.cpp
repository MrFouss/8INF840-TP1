#include "Genealogy.h"

void Genealogy::getDescendanceIN(int node){}

void Genealogy::getDescendancePRE(int node){}

void Genealogy::getDescendancePOST(int node){}

Genealogy::Genealogy()
{
	nextIndex = 0;
	tab = new vector<Node>();
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

int Genealogy::addMember(string name, string firstname, int birthyear, EyeColor eyes)
{
	Node* newMember = new Node(nextIndex++, name, firstname, birthyear, eyes);
	this->tab->push_back(*newMember);
	return 0;
}

int Genealogy::addMember(string name, string firstname, int birthyear, EyeColor eyes, int knownParentId)
{
	Node* newMember = new Node(nextIndex++, name, firstname, birthyear, eyes);
	
	if (knownParentId < nextIndex) {
		if ((tab->at(knownParentId).addChild(newMember)) == 0)
			return 0;
		else
			return -1;
	}
	else {
		return -1;
	}
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

void Genealogy::loadFromCSV(char* filepath)
{
	ifstream f;
	f.open(filepath);
	string line, name, firstname, birthyear, eyes;

	while (!f.eof())
	{
		getline(f, line);
		stringstream ss(line);
		getline(ss, firstname, ';');
		getline(ss, name, ';');
		getline(ss, birthyear, ';');
		getline(ss, eyes, ';');

		addMember(name, firstname, stoi(birthyear), itoEyeColor(stoi(eyes)));
	}

	f.close();
}

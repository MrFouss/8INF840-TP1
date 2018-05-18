#include "Genealogy.h"

void Genealogy::getDescendanceIN(int node){}

void Genealogy::getDescendancePRE(int node){}

void Genealogy::getDescendancePOST(int node){}

Genealogy::Genealogy()
{
	nextId = 1;
	tab = new vector<Node>();
	tab->push_back(*(new Node())); // dummy element so the vector start at 1
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
	Node* newMember = new Node(nextId++, name, firstname, birthyear, eyes);
	this->tab->push_back(*newMember);

	//cout << "New member : " << newMember->toString() << "\n";

	return 0;
}

int Genealogy::addMember(string name, string firstname, int birthyear, EyeColor eyes, int knownParentId, bool _left)
{
	Node* newMember = new Node(nextId++, name, firstname, birthyear, eyes);

	int index = getIndex(knownParentId);

	if (index != -1) //given parent exists
	{
		int left = 2 * index;
		int right = 2 * index + 1;

		int maxIndex = distance(tab->begin()+1, tab->end());
		
		// try insert as left child of given parent
		if (_left)
		{
			//check if index is not out of bound
			if (left > maxIndex)
				tab->resize(left+1);

			if ((tab->at(left).getId() == -1))
			{
				tab->at(left) = *newMember;
				return 0;
			}
			else
				return -1;
		}

		// try insert as left child of given parent
		if (!_left)
		{
			//check if index is not out of bound
			if (right > maxIndex)
				tab->resize(right + 1);

			if ((tab->at(right).getId() == -1))
			{
				tab->at(right) = *newMember;
				return 0;
			}
			else
				return -1;
		}
	}
	else // parent is not in the tree
		return -1;
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
	string line, name, firstname, year, eyes;
	int birthyear;

	while (!f.eof())
	{
		getline(f, line);
		stringstream ss(line);
		getline(ss, firstname, ';');
		getline(ss, name, ';');
		getline(ss, year, ';');
		getline(ss, eyes, ';');

		if (year[0] == '-')
			birthyear = stoi(year.erase(0,1)) * -1;
		else
			birthyear = stoi(year);

		addMember(name, firstname, stoi(year), itoEyeColor(stoi(eyes)));
	}

	f.close();
}

void Genealogy::printGenealogy(bool details)
{
	int count = 0;
	int nextLevel = 1;

	for (auto i = tab->begin()+1; i != tab->end(); ++i)
	{
		cout << ((Node)*i).toString(details);
		count++;
		if (count == nextLevel) {
			cout << "\n";
			count = 0;
			nextLevel *= 2;
		}
		else
			cout << " - ";
	}
}

bool Genealogy::exists(int id)
{
	for (auto it = tab->begin(); it != tab->end(); ++it)
	{
		if (((Node)*it).getId() == id)
			return true;
	}

	return false;
}

int Genealogy::getIndex(int id)
{
	for (auto it = tab->begin(); it != tab->end(); ++it)
	{
		if (((Node)*it).getId() == id)
			return (it - tab->begin());
	}

	return -1;
}


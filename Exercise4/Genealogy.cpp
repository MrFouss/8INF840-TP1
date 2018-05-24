#include "Genealogy.h"

vector<Node*>* Genealogy::getAncestorsIN(int nodeId)
{
	int currentIndex = getIndex(nodeId);
	int leftAncestor = currentIndex * 2;
	int rightAncestor = currentIndex * 2 + 1;

	vector<Node*>* left = new vector<Node*>();
	if (leftAncestor < tab->size())
		left = getAncestorsIN(tab->at(leftAncestor).getId());

	left->push_back(this->getNode(nodeId));

	vector<Node*>* right = new vector<Node*>();
	if (rightAncestor < tab->size())
		right = getAncestorsIN(tab->at(rightAncestor).getId());

	left->insert(left->end(), right->begin(), right->end());
	return left;
}

vector<Node*>* Genealogy::getAncestorsPRE(int nodeId)
{
	int currentIndex = getIndex(nodeId);
	int leftAncestor = currentIndex * 2;
	int rightAncestor = currentIndex * 2 + 1;

	vector<Node*>* result = new vector<Node*>();
	result->push_back(this->getNode(nodeId));

	vector<Node*>* left = new vector<Node*>();
	if (leftAncestor < tab->size())
		left = getAncestorsPRE(tab->at(leftAncestor).getId());

	vector<Node*>* right = new vector<Node*>();
	if (rightAncestor < tab->size())
		right = getAncestorsPRE(tab->at(rightAncestor).getId());

	result->insert(result->end(), left->begin(), left->end());
	result->insert(result->end(), right->begin(), right->end());
	return result;
}

vector<Node*>* Genealogy::getAncestorsPOST(int nodeId)
{
	int currentIndex = getIndex(nodeId);
	int leftAncestor = currentIndex * 2;
	int rightAncestor = currentIndex * 2 + 1;

	vector<Node*>* result = new vector<Node*>();

	vector<Node*>* left = new vector<Node*>();
	if (leftAncestor < tab->size())
		left = getAncestorsPOST(tab->at(leftAncestor).getId());

	vector<Node*>* right = new vector<Node*>();
	if (rightAncestor < tab->size())
		right = getAncestorsPOST(tab->at(rightAncestor).getId());

	result->insert(result->end(), left->begin(), left->end());
	result->insert(result->end(), right->begin(), right->end());
	result->push_back(this->getNode(nodeId));
	return result;
}

Genealogy::Genealogy()
{
	nextId = 1;
	tab = new vector<Node>();
	tab->push_back(*(new Node())); // dummy element so the vector start at 1
}

Genealogy::~Genealogy(){}

Node* Genealogy::getNode(int id)
{
	for (auto it = tab->begin() + 1; it != tab->end(); ++it)
	{
		if ((*it).getId() == id)
			return &(*it);
	}

	return nullptr;
}

Node* Genealogy::getNode(string name, string firstname)
{
	Node* result = nullptr;

	//tree traversal

	return result;
}

int Genealogy::getSize()
{
	return (tab->size()-1); //-1 because the first element is a dummy one
}

vector<Node*>* Genealogy::getAncestors(int node, TreeTraversal type)
{
	switch (type) {
	case INORDER:
		return getAncestorsIN(node);
	case PREORDER:
		return getAncestorsPRE(node);
	case POSTORDER:
		return getAncestorsPOST(node);
	default:
		cout << "ERROR : incorrect type of tree path ; must be INORDER, PREORDER or POSTORDER\n";
		return nullptr;
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

vector<Node>* Genealogy::getGenealogyByEyes(EyeColor color)
{
	vector<Node>* result = new vector<Node>();

	for (auto it = tab->begin(); it != tab->end(); ++it)
	{
		Node cur = (Node)*it;
		if (cur.getEyeColor() == color)
			result->push_back(cur);
	}

	return result;
}

vector<Node>* Genealogy::getAncestors(int nodeId)
{
	if (exists(nodeId))
	{
		vector<Node>* result = new vector<Node>();
		/// TODO
		return result;
	}
	else {
		cout << "\nERROR : the given id does not exist in this family. \n";
		return nullptr;
	}
}

vector<Node>* Genealogy::getAncestorsByEyes(int nodeId)
{
	if (exists(nodeId))
	{
		EyeColor color = this->getNode(nodeId)->getEyeColor();
		
		return nullptr;
	}
	else {
		cout << "\nERROR : the given id does not exist in this family. \n";
		return nullptr;
	}

}

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
	cout << "\n";
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


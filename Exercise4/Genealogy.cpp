#include "Genealogy.h"

vector<Node*>* Genealogy::getAncestorsIN(int nodeId)
{
	int currentIndex = getIndex(nodeId);
	int leftAncestor = getLeftAncestorIndex(currentIndex);
	int rightAncestor = getRightAncestorIndex(currentIndex);

	vector<Node*>* left = new vector<Node*>();
	if (leftAncestor < tab->size() && (tab->at(leftAncestor).getId() != -1))
		left = getAncestorsIN(tab->at(leftAncestor).getId());

	left->push_back(this->getNode(nodeId));

	vector<Node*>* right = new vector<Node*>();
	if (rightAncestor < tab->size() && (tab->at(rightAncestor).getId() != -1))
		right = getAncestorsIN(tab->at(rightAncestor).getId());

	left->insert(left->end(), right->begin(), right->end());
	return left;
}

vector<Node*>* Genealogy::getAncestorsPRE(int nodeId)
{
	int currentIndex = getIndex(nodeId);
	int leftAncestor = getLeftAncestorIndex(currentIndex);
	int rightAncestor = getRightAncestorIndex(currentIndex);

	vector<Node*>* result = new vector<Node*>();
	result->push_back(this->getNode(nodeId));

	vector<Node*>* left = new vector<Node*>();
	if (leftAncestor < tab->size() && (tab->at(leftAncestor).getId() != -1))
		left = getAncestorsPRE(tab->at(leftAncestor).getId());

	vector<Node*>* right = new vector<Node*>();
	if (rightAncestor < tab->size() && (tab->at(rightAncestor).getId() != -1))
		right = getAncestorsPRE(tab->at(rightAncestor).getId());

	result->insert(result->end(), left->begin(), left->end());
	result->insert(result->end(), right->begin(), right->end());
	return result;
}

vector<Node*>* Genealogy::getAncestorsPOST(int nodeId)
{
	int currentIndex = getIndex(nodeId);
	int leftAncestor = getLeftAncestorIndex(currentIndex);
	int rightAncestor = getRightAncestorIndex(currentIndex);

	vector<Node*>* result = new vector<Node*>();

	vector<Node*>* left = new vector<Node*>();
	if (leftAncestor < tab->size() && (tab->at(leftAncestor).getId() != -1))
		left = getAncestorsPOST(tab->at(leftAncestor).getId());

	vector<Node*>* right = new vector<Node*>();
	if (rightAncestor < tab->size() && (tab->at(rightAncestor).getId() != -1))
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

Genealogy::~Genealogy()
{
	nextId = 1;
	tab->clear();
}

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
	for (auto it = tab->begin() + 1; it != tab->end(); ++it)
	{
		if ((*it).getName() == name && (*it).getFirstname() == firstname)
			return &(*it);
	}

	return nullptr;
}

int Genealogy::getSize()
{
	int count = 0;

	for (auto it = tab->begin() + 1; it != tab->end(); ++it)
	{
		if ((*it).getId() != -1)
			count++;
	}

	return count;
}

vector<Node*>* Genealogy::getAncestors(int node, TreeTraversal type)
{
	if (exists(node))
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
	else
		return nullptr;
}

vector<Node*>* Genealogy::getDescendants(int nodeId)
{
	if (nodeId != 1)
	{
		int currIndex = getIndex(nodeId);
		int descendantIndex;
		
		if (getIndex(nodeId) % 2 == 0)
			descendantIndex = currIndex / 2;
		else
			descendantIndex = (currIndex - 1) / 2;

		vector<Node*>* v = getDescendants(descendantIndex);
		v->insert(v->begin(), getNode(nodeId));
		return v;

	}
	else {
		vector<Node*>* v = new vector<Node*>();
		v->push_back(getNode(1));
		return v;
	}
}

int Genealogy::addMember(string name, string firstname, int birthyear, EyeColor eyes)
{
	Node* newMember = new Node(nextId++, name, firstname, birthyear, eyes);
	this->tab->push_back(*newMember);

	//cout << "New member : " << newMember->toString() << "\n";

	return 0;
}

int Genealogy::getLeftAncestorIndex(int nodeIndex)
{
	return (2 * nodeIndex);
}

int Genealogy::getRightAncestorIndex(int nodeIndex)
{
	return (2 * nodeIndex + 1);
}

Node * Genealogy::getLeftAncestor(int nodeId)
{
	if (exists(nodeId))
		return &tab->at(getLeftAncestorIndex(getIndex(nodeId)));
	else
		return nullptr;
}

Node * Genealogy::getRightAncestor(int nodeId)
{
	if (exists(nodeId))
		return &tab->at(getRightAncestorIndex(getIndex(nodeId)));
	else
		return nullptr;
}

int Genealogy::addMember(string name, string firstname, int birthyear, EyeColor eyes, int knownDescendantID, bool _left)
{
	Node* newMember = new Node(nextId++, name, firstname, birthyear, eyes);

	int index = getIndex(knownDescendantID);

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

vector<Node*>* Genealogy::getGenealogyByEyes(EyeColor color)
{
	vector<Node*>* result = new vector<Node*>();

	for (auto it = tab->begin(); it != tab->end(); ++it)
	{
		if ((*it).getEyeColor() == color)
			result->push_back(&(*it));
	}

	return result;
}

vector<Node*>* Genealogy::getAncestorsByEyes(int nodeId)
{
	if (exists(nodeId))
	{
		EyeColor color = this->getNode(nodeId)->getEyeColor();
		vector<Node*>* ancestors = getAncestors(nodeId, INORDER);
		vector<Node*>* result = new vector<Node*>();

		for (auto it = ancestors->begin(); it != ancestors->end(); ++it)
		{
			Node* n = (Node*)*it;
			if (n->getEyeColor() == color)
				result->push_back(n);
		}

		return result;
	}
	else {
		cout << "\nERROR : the given id does not exist in this family. \n";
		return nullptr;
	}

}

int Genealogy::meanAge()
{
	time_t t = time(0);
	struct tm now;
	localtime_s(&now, &t);

	int membersCount = this->getSize();
	int sumAges = 0;
	int currentYear = now.tm_year +1900; //time describes time since 1900

	for (auto it = tab->begin(); it != tab->end(); ++it)
	{
		Node n = (*it);
		if (n.getId() != -1)
			sumAges += currentYear - n.getBirthyear();
	}

	if (membersCount != 0)
		return round((float)sumAges / membersCount);
	else
		return 0;
}

void Genealogy::loadFromCSV(const char* filepath)
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

	cout << "\n";

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


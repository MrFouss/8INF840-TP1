#include "Node.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <time.h>

enum TreeTraversal { INORDER, PREORDER, POSTORDER };

class Genealogy
{
private:
	int nextId;
	vector<Node>* tab;

	// get descendance with IN ORDER
	vector<Node*>* getAncestorsIN(int nodeId);
	// get descendance with PRE ORDER
	vector<Node*>* getAncestorsPRE(int nodeId);
	// get descendance with POSTORDER
	vector<Node*>* getAncestorsPOST(int nodeId);

public:
	// constructor
	Genealogy();

	// destructor
	~Genealogy();

	// return the node of the given id
	Node* getNode(int id);

	// return the node of the given couple name/firstname
	Node* getNode(string name, string firstname);

	// get the size of the family tree
	int getSize();

	// for a given id return a list of all ancestors, including the given person
	vector<Node*>* getAncestors(int node, TreeTraversal type);

	// add a new member to the family ; return 0 if success, -1 if error
	int addMember(string name, string firstname, int birthyear, EyeColor eyes);
	int addMember(string name, string firstname, int birthyear, EyeColor eyes, int knownParentId, bool left);

	// for a given color, list all members of the family with the same eye color
	vector<Node>* getGenealogyByEyes(EyeColor color);

	// list all ancestors with the same eye color, including the given person
	vector<Node>* getAncestorsByEyes(int nodeId);

	// calculation of the mean age of the family
	int meanAge();

	// load a prebuilt tree from txt file
	void loadFromCSV(char* filepath);

	// print all genealogy ; if details is true, all informations will be printed, otherwise, only firstname/name
	void printGenealogy(bool details);

	// return true if the given id exists
	bool exists(int id);

	// return index in vector of the given id ; -1 if an error occured
	int getIndex(int id);
};


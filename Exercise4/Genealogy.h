#include "Node.h"
#include <vector>
#include <fstream>
#include <sstream>

enum TreeTraversal { INORDER, PREORDER, POSTORDER };

class Genealogy
{
private:
	int nextIndex;
	vector<Node>* tab;

	// get descendance with IN ORDER
	void getDescendanceIN(int node);
	// get descendance with PRE ORDER
	void getDescendancePRE(int node);
	// get descendance with POSTORDER
	void getDescendancePOST(int node);

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

	// type is INORDER, PREORDER or POSTORDER ; person is the target
	void getDescendance(int node, TreeTraversal type);

	// add a new member to the family ; return 0 if success, -1 if error
	int addMember(string name, string firstname, int birthyear, EyeColor eyes);
	int addMember(string name, string firstname, int birthyear, EyeColor eyes, int knownParentId);

	// for a given color, list all members of the family with the same eye color
	void getGenealogyByEyes(EyeColor color);

	// list all ancestors with the same eye color, including the given person
	void getAncestorsByEyes(EyeColor color, int nodeId);

	// calculation of the mean age of the family
	float meanAge();

	// load a prebuilt tree from txt file
	void loadFromCSV(char* filepath);
};


#pragma once

#include <map>

#include <assert.h>

#include "MachineStartWorkEvent.h"
#include "MachineFinishWorkEvent.h"
#include "MachineIsRepairedEvent.h"

template <typename T>
class MachineDataLink;

class MachineLink;

// describes the behaviour of a machine that processes objects from input links and put the results on the output links
// the machine has a probability to break and takes a certain time be repaired
// the precise task of the machine must be implemented in the derived classes
class IMachine {
public:

	IMachine(std::string name, float workTime, float breakProbability, float repairTime);
	virtual ~IMachine() = default;

	std::string getName();

	// notify this machine that one of its input links has new data available
	void onInputLinkUpdated();

protected:

	// JOB DESCRIPTION

	// inheriting classes must implement these functions to actually describe the machine task
	virtual bool canStartNextJob() = 0;
	virtual void startNextJob() = 0;
	virtual void finishCurrentJob() = 0;

	// LINKS
	// giving public access to links is up to derived classes

	// setup this machine and the given link to be connected and label that link in this machine
	void linkInput(std::string name, MachineLink* link);
	void linkOutput(std::string name, MachineLink* link);
	
	// check weather a link exists based on its label
	bool hasInputLink(std::string name);
	bool hasOutputLink(std::string name);

	// give access to a link and dynamically cast it to the desired type
	// the function fails if no link is associated with the given name
	template <class T>
	MachineDataLink<T>* getInputLink(const std::string name) {
		assert(hasInputLink(name));
		return dynamic_cast<MachineDataLink<T>*>(inputLinks[name]);
	}
	template <class T>
	MachineDataLink<T>* getOutputLink(const std::string name) {
		assert(hasOutputLink(name));
		return dynamic_cast<MachineDataLink<T>*>(outputLinks[name]);
	}

private:

	// WORKING CYCLE
	// a cycle is composed of the execution of a job, and occasionnaly the repair of the machine

	// give access to certain events classes that manage the machine's work cycle
	friend MachineIsRepairedEvent;
	friend MachineFinishWorkEvent;
	friend MachineStartWorkEvent;

	// internal working cycle management
	void startWorkingCycle();
	void repairMachine();
	void endWorkingCycle();

	// FIELDS

	std::string name;
	float workTime;
	float breakProbability;
	float repairTime;
	bool isBroken;
	bool isWorking;

	// input and output links are identified by their label
	std::map<std::string, MachineLink*> inputLinks;
	std::map<std::string, MachineLink*> outputLinks;
};


#pragma once

// defines an object that can be processed by a machine
// it only contains a boolean that indicates if it has been processed
class Machineable {
public:
	Machineable();
	virtual ~Machineable() = default;

	bool isMachined() const;
	void setMachined();

private:
	bool machined;
};


#pragma once
class Machineable {
public:
	Machineable();
	virtual ~Machineable() = default;

	bool isMachined() const;
	void setMachined();

private:
	bool machined;
};


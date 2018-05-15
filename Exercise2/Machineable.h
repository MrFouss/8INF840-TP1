#pragma once
\
class Machineable {
public:
	Machineable() : machined(false) {}
	virtual ~Machineable() = default;

	bool isMachined() const { return machined; }
	void setMachined() { machined = true; }

private:
	bool machined;
};


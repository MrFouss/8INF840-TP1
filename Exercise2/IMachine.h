#pragma once

#include <string>

class IMachine {
public:
	IMachine(std::string name) : name(name) {}
	virtual ~IMachine() = default;

	virtual void tryProcessNext() = 0;
	virtual void onInputUpdate() = 0;
	virtual void onOutputUpdate() = 0;

	std::string getName() const {
		return name;
	};

private:

	std::string name;
};


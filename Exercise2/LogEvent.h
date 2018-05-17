#pragma once

#include "Event.h"
#include <iostream>
#include <string>

class LogEvent : public Event {
public:

	LogEvent(const LogEvent& e) = default;
	LogEvent(float triggerTime, std::string message) :
		Event(triggerTime), message(message) {}
	virtual ~LogEvent() = default;

	void trigger() const override {
		std::cout << "[" << getTriggerTime() << "] " << message << std::endl;
	}

	Event* clone() const override {
		return new LogEvent(*this);
	}

private:

	std::string message;
};


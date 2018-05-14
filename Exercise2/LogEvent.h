#pragma once

#include "Event.h"
#include <iostream>

class LogEvent : public Event {
public:
	LogEvent(float triggerTime, std::string message) :
		Event(triggerTime), message(message) {}

	virtual ~LogEvent() = default;

	virtual void trigger() const {
		std::cout << "[" << getTriggerTime() << "] " << message << std::endl;
	}

private:

	std::string message;
};


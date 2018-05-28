#include "LogEvent.h"

#include <iostream>

LogEvent::LogEvent(float triggerTime, std::string message) : 
	Event(triggerTime), 
	message(message) 
{}

void LogEvent::trigger() const {
	std::cout << "[" << getTriggerTime() << "] " << message << std::endl;
}

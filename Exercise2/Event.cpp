#include "Event.h"

Event::Event(const Event & other) : triggerTime(other.triggerTime) {}

Event::Event(float triggerTime) : triggerTime(triggerTime) {}

float Event::getTriggerTime() const {
	return triggerTime;
}

std::ostream & operator<<(std::ostream & os, const Event & e) {
	os << e.log();
	return os;
}

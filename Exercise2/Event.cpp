#include "Event.h"

Event::Event(const Event & other) : triggerTime(other.triggerTime) {}

Event::Event(float triggerTime) : triggerTime(triggerTime) {}

float Event::getTriggerTime() const {
	return triggerTime;
}

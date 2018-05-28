#include "Event.h"

Event::Event(float triggerTime) : 
	triggerTime(triggerTime) 
{}

float Event::getTriggerTime() const {
	return triggerTime;
}

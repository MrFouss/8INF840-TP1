#include "EventManager.h"
#include <assert.h>
#include <iostream>

EventManager::EventManager() : eventList(), time(0) {}

EventManager & EventManager::getInstance() {
	static EventManager em;
	return em;
}

EventManager::~EventManager() {
	clear();
}

void EventManager::addEvent(Event* event) {
	assert(event->getTriggerTime() >= time);
	eventList.push(event);
}

void EventManager::triggerNextEvent(bool log) {
	assert(!isEmpty());
	Event* e = eventList.top();
	eventList.pop();
	e->trigger();

	if (log) {
		std::cout << "[" << e->getTriggerTime() << "] " << *e << std::endl;
	}

	time = e->getTriggerTime();
	delete e;
}

void EventManager::clear(bool log) {
	while (!isEmpty()) {
		triggerNextEvent(log);
	}
}

bool EventManager::isEmpty() const {
	return eventList.empty();
}

float EventManager::getTime() const {
	return time;
}

bool EventManager::Posteriority::operator()(const Event * a, const Event * b) {
	return a->getTriggerTime() > b->getTriggerTime();
}

#include "EventManager.h"

#include <cassert>
#include <iostream>

#include "LogEvent.h"
#include "Event.h"

EventManager::EventManager() : 
	eventList(),
	time(0), 
	printLog(false) 
{}

EventManager* EventManager::getInstance() {
	static EventManager em;
	return &em;
}

EventManager::~EventManager() {
	while (isEmpty()) {
		Event* e = eventList.top();
		eventList.pop();
		delete e;
	}
}

void EventManager::addEvent(Event* event) {
	assert(event != 0 && event->getTriggerTime() >= time);
	eventList.push(event);
}

void EventManager::setPrintLog(bool printLog) {
	this->printLog = printLog;
}

Event * EventManager::nextEvent() const {
	return eventList.top();
}

void EventManager::triggerNextEvent() {
	assert(!isEmpty());
	Event* e = eventList.top();
	eventList.pop();
	if (dynamic_cast<LogEvent*>(e) == 0 || printLog) {
		time = e->getTriggerTime();
		e->trigger();
	}
	delete e;
}

void EventManager::triggerAllEvents() {
	while (!isEmpty()) {
		triggerNextEvent();
	}
}

bool EventManager::isEmpty() const {
	return eventList.empty();
}

float EventManager::getTime() const {
	return time;
}

bool EventManager::Posteriority::operator()(const Event * a, const Event * b) {
	return a->getTriggerTime() > b->getTriggerTime()
		|| dynamic_cast<LogEvent *>(const_cast<Event*>(b)) != 0;
}

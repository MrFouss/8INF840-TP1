#pragma once

#include <queue>
#include <functional>
#include "Event.h"

class EventManager {
public:
	static EventManager& getInstance();

	~EventManager();

	void addEvent(Event* event);
	void triggerNextEvent();
	void clear();

	bool isEmpty() const;
	float getTime() const;
	
private:
	EventManager();
	EventManager(const EventManager&) = delete;
	const EventManager& operator=(const EventManager&) = delete;

	class Posteriority {
	public:
		bool operator()(const Event * a, const Event * b);
	};

	std::priority_queue<Event*, std::vector<Event*>, Posteriority> eventList;
	float time;
};


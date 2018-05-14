#pragma once

#include <ostream>
#include <string>

class Event
{
public:
	Event(const Event& other);
	Event(float triggerTime);

	virtual ~Event() = default;

	virtual void trigger() const = 0;

	float getTriggerTime() const;

private:
	
	float triggerTime;
};


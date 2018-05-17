#pragma once

class Event
{
public:
	Event(float triggerTime) : triggerTime(triggerTime) {}
	Event(const Event& e) = default;
	virtual ~Event() = default;

	virtual void trigger() const = 0;
	virtual Event* clone() const = 0;

	float getTriggerTime() const {
		return triggerTime;
	}

private:
	
	float triggerTime;
};


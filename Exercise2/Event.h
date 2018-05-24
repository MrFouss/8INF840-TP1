#pragma once

class Event
{
public:
	Event(float triggerTime);
	virtual ~Event() = default;

	virtual void trigger() const = 0;

	float getTriggerTime() const;

private:
	
	float triggerTime;
};


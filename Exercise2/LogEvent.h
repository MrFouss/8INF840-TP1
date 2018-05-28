#pragma once

#include "Event.h"

#include <string>

class LogEvent : public Event {
public:

	LogEvent(float triggerTime, std::string message);
	virtual ~LogEvent() = default;

	void trigger() const override;

private:

	std::string message;
};


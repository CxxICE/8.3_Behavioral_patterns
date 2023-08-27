#pragma once
#include "Observer.h"

class WarningObserver : public Observer
{
public:
	WarningObserver() = default;
	void onWarning(const std::string &message) override;
};



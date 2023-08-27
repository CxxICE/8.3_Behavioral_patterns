#pragma once
#include "Observer.h"

class FatalErrorObserver : public Observer
{
public:
	FatalErrorObserver() = default;
	void onFatalError(const std::string &message) override;
};


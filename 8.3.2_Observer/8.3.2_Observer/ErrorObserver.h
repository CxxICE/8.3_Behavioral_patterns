#pragma once
#include "Observer.h"

class ErrorObserver : public Observer
{
public:
	ErrorObserver() = default;
	void onError(const std::string &message) override;
};


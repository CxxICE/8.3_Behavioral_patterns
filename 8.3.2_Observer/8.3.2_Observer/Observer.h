#pragma once
#include <iostream>
#include <fstream>
#include <string>

#include "Observed.h"

class Observed;

class Observer
{
public:
	virtual void onWarning(const std::string &message);
	virtual void onError(const std::string &message);
	virtual void onFatalError(const std::string &message);
	void addObserved(Observed *observed);
	void delObserved();
	~Observer();
private:
	Observed *_observed = nullptr;
};

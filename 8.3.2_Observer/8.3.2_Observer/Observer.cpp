#include "Observer.h"

void Observer::onWarning(const std::string &message) {};
void Observer::onError(const std::string &message) {};
void Observer::onFatalError(const std::string &message) {};

void Observer::addObserved(Observed *observed)
{
	_observed = observed;
}

void Observer::delObserved()
{
	_observed = nullptr;
}

Observer::~Observer()
{
	if (_observed)
	{
		_observed->RemoveObserver(this);
	}	
}



#include "Observer.h"

void Observer::onWarning(const std::string &message) {};
void Observer::onError(const std::string &message) {};
void Observer::onFatalError(const std::string &message) {};

void Observer::addObserved(Observed *observed)
{
	_observed = observed;
}

Observer::~Observer()
{
	_observed->RemoveObserver(this);
}



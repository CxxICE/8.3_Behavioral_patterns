#include "Observed.h"

void Observed::AddObserver(Observer *observer)
{
	_observers.push_back(observer);
	observer->addObserved(this);
}
void Observed::RemoveObserver(Observer *observer)
{
	auto it = std::remove(_observers.begin(), _observers.end(), observer);
	_observers.erase(it, _observers.end());
}
void Observed::warning(const std::string &message) const
{
	for (const auto &el : _observers)
	{
		el->onWarning(message);
	}
}
void Observed::error(const std::string &message) const
{
	for (const auto &el : _observers)
	{
		el->onError(message);
	}
}
void Observed::fatalError(const std::string &message) const
{
	for (const auto &el : _observers)
	{
		el->onFatalError(message);
	}
}

Observed::~Observed()
{
	for (const auto& el : _observers)
	{
		el->delObserved();
	}
}

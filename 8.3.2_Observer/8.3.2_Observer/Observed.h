#pragma once
#include <vector>

#include "Observer.h"

class Observer;

class Observed
{
public:
	void AddObserver(Observer *observer);
	void RemoveObserver(Observer *observer);
	void warning(const std::string &message) const;
	void error(const std::string &message) const;
	void fatalError(const std::string &message) const;
	~Observed();
private:
	std::vector<Observer*> _observers;
};


#include "WarningObserver.h"

void WarningObserver::onWarning(const std::string &message)
{
	std::cout << message << std::endl;
};


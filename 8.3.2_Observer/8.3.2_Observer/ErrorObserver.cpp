#include "ErrorObserver.h"

void ErrorObserver::onError(const std::string &message)
{
	std::ofstream file("ErrorLog.log", std::ios::app);
	if (file.is_open())
	{
		file << message << "\n";
		file.close();
	}
};


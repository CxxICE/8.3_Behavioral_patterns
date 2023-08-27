#include "FatalErrorObserver.h"

void FatalErrorObserver::onFatalError(const std::string &message)
{
	std::cout << message << std::endl;
	std::ofstream file("ErrorLog.log", std::ios::app);
	if (file.is_open())
	{
		file << message << "\n";
		file.close();
	}
};

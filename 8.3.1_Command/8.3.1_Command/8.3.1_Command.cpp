#include <iostream>
#include <chrono>
#include <string>
#include <time.h>
#include <fstream>

class LogCommand 
{
public:
	virtual ~LogCommand() = default;
	virtual void print(const std::string &message) = 0;
};

class CoutLogCommand : public LogCommand
{
public:
	CoutLogCommand() = default;

	void print(const std::string &message) override
	{
		std::cout << message << std::endl;
	};
};

class FileLogCommand : public LogCommand
{
public:
	FileLogCommand()
	{
		auto const now = std::chrono::system_clock::now();
		std::time_t newt = std::chrono::system_clock::to_time_t(now);
		std::tm buf;
		localtime_s(&buf, &newt);
		std::string year = std::to_string(1900 + buf.tm_year);
		std::string month = buf.tm_mon < 9 ? "0" + std::to_string(1 + buf.tm_mon) : std::to_string(1 + buf.tm_mon);
		std::string day = std::to_string(buf.tm_mday);
		//std::string hour = buf.tm_hour < 10 ? "0" + std::to_string(buf.tm_hour) : std::to_string(buf.tm_hour);
		//std::string min = buf.tm_min < 10 ? "0" + std::to_string(buf.tm_min) : std::to_string(buf.tm_min);
		//std::string sec = buf.tm_sec < 10 ? "0" + std::to_string(buf.tm_sec) : std::to_string(buf.tm_sec);
		filename = "LogFile_" + year + "." + month + "." + day + ".log";
	};

	void print(const std::string &message) override
	{
		std::ofstream file(filename, std::ios::app);
		if (file.is_open())
		{
			file << message << "\n";
			file.close();
		}
	};
private:
	std::string filename;
};

class Invoker
{
public:
	Invoker(LogCommand *lc)
	{
		_lc = lc;
	}
	void setCommand(LogCommand *lc)
	{
		_lc = lc;
	}
	void print(const std::string &message)
	{
		_lc->print(message);
	}
private:
	LogCommand *_lc;
};

int main()
{
	FileLogCommand flog;
	CoutLogCommand clog;
	
	Invoker inv(&clog);
	inv.print("cout_log1");
	inv.print("cout_log2");
	inv.print("cout_log3");

	inv.setCommand(&flog);
	inv.print("file_log1");
	inv.print("file_log2");
	inv.print("file_log3");
	return 0;
}



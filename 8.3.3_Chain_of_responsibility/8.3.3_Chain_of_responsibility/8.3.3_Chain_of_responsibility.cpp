#include <iostream>
#include <fstream>
#include <exception>

class LogMessage 
{
public:	
	enum class Type
	{
		Warning,
		Error,
		FatalError,
		Unknown
	};
	virtual Type type() const = 0;
	virtual const std::string &message() const = 0;	
};

class WarningMessage : public LogMessage
{
public:
	explicit WarningMessage(const std::string &message)
	{
		_message = message;
	}
	Type type() const override
	{
		return Type::Warning;
	};
	const std::string &message() const
	{
		return _message;
	};
private:
	std::string _message;
};

class ErrorMessage : public LogMessage
{
public:
	explicit ErrorMessage(const std::string &message)
	{
		_message = message;
	}
	Type type() const override
	{
		return Type::Error;
	};
	const std::string &message() const
	{
		return _message;
	};
private:
	std::string _message;
};

class FatalErrorMessage : public LogMessage
{
public:
	explicit FatalErrorMessage(const std::string &message)
	{
		_message = message;
	}
	Type type() const override
	{
		return Type::FatalError;
	};
	const std::string &message() const
	{
		return _message;
	};
private:
	std::string _message;
};

class UnknownMessage : public LogMessage
{
public:
	explicit UnknownMessage(const std::string &message)
	{
		_message = message;
	}
	Type type() const override
	{
		return Type::Unknown;
	};
	const std::string &message() const
	{
		return _message;
	};
private:
	std::string _message;
};

class LogHandler 
{
public:
	explicit LogHandler(std::unique_ptr<LogHandler> next) : next_(std::move(next)) {}
	void receiveLog(const LogMessage &message) 
	{
		if (handleLog(message)) 
		{
			return;
		}
		if (!next_) 
		{ 
			throw std::runtime_error("Unhandled Message");//только в случае неверно созданной Chain_of_responsibility, когда не нашлось нужного обработчика
		}
		next_->receiveLog(message);
	}
private:
	virtual bool handleLog(const LogMessage &message) = 0;
	std::unique_ptr<LogHandler> next_;
};

class WarningHandler : public LogHandler
{
public:
	using LogHandler::LogHandler;
private:
	virtual bool handleLog(const LogMessage &message) override
	{
		if (message.type() != LogMessage::Type::Warning)
		{
			return false;
		}
		std::cout << message.message() << std::endl;

		return true;
	};
};

class ErrorHandler : public LogHandler
{
public:
	using LogHandler::LogHandler;
private:
	virtual bool handleLog(const LogMessage &message) override
	{
		if (message.type() != LogMessage::Type::Error)
		{
			return false;
		}
		std::ofstream file("ErrorLog.log", std::ios::app);
		if (file.is_open())
		{
			file << message.message() << "\n";
			file.close();
		}
		return true;
	};
};

class FatalErrorHandler : public LogHandler
{
public:
	using LogHandler::LogHandler;
private:
	virtual bool handleLog(const LogMessage &message) override
	{
		if (message.type() != LogMessage::Type::FatalError)
		{
			return false;
		}
		std::string error = "Fatal Error: " + message.message();
		throw std::runtime_error(error);
		return true;
	};
};

class UnknownMessageHandler : public LogHandler
{
public:
	using LogHandler::LogHandler;
private:
	virtual bool handleLog(const LogMessage &message) override
	{
		if (message.type() != LogMessage::Type::Unknown)
		{
			return false;
		}
		throw std::runtime_error("Unknown type message handled!");
	};
};


int main()
{
	setlocale(LC_ALL, "RU");
	{
		auto unknownMessageHandler = std::make_unique<UnknownMessageHandler>(nullptr);
		auto fatalErrorHandlerr = std::make_unique<FatalErrorHandler>(std::move(unknownMessageHandler));
		auto errorHandler = std::make_unique<ErrorHandler>(std::move(fatalErrorHandlerr));
		auto handler = std::make_unique<WarningHandler>(std::move(errorHandler));
		try
		{
			handler->receiveLog(WarningMessage("Предупреждение!"));
			handler->receiveLog(ErrorMessage("Ошибка 001!"));
			handler->receiveLog(FatalErrorMessage("Фатальная ошибка!"));
		}
		catch (const std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}

		try
		{
			handler->receiveLog(UnknownMessage("Неизвестная ошибка!"));
		}
		catch (const std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	std::cout << "\n\n";
	{
		//из цепочки исключен обработчик UnknownHandler
		auto fatalErrorHandlerr = std::make_unique<FatalErrorHandler>(nullptr);
		auto errorHandler = std::make_unique<ErrorHandler>(std::move(fatalErrorHandlerr));
		auto handler = std::make_unique<WarningHandler>(std::move(errorHandler));
		try
		{
			handler->receiveLog(WarningMessage("Предупреждение!"));
			handler->receiveLog(ErrorMessage("Ошибка 001!"));
			handler->receiveLog(FatalErrorMessage("Фатальная ошибка!"));
		}
		catch (const std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}

		try
		{
			handler->receiveLog(UnknownMessage("Неизвестная ошибка!"));
		}
		catch (const std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	return 0;    
}

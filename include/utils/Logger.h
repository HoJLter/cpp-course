#pragma once
#include <string>
#include <memory>
#include <fstream>

class ILogger;

enum class LogLevel {
	Debug,
	Info,
	Warn,
	Error
};

enum class LoggerType {
	Console,
	File
};

class Log {
private:
	static std::unique_ptr<ILogger> curLogger;
	static std::string filename;

public:
	static void setLogger(LoggerType type);
	static void setFilename(const std::string& filename);

	static void debug(const std::string& msg);
	static void info(const std::string& msg);
	static void warn(const std::string& msg);
	static void error(const std::string& msg);
};

class ILogger {
public:
	virtual ~ILogger() = default;
	virtual void log(LogLevel lvl, const std::string& msg) = 0;

protected:
	std::string getTimeString();
	std::string makeRecord(LogLevel lvl, const std::string& msg);
};

class FileLogger : public ILogger {
private:
	std::ofstream ofs;

public:
	FileLogger(std::string filename);
	FileLogger();

	void log(LogLevel lvl, const std::string& msg) override;
};

class ConsoleLogger : public ILogger {
public:
	void log(LogLevel lvl, const std::string& msg) override;
};
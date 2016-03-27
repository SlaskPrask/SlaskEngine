#pragma once
class LogHandler
{
private:
	void writeLog(const char *logger, const char *str, int type);

public:
	static LogHandler* instance();
	void init();
	~LogHandler();

	void log(const char *str);
	void error(const char *str);
	void error(const char* logger, const char *str);
	void log(const char *logger, const char *str);
	void notify(const char *str);

	enum LogType {Log,Notify,Error};
};


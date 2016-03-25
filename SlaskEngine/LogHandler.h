#pragma once
class LogHandler
{
private:

public:
	static LogHandler* instance();
	void init();
	~LogHandler();
};


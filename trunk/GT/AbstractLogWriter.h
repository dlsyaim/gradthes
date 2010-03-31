#pragma once

class AbstractLogWriter
{
public:
	AbstractLogWriter(void);
	virtual ~AbstractLogWriter(void);
	// Write the log file
	void writeLogFile(void);
	// A function to be overridden in sub-classes
	virtual CString constructLogString(void) = 0;
};

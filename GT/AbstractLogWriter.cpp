#include "StdAfx.h"
#include <fstream>
#include "AbstractLogWriter.h"

AbstractLogWriter::AbstractLogWriter(void)
{
}

AbstractLogWriter::~AbstractLogWriter(void)
{
}


void AbstractLogWriter::writeLogFile(void)
{
	CString log = constructLogString();

	std::ofstream os("log.log");
	os.write(log, log.GetLength());
	
}

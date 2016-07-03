
// stdafx.cpp : source file that includes just the standard includes
// SimpleDcmViewer.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"




#define LINE_SIZE 2048


void t_info(const char* fmt, ...)
{
	char line[LINE_SIZE];
	va_list ap;

	va_start(ap, fmt);
	vsprintf_s(line, LINE_SIZE, fmt, ap);
	va_end(ap);

	fprintf(stderr, "%s", line);
}

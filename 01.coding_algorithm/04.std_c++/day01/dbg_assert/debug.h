/*****************************************
* Copyright (C) 2018 * Ltd. All rights reserved.
* 
* File name   : debug.h
* Author      : longbin
* Created date: 2018-08-09 21:57:32
* Description : 
*
*******************************************/

#ifndef __DEBUG_H__
#define __DEBUG_H__
#include <stdio.h>
#include <stdlib.h>
#include <execinfo.h>

/* include <execinfo.h> and <stdlib.h> to use this macro */
#define DBG_ASSERT(x) do { \
	if (x) { break; } \
	printf("\r\n------ %s [%d] ------\r\n", __FILE__, __LINE__);\
	void *pptrace_raw[32] = {0}; \
	char **pptrace_str = NULL; \
	int  trace_num = 0, i = 0; \
	trace_num = backtrace(pptrace_raw, 32); \
	pptrace_str = (char **)backtrace_symbols(pptrace_raw, trace_num); \
	for (i = 0; i < trace_num; i++) { printf("%s\r\n", pptrace_str[i]); } \
	if (pptrace_str) { free(pptrace_str); } \
} while (0);

#endif


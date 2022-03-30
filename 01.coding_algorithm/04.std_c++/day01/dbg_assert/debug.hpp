/*****************************************
* Copyright (C) 2018 * Ltd. All rights reserved.
* 
* File name   : debug.hpp
* Author      : longbin
* Created date: 2018-08-09 21:57:32
* Description : 
*
*******************************************/

#ifndef __DEBUG_HPP__
#define __DEBUG_HPP__
#include <iostream>
#include <execinfo.h>

/* include <execinfo.h> to use this macro */
#define DBG_ASSERT(x) do { \
	if (x) { break; } \
	std::cout << "\r\n------ " <<  __FILE__ << " " <<  __LINE__ << " ------" << endl;\
	void *pptrace_raw[32] = {0}; \
	char **pptrace_str = NULL; \
	int  trace_num = 0, i = 0; \
	trace_num = backtrace(pptrace_raw, 32); \
	pptrace_str = (char **)backtrace_symbols(pptrace_raw, trace_num); \
	for (i = 0; i < trace_num; i++) { std::cout << pptrace_str[i] << endl; } \
	if (pptrace_str) { delete pptrace_str; } \
} while (0);

#endif


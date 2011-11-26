/*
 * CommandLine.h
 *
 *  Created on: 21.11.2011
 *      Author: Tim
 */

#pragma once/* COMMANDLINE_H_ */

#include <string.h>
#include <stdlib.h>

enum CL_ParamType
{
	CLPT_NONE = 0,
	CLPT_INT,
	CLPT_FLOAT,
	CLPT_STRING
};

typedef struct {
	CL_ParamType type;
	union {
		int intvalue;
		float floatvalue;
		char stringvalue[128];
	};
} CL_ParamValue;

typedef struct {
	char name[128];
	CL_ParamValue value;
} CL_Param;

struct CL_ParamEntry
{
	CL_Param param;
	CL_ParamEntry* Next;
};

struct CL_ParamList
{
	unsigned char NumParams;
	CL_ParamEntry* Head;
};

void ParseCL_Value(CL_Param* pParam, const char* value);
void AppendCL_Param(CL_ParamList* pList, const char* name, const char* value);
void DeleteCL_Params(CL_ParamEntry* pStart);

CL_ParamList ParseCommandLine(int argc, char** argv);

CL_ParamValue CheckCL_Param(CL_ParamList* pList, const char* Param);

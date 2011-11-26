/*
 * CommandLine.h
 *
 *  Created on: 21.11.2011
 *      Author: Tim
 */

#include "CommandLine.h"

void ParseCL_Value(CL_Param* pParam, const char* value)
{
	pParam->value.type = CLPT_NONE;
	if(strlen(value) == 1)
	{
		pParam->value.type = CLPT_STRING;
	}
	else
	{
		switch(value[0])
		{
		case 'i':
			pParam->value.type = CLPT_INT;
			break;
		case 'f':
			pParam->value.type = CLPT_FLOAT;
			break;
		case 's':
		default:
			pParam->value.type = CLPT_STRING;
			break;
		}
		value++;
	}

	switch(pParam->value.type)
	{
	case CLPT_INT:
		pParam->value.intvalue = atoi(value);
		break;
	case CLPT_FLOAT:
		pParam->value.floatvalue = atof(value);
		break;
	case CLPT_STRING:
		strcpy(pParam->value.stringvalue, value);
		break;
	case CLPT_NONE:
		pParam->value.intvalue = 0;
		pParam->value.floatvalue = 0;
	}
}

void AppendCL_Param(CL_ParamList* pList, const char* name, const char* value)
{
	CL_ParamEntry* pEntry = new CL_ParamEntry;
	strcpy(pEntry->param.name, name);

	ParseCL_Value(&pEntry->param, value);

	pEntry->Next = pList->Head;
	pList->Head = pEntry;
}

void DeleteCL_Params(CL_ParamEntry* pStart)
{
	if(pStart == NULL)
		return;
	else
	{
		DeleteCL_Params(pStart->Next);
		delete pStart;
	}
}

CL_ParamList ParseCommandLine(int argc, char** argv)
{
	CL_ParamList ReturnList;

	int MaxParam = (argc-1>32)?16:(argc-1)/2;
	ReturnList.NumParams = MaxParam;
	ReturnList.Head = NULL;

	for(int i=0;i<MaxParam;i++)
	{
		const char* Name = argv[i*2+1];
		const char* Value = argv[i*2+2];

		AppendCL_Param(&ReturnList, Name, Value);
	}

	return ReturnList;
}

CL_ParamValue CheckCL_Param(CL_ParamList* pList, const char* Param)
{
	CL_ParamEntry* pEntry = pList->Head;
	for(int i=0;i<pList->NumParams;i++)
	{
		if(strcmp(pEntry->param.name,Param) == 0)
			return pEntry->param.value;
		pEntry = pEntry->Next;
	}
	CL_ParamValue NullValue = {CLPT_NONE, {0}};
	return NullValue;
}

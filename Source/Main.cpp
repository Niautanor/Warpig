/*
 * Main.cpp
 *
 *  Created on: 21.11.2011
 *      Author: Tim
 */

#include <iostream>

#include "CommandLine.h"

#include "Main.h"

Main::Main()
{
	// TODO Auto-generated constructor stub

}

int main(int argc, char** argv)
{
	CL_ParamList CL_Params = ParseCommandLine(argc, argv);
	char* s = CheckCL_Param(&CL_Params, "asdf").stringvalue;
	std::cout << "JEAS" << std::endl;
	std::cout << s;
	return 0;
}

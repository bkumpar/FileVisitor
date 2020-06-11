// ArgParser.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <BUtils.h>
#include "FileVisitor.h"

using namespace datetime_utils;

void onFile(void*, FileVisitorEventArguments &e)
{

}

void onFolder(void*, FileVisitorEventArguments &e)
{

}

int _tmain(int argc, _TCHAR* argv[])
{
	FileVisitor* fv = new FileVisitor();

}
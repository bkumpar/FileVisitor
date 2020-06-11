#pragma once
#include "StdAfx.h"
#include "ExportImport.h"
#include <string>
#include <BEvent.h>
//#include <BControl.h>

typedef unsigned long long filesize_t;

class FileVisitorEventArguments :  public EventArguments
{
public:
	FileVisitorEventArguments(WIN32_FIND_DATA findData, std::wstring path, std::wstring fileName, bool recursive)
		: findData(findData), path(path), fileName(fileName), recursive(recursive){};

//private:
	std::wstring path;
	std::wstring fileName;
    bool recursive;
	WIN32_FIND_DATA findData;
};

IMPORT_EXPORT class FileVisitor // : public BControl
{
public:

	typedef void (FileVisitor::*OnFileHandler)(void*, FileVisitorEventArguments &e);
	typedef void (FileVisitor::*OnFolderHandler)(void*, FileVisitorEventArguments &e);

	FileVisitor();
	~FileVisitor();

    void run(const std::wstring& root, const std::wstring& pattern, bool recursive );
	void setOnFileHandler(void* target, OnFileHandler onFileHandler);
	void setOnFolderHandler(void* target, OnFolderHandler onFolderHandler);

private:
	std::wstring appendPath(std::wstring root, std::wstring path);

	OnFileHandler _onFileHandler;
	void * _onFileTarget;

	OnFolderHandler _onFolderHandler;
	void * _onFolderTarget;


};


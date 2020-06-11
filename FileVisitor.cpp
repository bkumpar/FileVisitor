#include "stdafx.h"
#include "FileVisitor.h"
#include "WildcardMatch.h"


FileVisitor::FileVisitor()
{
	_onFileHandler = NULL;
	_onFolderHandler= NULL;
}

FileVisitor::~FileVisitor()
{

}

void FileVisitor::run(const std::wstring& root, const std::wstring& pattern, bool recursive )

{
	HANDLE hFile;
	WIN32_FIND_DATA file;
	std::wstring currentFolder(L".");
	std::wstring parentFolder(L"..");
	std::wstring folderSeparator(L"\\");
	std::wstring allFiles(L"*.*");
	std::wstring search = appendPath(root, allFiles);
	hFile = FindFirstFile(search.c_str() , &file);
	if ( hFile )
	{
		while ( FindNextFile( hFile, &file))
		{
			std::wstring fileName = file.cFileName;
			std::wstring fullPath = appendPath(root, fileName);
			if(fileName == currentFolder || fileName == parentFolder )
			{
				continue;
			}

			bool match = wildcardMatch(fullPath, pattern);
			// It could be a directory we are looking at
			// if so look into that dir
			if ( file.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY )
			{
				FileVisitorEventArguments e(file, root, fileName, recursive);
				if(_onFolderHandler && match  /* && _onFileTarget */)
				{

					FileVisitor* target =  (FileVisitor*)_onFolderTarget;
					(target->*_onFolderHandler)(this, e);
				}
				std::wstring newRoot = appendPath(root, fileName);
				if(e.recursive )
				{
					run( newRoot, pattern, e.recursive );
				}
			}
			else
			{
				if(_onFileHandler && match /* && _onFileTarget */)
				{
					FileVisitorEventArguments e(file, root, fileName, recursive);
					FileVisitor* target =  (FileVisitor*)_onFileTarget;
					(target->*_onFileHandler)(this, e);
				}
			}
		}
		FindClose( hFile );
	}
	return ;

}

void FileVisitor::setOnFileHandler(void* target, OnFileHandler onFileHandler)
{
	_onFileHandler = onFileHandler;
	_onFileTarget = target;
}

void FileVisitor::setOnFolderHandler(void* target, OnFolderHandler onFolderHandler)
{
	_onFolderHandler = onFolderHandler;
	_onFolderTarget = target;
}

std::wstring FileVisitor::appendPath(std::wstring root, std::wstring path)
{
	std::wstring folderSeparator(L"\\");
	if( folderSeparator.front() != root.back() )
	{
		root.append(folderSeparator);
	}
	
	return 	root.append(path);
}

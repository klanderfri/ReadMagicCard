#include "stdafx.h"
#include "FileHandling.h"
#include <experimental\filesystem>
#include <chrono>
#include "boost\algorithm\string.hpp"
#include "boost\filesystem.hpp"

namespace fs = std::experimental::filesystem;
using namespace std;

const wstring FileHandling::MTG_IMAGES_WORKING_FOLDER = L"MtG-cards";
mutex FileHandling::m_fileLock;
mutex FileHandling::m_createFolderLock;

FileHandling::FileHandling()
{
}

FileHandling::~FileHandling()
{
}

wstring FileHandling::GetMtgImageFileFolderPath(Session* session) {

	//Create the file path.
	return session->systemMethods->GetUserPicturesFileDirectory() + MTG_IMAGES_WORKING_FOLDER + L"\\";
}

vector<wstring> FileHandling::GetMtgImageFilePaths(Session* session, wstring fullFolderPath) {

	//Create a list holding the filenames.
	vector<wstring> filepaths;

	//Run the reader for every card in the working folder.
	for (auto & p : fs::directory_iterator(fullFolderPath)) {

		//Fetch the file name.
		wstring filePath = p.path().wstring();

		//Skip all folders.
		if (boost::filesystem::is_directory(filePath)) {
			continue;
		}

		//Add the file path to the vector.
		filepaths.push_back(filePath);
	}

	return filepaths;
}

wstring FileHandling::AddRowToFile(Session* session, wstring textToWrite, wstring fileName, wstring subFolder) {

	return AddRowToFile(session, textToWrite, fileName, subFolder, m_fileLock);
}

wstring FileHandling::AddRowToFile(Session* session, wstring textToWrite, wstring fileName, wstring subFolder, std::mutex& fileLock) {

	wstring folderPath = GetSubFolderPath(session, subFolder);
	wstring fullFilePath = folderPath + fileName;

	if (CreateFileDirectory(folderPath))
	{
		fileLock.lock();

		//Implemented as suggested at
		//http://www.publicstaticfinal.com/2015/12/18/converting-stdwstring-to-utf-8-in-c-x11-and-writing-utf-8-files-with-fstream/
		ofstream file(fullFilePath, fstream::in | fstream::out | fstream::app);
		wbuffer_convert<codecvt_utf8<wchar_t>> converter(file.rdbuf());
		wostream out(&converter);
		out << textToWrite << endl;
		file.close();

		fileLock.unlock();
	}
	else
	{
		//Failed to create directory.
		throw SaveException("Could not create file directory: " + session->systemMethods->ToString(folderPath));
	}

	return fullFilePath;
}

wstring FileHandling::GetSubFolderPath(Session* session, wstring subFolder)
{
	//Check that we actually got a subfolder.
	if (subFolder.empty()) {
		throw OperationException("The subFolder parameter cannot be empty!");
	}

	//Create the file path.
	return FileHandling::GetMtgImageFileFolderPath(session) + subFolder + L"\\";
}

bool FileHandling::CreateFileDirectory(wstring fullFolderPath) {

	while (!m_createFolderLock.try_lock()) {
		this_thread::sleep_for(chrono::milliseconds(1));
	}

	bool folderExists = true;
	if (!boost::filesystem::exists(fullFolderPath)) {
		folderExists = boost::filesystem::create_directories(fullFolderPath);
	}

	m_createFolderLock.unlock();

	return folderExists;
}

wstring FileHandling::CreateFileNumberPostfix(int currentFileNumber, int amountOfFiles) {

	if (currentFileNumber < 1) {
		throw ParameterException("The first file to get a postfix must have a number bigger than zero!", "currentFileNumber");
	}

	wstring numberStr = to_wstring(currentFileNumber);

	if (amountOfFiles > 0) {
		return L" (" + numberStr + L" of " + to_wstring(amountOfFiles) + L")";
	}
	else {
		return L" (" + numberStr + L")";
	}
}

double FileHandling::CompareFilenames(std::wstring filename1, std::wstring filename2) {

	wstring temp_name1 = filename1;
	wstring temp_name2 = filename2;
	boost::to_lower(temp_name1);
	boost::to_lower(temp_name2);

	return temp_name1.compare(temp_name2);
}

#include "stdafx.h"
#include "SaveOcvImage.h"
#include "FileHandling.h"
#include <opencv2\imgcodecs.hpp>

using namespace std;
using namespace cv;

SaveOcvImage::SaveOcvImage()
{
}

SaveOcvImage::~SaveOcvImage()
{
}

//Saves the image and gives the specified name to the file.
void SaveOcvImage::SaveImageData(SystemMethods* systemMethods, Mat imageToSave, wstring fileNameOfSavedFile, wstring subFolder)
{
	if (subFolder.empty()) {
		throw ParameterException("The subfolder cannot be empty!", "subFolder");
	}

	//Get the path the image should be saved to.
	wstring saveInFolderPath = FileHandling::GetSubFolderPath(systemMethods, subFolder);
	wstring savePath = saveInFolderPath + fileNameOfSavedFile;

	if (FileHandling::CreateFileDirectory(saveInFolderPath))
	{
		//Create grey scale image.
		string pathParameter = systemMethods->ToString(savePath);
		bool couldWriteToFile = imwrite(pathParameter, imageToSave);

		if (!couldWriteToFile) {
			throw SaveException("Could not write image to file: " + systemMethods->ToString(savePath));
		}
	}
	else
	{
		//Failed to create directory.
		throw SaveException("Could not create file directory: " + systemMethods->ToString(saveInFolderPath));
	}
}
#include "stdafx.h"
#include "StoreCardProcessingData.h"
#include "SaveOcvImage.h"

using namespace std;

const wstring StoreCardProcessingData::SubfolderName = L"Image Data";
bool StoreCardProcessingData::hasSetSystemMethods = false;
SystemMethods* StoreCardProcessingData::systemMethods;
mutex StoreCardProcessingData::fl_OcrConfidence;
mutex StoreCardProcessingData::fl_SideRelations;
bool StoreCardProcessingData::hwfh_OcrConfidence = false;
bool StoreCardProcessingData::hwfh_SideRelations = false;

StoreCardProcessingData::StoreCardProcessingData(SystemMethods* systemMethods)
{
	if (!hasSetSystemMethods) {
		this->systemMethods = systemMethods;
		this->hasSetSystemMethods = true;
	}
}

StoreCardProcessingData::~StoreCardProcessingData()
{
}

wstring StoreCardProcessingData::StoreFinalResult(vector<CardNameInfo> result) {

	wstring textToAdd = L"Image file name\tCard name\tCard type\tOCR confidence\tSuccess\n";
	for (CardNameInfo info : result) {

		textToAdd +=
			info.FileName +
			L"\t" + info.CardName +
			L"\t" + to_wstring(info.CardType) +
			L"\t" + to_wstring(info.Confidence) +
			L"\t" + to_wstring(info.IsConfidentTitle()) +
			L"\n";

		//Store the extracted card so the user can use it (for example, to showing before selling it).
		SaveOcvImage::SaveImageData(systemMethods, info.ExtractedCardImage, info.FileName, SubfolderName + L"\\Extracted Cards");
	}
	textToAdd = textToAdd.substr(0, textToAdd.size() - 1);

	return FileHandling::AddRowToFile(systemMethods, textToAdd, L"CardTitles.txt", SubfolderName);
}

wstring StoreCardProcessingData::StoreOcrConfidence(wstring imageFileName, int numberOfCardReadTries, wstring ocrResult, int ocrConfidence) {

	vector<wstring> headers{ L"Image file name", L"Number of tries", L"OCR result", L"OCR confidence" };
	vector<wstring> rowData{ imageFileName, to_wstring(numberOfCardReadTries), ocrResult, to_wstring(ocrConfidence) };

	return writeToFile(L"TitleDecodeConfidence.txt", fl_OcrConfidence, hwfh_OcrConfidence, headers, rowData);
}

wstring StoreCardProcessingData::StoreSideRelations(wstring imageFileName, float sideFactor) {

	vector<wstring> headers{ L"Image file name", L"Long side to short side" };
	vector<wstring> rowData{ imageFileName, systemMethods->ToWString(sideFactor) };

	return writeToFile(L"CardSidesRelations.txt", fl_SideRelations, hwfh_SideRelations, headers, rowData);
}

wstring StoreCardProcessingData::writeToFile(wstring textfileName, mutex& fileLock, bool& hasWrittenFileHeader, vector<wstring> headers, vector<wstring> rowData) {

	//Make sure the header can't be written by two different threads.
	fileLock.lock();
	if (!hasWrittenFileHeader) {

		wstring rowToAdd = headers[0];
		for (size_t i = 1; i < headers.size(); i++) {
			rowToAdd += L"\t" + headers[i];
		}

		FileHandling::AddRowToFile(systemMethods, rowToAdd, textfileName, SubfolderName);

		hasWrittenFileHeader = true;
	}
	fileLock.unlock();

	wstring rowToAdd = rowData[0];
	for (size_t i = 1; i < rowData.size(); i++) {
		rowToAdd += L"\t" + rowData[i];
	}

	return FileHandling::AddRowToFile(systemMethods, rowToAdd, textfileName, SubfolderName, fileLock);
}

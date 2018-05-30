// CardReaderLibrary.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "CardReaderLibrary.h"
#include "ApiCodeConnector.h"

using namespace std;

namespace CardReaderLibrary {

	char const* CRLibrary::ReadCardTitles(char const* input) {

		ApiCodeConnector connector = ApiCodeConnector();
		string resultData = connector.ReadCardTitles(input);
		string* result = new string(resultData);

		return result->c_str();
	}

	bool CRLibrary::CompareCardNames(char const* cardName1, char const* cardName2) {

		return ApiCodeConnector().CompareCardNames(cardName1, cardName2);
	}

	int CRLibrary::GetMaxCardAmount() {

		return ApiCodeConnector().GetMaxCardAmount();
	}
}
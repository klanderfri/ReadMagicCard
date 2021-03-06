#include "stdafx.h"
#include "CardReaderLibrary.h"
#include "ApiCodeConnector.h"

namespace CRLibrary {

	__declspec(dllexport) bool CompareCardNames(char const* cardName1, char const* cardName2) {

		return ApiCodeConnector().CompareCardNames(cardName1, cardName2);
	}

	__declspec(dllexport) void __cdecl ReadCardTitles(char const* input, char* result, int maxLength) {

		ApiCodeConnector connector = ApiCodeConnector();
		std::string resultData = connector.ReadCardTitles(input);
		strcpy_s(result, maxLength, resultData.c_str());
	}

	__declspec(dllexport) int GetMaxCardAmount() {

		return ApiCodeConnector().GetMaxCardAmount();
	}

	__declspec(dllexport) void __cdecl GetResultExample(char* result, int maxLength) {

		std::string resultData = "C:\\Users\\BjornLa\\Pictures\\MtG-cards\\Arterial Flow.jpg;Arterial Flow;1;82;1;C:\\MTG-card\\Zombie - Token.jpg;ZOMBIE;8;79;1;";
		strcpy_s(result, maxLength, resultData.c_str());
	}
}

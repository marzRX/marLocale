#pragma once

#include <stdio.h>
#include <fstream>
#include <iostream>
#ifdef _WIN32
#include <Windows.h>
#else
#include <locale.h>
#endif

// Error codes used by the localization functions.
// ローカライゼーション機能に使用するエラーコード。
enum ErrorCode {
  JSON_Success = 0,
  JSON_FileNotFound = -1,
  JSON_ParseError = -2
};

// Change the language of the application.
int setLanguage(const std::string& languageCode);

// Return the translation for the given source text.
std::string translate(const std::string& source);

// Optional function for language changes, intended to be used as a callback.
void onLanguageChanged(const std::string& languageCode);

//----------------------------------------------------------------------
// Determines if the operating system is set to a Japanese locale.
bool isJapaneseOS();

// Determines if the operating system is set to an English locale.
bool isEnglishOS();

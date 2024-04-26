#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include "marLocale.h"

#define USE_ENVIRONMENT_BASED_LOCALE

// Use the JSON library namespace.
// JSONライブラリの名前空間を使う。
using json = nlohmann::json;

// Global dictionary to hold translation data.
// 翻訳情報を保持するためのグローバル辞書。
std::map<std::string, std::string> translations;

// Function to load translation data from a specified JSON file into std::map.
// 指定されたJSONファイルから翻訳データを読み込み、std::mapに格納する関数。
int loadTranslationMap(const std::string& filename) {
  std::ifstream file(filename);
  if (!file) {
    // Return error if the JSON file is not found.
    // JSONファイルが見つからない場合にエラーを返す。
    return JSON_FileNotFound;
  }
  try {
    // Safely load the contents of the JSON file.
    // json::parse throws an exception if parsing fails.
    // JSONファイルの内容を安全に読み込む。
    // パースに失敗した場合、json::parseは例外を投げます。
    json j = json::parse(file);

    // Clear existing translation data
    // 現存の翻訳データをクリア。
    translations.clear();
    for (auto& element : j.items()) {
      // Update with new data.
      // 新しいデータで更新。
      translations[element.key()] = element.value(); 
    }
  } catch (const json::parse_error& e) {
    std::cerr << "JSON parse error in file '" << filename << "': " << e.what() << std::endl;
    // Handle the case where a parse error occurs.
    // パースエラーが発生した場合の処理。
    return JSON_ParseError;
  }
  return JSON_Success;
}

// Change the language of the application.
// アプリケーションの言語を変更する関数。指定された言語コードに基づいて、
// 適切なJSON翻訳ファイルをロードします。
int setLanguage(const std::string& languageCode) {
  std::string filename = "lang/translations_" + languageCode + ".json";
  return loadTranslationMap(filename);
}

// Return the translation for the given source text.
// ソーステキストに対応する翻訳を返す関数。翻訳が見つからない場合は、
// ソーステキストをそのまま返します。
std::string translate(const std::string& source) {
  auto it = translations.find(source);
  if (it != translations.end()) {
    return it->second;
  }
  // If no translation is found, return the original text.
  // 翻訳が見つからない場合は元の文字列を返す。
  return source;
}

// Optional function for language changes, intended to be used as a callback.
// 言語変更のためのオプショナル関数。コールバック関数として使用することを想定。
void onLanguageChanged(const std::string& languageCode) {
  int result = setLanguage(languageCode);
  if (result != JSON_Success) {
    std::cerr << "Error loading language file for: " << languageCode << std::endl;
  }
}

//----------------------------------------------------------------------
// The following functions are used to determine the operating system's language and are utilized to set the display language at the application's initial launch.
// For example, if you are using a Spanish OS, the following initialization might be useful:
// 以下の関数群はオペレーティングシステムの言語を判定し、アプリケーションの初回起動時に表示言語を決定するために使用されます。
// 例えば、もしスペイン語のOSを使用している場合、次のような初期化処理が便利です：
// if (isSpanishOS()) {
//   setLanguage("es");
// } else {
//   setLanguage("en");
// }
// In such cases, consider adding a function like isSpanishOS().
// This function can be implemented using the appropriate LANGID or locale string ("es_ES").
// このような条件に対応するために、isSpanishOS() という関数を追加することを検討してください。
// この関数は、適切な LANGID やロケール文字列 ("es_ES") を使用して実装できます。
//----------------------------------------------------------------------

// Determines if the operating system is set to a Japanese locale.
// オペレーティングシステムが日本語ロケールに設定されているかどうかを判定します。
bool isJapaneseOS()
{
  bool result = false;
#ifdef _WIN32
  // Windows
  LANGID langID = GetSystemDefaultLangID();
  if (langID == 1041) {
    result = true; // The OS is Japanese
  }
#elif defined(__linux__)
  // Linux
#ifdef USE_ENVIRONMENT_BASED_LOCALE
  // Considers the OS as Japanese if Japanese input is added, even if the system UI language is English.
  // 英語OSであっても日本語入力が追加されていれば日本語と判断
  // Set locale from environment variables.
  // 環境変数からロケールを設定します。
  setlocale(LC_ALL, "");
  // Get the current locale setting.
  // 現在のロケール設定を取得します。
  const char* locale = setlocale(LC_ALL, NULL);
  if (locale) {
    if (strstr(locale, "ja_JP") != nullptr) {
      result = true; // The OS is Japanese
    }
  }
#else
  // Determines based on the system UI language.
  // システムのUI言語に基づいて判断
  const char* lang = getenv("LANG");
  if (lang) {
    if (strstr(lang, "ja_JP") != nullptr) {
      result = true; // OS is Japanese
    }
  }
#endif // USE_ENVIRONMENT_BASED_LOCALE
#else
  // Other platforms
  // Code to handle other platforms can be added here.
  // 他のプラットフォームのためのコードはここに追加することができます。
#endif // _WIN32, __linux__, or other platforms
  return result;
}

// Determines if the operating system is set to an English locale.
// オペレーティングシステムが英語ロケールに設定されているかどうかを判定します。
bool isEnglishOS()
{
  bool result = false;
#ifdef _WIN32
  // Windows
  LANGID langID = GetSystemDefaultLangID();
  if (langID == 1033) {
    result = true; // The OS is English
  }
#elif defined(__linux__)
  // Linux
  // Set locale from environment variables.
  // 環境変数からロケールを設定します。
  setlocale(LC_ALL, "");
  // Get the current locale setting.
  // 現在のロケール設定を取得します。
  const char* locale = setlocale(LC_ALL, NULL);
  if (locale && (strstr(locale, "en_US") != nullptr || strstr(locale, "en_GB") != nullptr || strstr(locale, "en_CA") != nullptr)) {
    result = true; // The OS is English
  }
#else
  // Other platforms
  // Code to handle other platforms can be added here.
  // 他のプラットフォームのためのコードはここに追加することができます。
#endif // _WIN32, __linux__, or other platforms
  return result;
}

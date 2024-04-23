#include <stdio.h>
#include "marLocale.h"

int main()
{
  // アプリケーション起動時の言語を決定します。
  // ここでは、OSの言語が日本語なら日本語をそれ以外なら英語を表示しています。

  // Determines the language at application startup.
  // Here, if the OS language is Japanese, Japanese is displayed; otherwise, English is displayed.

  if (isJapaneseOS()) {
    setLanguage("ja");
  } else {
    setLanguage("en");
  }
  // 
  printf("%s\n", translate("Hello World").c_str());
  printf("%s\n", translate("Goodbye").c_str());

  // Spanish
  setLanguage("es");
  printf("%s\n", translate("Hello World").c_str());
  printf("%s\n", translate("Goodbye").c_str());

  // Japanese
  setLanguage("ja");
  printf("%s\n", translate("Hello World").c_str());
  printf("%s\n", translate("Goodbye").c_str());

  // English
  setLanguage("en");
  printf("%s\n", translate("Hello World").c_str());
  printf("%s\n", translate("Goodbye").c_str());

  return 0;
}

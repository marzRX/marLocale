# Method for Determining the Language at Startup

For software with internationalization support, special attention must be paid to the selection of the default language (the language used at the first launch). Please consider the following methods:

1.    Follow the OS language settings: The software reads the OS settings and uses the same language as the default.
2.    Based on the developer's region: If the OS used is from the same country as the developer's locale, that language is used as the default. Otherwise, English is used.
3.    Use English as the default: English is set as the default language initially as it is the most widely understood language, catering to a broad range of users.

The method I frequently use is the second one, "Based on the developer's region." For example, if using a Japanese OS, I set Japanese as the default language; otherwise, I set English. Here is an example of how this is implemented in code:

```cpp
if (isJapaneseOS()) {
    setLanguage("ja");
} else {
    setLanguage("en");
}
```

This program is equipped with isJapaneseOS() and isEnglishOS(). If needed, consider adding functions such as isSpanishOS(), isFrenchOS(). Below is some reference information for adding these functions.

## Method for Determining Language in Windows

In Windows, the language of the OS is determined using LANGID. For example, 1041 represents Japanese, and 1033 represents English (United States). You can check the details for each language's LANGID at the following link:

-    [Language Identifier Constants and Strings](https://winprotocoldoc.blob.core.windows.net/productionwindowsarchives/MS-LCID/%5bMS-LCID%5d-210407.pdf)

## Method for Determining Language in Linux

In Linux, the language of the OS is determined using POSIX locales. Locale strings are represented in formats such as ja_JP and en_US, which indicate the language and region. This allows for the proper setting of the language environment.

The previously mentioned PDF also includes information about locale strings.
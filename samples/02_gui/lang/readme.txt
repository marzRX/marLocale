Customize <Your Software Name>'s Language

To personalize <Your Software Name>''s interface, you can modify the language strings to suit your preferences or language. Simply edit the 'lang/translations_user_custom.json' file.

Snippet of JSON entry:
{
  "Help": "Help",
  "About": "About",
  "Scale Viewer": "Scale Viewer",
  // More strings follow...
}

Each entry in the JSON file is a pair of "Key": "Value". You can change the "Value" part to your desired text, which is the displayed language string within the application. For example:

{
  "Help": "Ayuda",
  "About": "Acerca de",
  // Continue translating other strings...
}

Important Guidelines:

    Do not modify the "Key" part of each pair, as <Your Software Name> uses this to identify the text to be replaced.
    Ensure your translations_user_custom.json file is saved with UTF-8 encoding to support special characters and Unicode symbols.
    After editing and saving your custom language file, select [File | Language | User Custom] from the application menu to apply your changes.
    No trailing commas: Ensure there isn't a comma after the last entry. Correctly close the JSON object with a }.

Correct:
  "Back": "Back",
  "Font Size": "Font Size"
}

Incorrect (note the trailing comma):
  "Back": "Back",
  "Font Size": "Font Size",
}

By following these steps, you can enjoy <Your Software Name> with the language settings of your choice. If your JSON has some issues, <Your Software Name> will notify you with a red error message in the status bar. 

Happy customizing!

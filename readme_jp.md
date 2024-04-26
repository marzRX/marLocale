# marLocale モジュール
##概要

このモジュールは、C++アプリケーションの国際化をサポートするために設計されました。言語設定ファイルがJSON形式であるため、ユーザーは自身の環境でJSONファイルを編集するだけで簡単にローカライズすることが可能です。

## 使い方

簡単なサンプルが用意されていますので、それらを参照することをお勧めします。サンプルはWindowsおよびLinuxで動作します。

```cpp
#include <stdio.h>
#include "marLocale.h"

int main()
{
  setLanguage("es");
  printf("%s\n", translate("Hello World").c_str());
  return 0;
}
```

### JSON ファイルの例
以下はスペイン語の翻訳ファイルの例です。実際のファイルは lang/translations_es.json に保存します。
```json
{
  "Hello World": "Hola mundo",
  "Goodbye": "Adiós"
}
```

## サンプルプログラム

-    01_commandline: 国際化対応を行うための非常にシンプルなコマンドラインプログラムです。
-    02_gui: ImGuiを使用したGUIプログラムです。OpenGLを使用していますが、GUI要素の翻訳に焦点を当てたコードになっているので理解しやすいと思います。

### サンプルプログラムのビルド
Windows/Linux ともにmakefile を実行するだけです。
```bash
make
```

## 必要条件

#### nlohmann/json
このプロジェクトはJSON処理のために **nlohmann/json** ライブラリに依存しています。以下は、異なるオペレーティングシステムでのセットアップ方法です。
##### Windows (MSYS2使用):

MSYS2内でpacmanを使用して nlohmann/json ライブラリを簡単にインストールできます。

```bash
pacman -S mingw-w64-x86_64-nlohmann-json
```
##### Linux Mint (Ubuntu):

Linux Mintでは、GitHubのリリースページから直接ライブラリをダウンロードし、手動でインストールすることができます。

```bash
sudo mkdir -p /usr/include/nlohmann
sudo wget https://github.com/nlohmann/json/releases/download/v3.10.5/json.hpp -O /usr/include/nlohmann/json.hpp
```

#### GLFW と GLEW

marLocale には GLFW と GLEW は必要ありませんが、サンプル アプリケーション 02_gui を実行するには必要です。

##### Windows (using MSYS2):

```bash
pacman -Syu
pacman -S mingw-w64-x86_64-glfw
pacman -S mingw-w64-x86_64-glew
```

##### Linux Mint (Ubuntu):

```bash
sudo apt update
sudo apt install -y libglfw3 libglfw3-dev
sudo apt install -y libglew-dev
```
## ライセンス

このプロジェクトは[MITライセンス](LICENSE.txt)の下で公開されています。
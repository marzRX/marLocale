#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "marLocale.h"

// Japanese font (日本語のフォント)
const char* FONT_SRC_JAPANESE = "../mplus-1p-medium.ttf";

// Arabic font (アラビア語のフォント)
const char* FONT_SRC_ARABIC = "../NotoSansArabic-Regular.ttf";

// Arabic glyph range (アラビア語の範囲)
static const ImWchar arabic_ranges[] = {
    0x0600, 0x06FF, // Arabic (アラビア語)
    0xFB50, 0xFDFF, // Arabic Presentation Forms-A (アラビア語表示形式A)
    0xFE70, 0xFEFF, // Arabic Presentation Forms-B (アラビア語表示形式B)
    0
};

// Hindi font (ヒンディー語のフォント)
const char* FONT_SRC_DEVANAGARI = "../NotoSansDevanagari-Regular.ttf";

// Devanagari glyph ranges (デヴァナガリの範囲)
static const ImWchar devanagari_ranges[] = {
    0x0900, 0x097F, // Devanagari (デヴァナガリ)
    0xA8E0, 0xA8FF, // Devanagari Extended (デヴァナガリ拡張)
    0
};

int running;

// Function prototype declaration for OpenGL cleanup.
// OpenGLのクリーンアップのための関数プロトタイプ宣言。
void quit_opengl();

ImVec4 clear_color = ImVec4(0.65, 0.87, 0.65, 1.0);

int gLanguage = 0; // 0: English, 1: Japanese, 2: Spanish, ...
int g_locale_result = 0;

// Drawing operation (描画処理)
void paintGL()
{
  // Clear the screen with the specified background color.
  // glClear() で指定した背景色で画面をクリアする。
  glClear(GL_COLOR_BUFFER_BIT);
}

// Window size change callback.
void window_size_callback(GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, width, height);
}

// Character input callback.
void char_callback(GLFWwindow* window, unsigned int codepoint)
{
  switch(codepoint)
    {
    case 'q':
    case 'Q':
    case 27: // [Esc]
      running = GL_FALSE;
      break;

    default:
      break;
    }
}

// Sets up the layout for ImGui components to be rendered by ImGui::Render().
// ImGui::Render()によってレンダリングされるImGuiコンポーネントのレイアウトを設定します。
void setupImGuiLayout()
{
  // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
  {
    static float f = 0.0f;
    static int counter = 0;

    std::string window_title;
    window_title = translate("Hello, world!") + "###Hello";
    printf("%s\n", window_title.c_str());

    ImGui::Begin(window_title.c_str());                          // Create a window called "Hello, world!" and append into it.

    ImGui::Text(translate("This is some useful text.").c_str());               // Display some text (you can use a format strings too)

    ImGui::SliderFloat(translate("float").c_str(), &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
    ImGui::ColorEdit3(translate("clear color").c_str(), (float*)&clear_color); // Edit 3 floats representing a color
    glClearColor(clear_color.x, clear_color.y, clear_color.z, 1.0);

    if (ImGui::Button(translate("Button").c_str()))                            // Buttons return true when clicked (most widgets return true when edited/activated)
      counter++;
    ImGui::SameLine();
    ImGui::Text("%s = %d", translate("counter").c_str(), counter);

    // Select and change language using radio buttons.
    // ラジオボタンを使用して言語を選択し、変更します。
    if (ImGui::RadioButton(translate("English").c_str(), &gLanguage, 0)) {
      g_locale_result = setLanguage("en");
      printf("Selected English\n");
    }
    if (ImGui::RadioButton(translate("Japanese").c_str(), &gLanguage, 1)) {
      g_locale_result = setLanguage("ja");
      printf("Selected Japanese\n");
    }
    if (ImGui::RadioButton(translate("Spanish").c_str(), &gLanguage, 2)) {
      g_locale_result = setLanguage("es");
      printf("Selected Spanish\n");
    }
    if (ImGui::RadioButton(translate("French").c_str(), &gLanguage, 3)) {
      g_locale_result = setLanguage("fr");
      printf("Selected French\n");
    }
    if (ImGui::RadioButton(translate("German").c_str(), &gLanguage, 4)) {
      g_locale_result = setLanguage("de");
      printf("Selected German\n");
    }
    if (ImGui::RadioButton(translate("Portugues").c_str(), &gLanguage, 5)) {
      g_locale_result = setLanguage("pt");
      printf("Selected Portugues\n");
    }
    if (ImGui::RadioButton(translate("Arabic").c_str(), &gLanguage, 6)) {
      g_locale_result = setLanguage("ar");
      printf("Selected Arabic\n");
    }
    // Handle selection for Custom User.
    // カスタムユーザー選択時の処理。
    if (ImGui::RadioButton(translate("Custom User").c_str(), &gLanguage, 7)) {
      g_locale_result = setLanguage("custom_user");
      printf("Selected Custom User\n");
    }

    std::string locale_message;
    if (g_locale_result==JSON_ParseError) {
      locale_message = "Failed to parse the JSON file. Please check the file for formatting errors.";
    } else if (g_locale_result == JSON_FileNotFound) {
      locale_message = "The JSON file for translations could not be found. Please ensure the file exists in the correct location.";
    } else {
      // No message is displayed if everything is normal.
      // 正常時特にメッセージは表示しない。
      locale_message = ""; 
    }
    ImGui::Text(locale_message.c_str());

    ImGui::Text("%s %.3f ms/frame (%.1f FPS)",
		translate("Application average").c_str(), 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();
  }
}
  
int main()
{
  if (! glfwInit() ) {
    fprintf(stderr, "ERROR: could not start GLFW3\n");
    return 1;
  }

  // Decide GL+GLSL versions
  const char* glsl_version = "#version 430";
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

  GLFWwindow* window = glfwCreateWindow(640, 640, "OpenGL sample", NULL, NULL);
  if (! window) {
    fprintf(stderr, "ERROR: could not open window with GLFW3\n");
    glfwTerminate();
    return 1;
  }
  glfwMakeContextCurrent(window);

#ifdef GPUINFO
  printf("OpenGL Vendor  = %s\n", glGetString(GL_VENDOR));
  printf("OpenGL GPU     = %s\n", glGetString(GL_RENDERER));
  printf("OpenGL Version = %s\n", glGetString(GL_VERSION));
  printf("GLSL   Version = %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
#endif

  // GLEW initialization is commented out because OpenGL extensions are not used in this program.
  // 今回はOpenGL拡張を使用していないので、GLEWの初期化処理をコメントアウトしています。
  /*
  // Enable OpenGL extensions.
  // OpenGL 拡張機能を使えるようにする。
  glewExperimental = GL_TRUE;
  GLenum err = glewInit();
  if (err != GLEW_OK) {
    fprintf(stderr, "Error: '%s'\n", glewGetErrorString(err));
    return 1;
  }
  */

  // Specify the background color.
  // 背景色を指定する。
  glClearColor(clear_color.x, clear_color.y, clear_color.z, 1.0);

  if (isJapaneseOS()) {
    setLanguage("ja");
  } else {
    setLanguage("en");
  }

  // Register callbacks. (コールバックを登録します。)
  glfwSetWindowSizeCallback(window, window_size_callback);
  glfwSetCharCallback(window, char_callback);

  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO(); (void)io;

  // Setup Dear ImGui style
  ImGui::StyleColorsDark();
  //  ImGui::StyleColorsLight();

  // Setup Platform/Renderer bindings
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init(glsl_version);

  //----------------------------------------------------------------------
  float text_fontsize = 20.0f; // font size (フォントサイズ)
  ImFontConfig icons_config;

  // Prevent ImGui from freeing font data.
  // ImGuiがフォントデータを解放しないようにする。
  icons_config.FontDataOwnedByAtlas = false;

  // Load Japanese characters from .ttf font file for use in ImGui.
  // .ttfファイルから日本語の文字を読み込み、ImGuiで使用します。
  io.Fonts->AddFontFromFileTTF(FONT_SRC_JAPANESE, text_fontsize, NULL, io.Fonts->GetGlyphRangesJapanese());

  icons_config.MergeMode = true;
  icons_config.PixelSnapH = true;

  io.Fonts->AddFontFromFileTTF(FONT_SRC_ARABIC, text_fontsize, &icons_config, arabic_ranges);
  io.Fonts->AddFontFromFileTTF(FONT_SRC_DEVANAGARI, text_fontsize, &icons_config, devanagari_ranges);
  //----------------------------------------------------------------------

  running = GL_TRUE;
  while ( running && (! glfwWindowShouldClose(window)) ) {
    // Poll and handle events (inputs, window resize, etc.)
    glfwPollEvents();

    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    setupImGuiLayout();

    // Rendering
    ImGui::Render();

    paintGL();

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // Exit on ESC key press. (ESCキーでプログラムを終了する。)
    running = !glfwGetKey(window, GLFW_KEY_ESCAPE);

    glfwSwapBuffers(window);
  }

  // Cleanup
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
  
  quit_opengl();
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}

// Cleanup operations. (終了処理)
void quit_opengl()
{
}

REPO_ROOT := $(shell git rev-parse --show-cdup)
# REPO_ROOT's trailing '/', gets the path to the Git root
# REPO_ROOT の終端は、'/', Git のルートとなるパスを取得してる

CXXFLAGS = -g -std=gnu++17 -Wno-format-security

CXX = g++
DIR_SRC = $(REPO_ROOT)src
DIR_IMGUI = $(REPO_ROOT)External/imgui
INC = -I$(DIR_SRC) -I$(DIR_IMGUI)
ifdef OS
  # Windows (msys2)
  LIBS = -lopengl32 -lglfw3 -lglew32
else
  # Linux
  LIBS = -lGL -lglfw -lGLEW -ldl
endif

# prog*.cpp をメインモジュールとする
MAIN_SRC := $(wildcard prog*.cpp)
TARGET_BASE := $(basename $(MAIN_SRC))

TARGET = $(TARGET_BASE).exe
OBJS = $(TARGET_BASE).o marLocale.o \
imgui.o imgui_widgets.o imgui_draw.o imgui_impl_glfw.o imgui_impl_opengl3.o imgui_tables.o

.PHONY: all clean run
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(INC) -o $(TARGET) $(OBJS) $(LIBS)

marLocale.o: $(DIR_SRC)/marLocale.cpp $(DIR_SRC)/marLocale.h
	$(CXX) $(INC) $(CXXFLAGS) -c $< -o $@

imgui.o: $(DIR_IMGUI)/imgui.cpp
	$(CXX) $(INC) $(CXXFLAGS) -c $< -o $@

imgui_widgets.o: $(DIR_IMGUI)/imgui_widgets.cpp
	$(CXX) $(INC) $(CXXFLAGS) -c $< -o $@

imgui_draw.o: $(DIR_IMGUI)/imgui_draw.cpp
	$(CXX) $(INC) $(CXXFLAGS) -c $< -o $@

imgui_impl_glfw.o: $(DIR_IMGUI)/imgui_impl_glfw.cpp
	$(CXX) $(INC) $(CXXFLAGS) -c $< -o $@

imgui_impl_opengl3.o: $(DIR_IMGUI)/imgui_impl_opengl3.cpp
	$(CXX) $(INC) $(CXXFLAGS) -c $< -o $@

imgui_tables.o: $(DIR_IMGUI)/imgui_tables.cpp
	$(CXX) $(INC) $(CXXFLAGS) -c $< -o $@

$(TARGET_BASE).o: $(TARGET_BASE).cpp
	$(CXX) $(INC) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

##
# $@ ... target_name
# $* ... strip_extension(target_name)
# $< ... The first dependency file; however, this is not available in Borland make
# $< ... 最初の依存ファイル ただし borland make には存在せず

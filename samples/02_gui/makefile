CURROOT = $(shell git rev-parse --show-cdup)
# CURROOT's trailing '/', gets the path to the Git root
# CURROOT の終端は、'/', Git のルートとなるパスを取得してる

CFLAGS = -c -g -std=gnu++17 -Wno-format-security

CC = g++
DIR_SRC = $(CURROOT)src
DIR_IMGUI = $(CURROOT)External/imgui
INC = -I$(DIR_SRC) -I$(DIR_IMGUI)
ifdef OS
  # Windows (msys2)
  LIBS = -lopengl32 -lglfw3 -lglew32
else
  # Linux
  LIBS = -lGL -lglfw -lGLEW -ldl
endif

V ?= 2
TARGET = prog$(V).exe
OBJS = prog$(V).o marLocale.o \
imgui.o imgui_widgets.o imgui_draw.o imgui_impl_glfw.o imgui_impl_opengl3.o imgui_tables.o

$(TARGET): $(OBJS)
	$(CC) $(INC) -o $(TARGET) $(OBJS) $(LIBS)

marLocale.o: $(DIR_SRC)/marLocale.cpp $(DIR_SRC)/marLocale.h
	$(CC) $(INC) $(CFLAGS) $(DIR_SRC)/marLocale.cpp

imgui.o: $(DIR_IMGUI)/imgui.cpp
	$(CC) $(INC) $(CFLAGS) $(DIR_IMGUI)/imgui.cpp

imgui_widgets.o: $(DIR_IMGUI)/imgui_widgets.cpp
	$(CC) $(INC) $(CFLAGS) $(DIR_IMGUI)/imgui_widgets.cpp

imgui_draw.o: $(DIR_IMGUI)/imgui_draw.cpp
	$(CC) $(INC) $(CFLAGS) $(DIR_IMGUI)/imgui_draw.cpp

imgui_impl_glfw.o: $(DIR_IMGUI)/imgui_impl_glfw.cpp
	$(CC) $(INC) $(CFLAGS) $(DIR_IMGUI)/imgui_impl_glfw.cpp

imgui_impl_opengl3.o: $(DIR_IMGUI)/imgui_impl_opengl3.cpp
	$(CC) $(INC) $(CFLAGS) $(DIR_IMGUI)/imgui_impl_opengl3.cpp

imgui_tables.o: $(DIR_IMGUI)/imgui_tables.cpp
	$(CC) $(INC) $(CFLAGS) $(DIR_IMGUI)/imgui_tables.cpp

prog$(V).o: prog$(V).cpp
	$(CC) $(INC) $(CFLAGS) prog$(V).cpp

all: $(TARGET)

clean:
	-rm -f *.o
	-rm -f $(TARGET)

##
# $@ ... target_name
# $* ... strip_extension(target_name)
# $< ... The first dependency file; however, this is not available in Borland make
# $< ... 最初の依存ファイル ただし borland make には存在せず

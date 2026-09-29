CXX = g++
DIR_SRC = ../../src
INC = -I$(DIR_SRC)

# prog*.cpp をメインモジュールとする
MAIN_SRC := $(wildcard prog*.cpp)
TARGET_BASE := $(basename $(MAIN_SRC))

TARGET = $(TARGET_BASE).exe
OBJS = $(TARGET_BASE).o marLocale.o
CXXFLAGS = -g

.PHONY: all clean run
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(INC) -o $(TARGET) $(OBJS) $(LIBS)

$(TARGET_BASE).o: $(TARGET_BASE).cpp
	$(CXX) $(INC) $(CXXFLAGS) -c $< -o $@

marLocale.o: $(DIR_SRC)/marLocale.cpp $(DIR_SRC)/marLocale.h
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

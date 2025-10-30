CXX = g++
DIR_SRC = ../../src
INC = -I$(DIR_SRC)

V ?= 1
TARGET = prog$(V).exe
OBJS = prog$(V).o marLocale.o
CXXFLAGS = -c -g

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(INC) -o $(TARGET) $(OBJS) $(LIBS)

prog$(V).o: prog$(V).cpp
	$(CXX) $(INC) $(CXXFLAGS) prog$(V).cpp

marLocale.o: $(DIR_SRC)/marLocale.cpp $(DIR_SRC)/marLocale.h
	$(CXX) $(INC) $(CXXFLAGS) $(DIR_SRC)/marLocale.cpp

clean:
	-rm -f *.o
	-rm -f $(TARGET)

##
# $@ ... target_name
# $* ... strip_extension(target_name)
# $< ... The first dependency file; however, this is not available in Borland make
# $< ... 最初の依存ファイル ただし borland make には存在せず

CXX?=clang++
EXE=analyzer
CXXDEBUG= -g -Wall
CXXSTD=-std=c++14
CXXFLAGS= -Wno-deprecated-register -O0 $(CXXDEBUG) $(CXXSTD)
CPPOBJ= main Parser Lexer
FILES= $(addsuffix .cpp, $(CPPOBJ))
OBJS = $(addsuffix .o, $(CPPOBJ))
CLEANLIST = $(OBJS) $(EXE) Lexer.cpp

.PHONY: all
all: build

build: Lexer.cpp $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXE) $(OBJS)

Lexer.cpp: lexer.ll
	flex++ lexer.ll

.PHONY: clean
clean:
	rm -rf $(CLEANLIST)

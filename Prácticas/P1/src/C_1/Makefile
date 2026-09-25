CXX = g++
CXXFLAGS = -Wall -std=c++11
FLEX = flex++

TARGET = compiler
OBJS = Lexer.o main.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

Lexer.cpp: lexer.ll Lexer.hpp tokens.hpp
	$(FLEX) lexer.ll

Lexer.o: Lexer.cpp Lexer.hpp tokens.hpp
	$(CXX) $(CXXFLAGS) -c Lexer.cpp

main.o: main.cpp Lexer.hpp tokens.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

run: $(TARGET)
	./$(TARGET) prueba

clean:
	rm -f $(TARGET) $(OBJS) Lexer.cpp

.PHONY: all run clean


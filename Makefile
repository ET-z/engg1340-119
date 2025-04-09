CXX = g++  
FLAGS = -Wall -pedantic-errors -std=c++11 
ENGFLAG = -lncurses 

SRCS = main.cpp game.cpp tutorial1.cpp tutorial2.cpp tutorial3.cpp 
OBJS = $(SRCS:.cpp=.o) 

TARGET = main
ARCHIVE = main.tgz

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(FLAGS) $^ -o $@ $(ENGFLAG)

%.o: %.cpp game.h 
	$(CXX) $(FLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJS) $(ARCHIVE) # Remove target, all objects, and archive

tar:
	tar -czvf $(ARCHIVE) $(SRCS) *.h Makefile # Archive sources, headers, and Makefile

# Declare phony targets
.PHONY: all run clean tar
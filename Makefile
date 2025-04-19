CXX = g++
FLAGS = -Wall -pedantic-errors -std=c++11
ENGFLAG = -lncurses

# Add all relevant .cpp files here
SRCS = main.cpp \
        game.cpp \
        draw_characters.cpp \
        pause.cpp \
        tutorial_pages/tutorial1.cpp \
        tutorial_pages/tutorial2.cpp \
        tutorial_pages/tutorial3.cpp \
	draw_healthbar.cpp
 
OBJS = $(SRCS:.cpp=.o)
 
TARGET = main
ARCHIVE = main.tgz
 
all: $(TARGET)
 
$(TARGET): $(OBJS)
        $(CXX) $(FLAGS) $^ -o $@ $(ENGFLAG)
%.o: %.cpp 25         
	$(CXX) $(FLAGS) -c $< -o $@
run: $(TARGET)
        ./$(TARGET)
clean:
        rm -f $(TARGET) $(OBJS) $(ARCHIVE)
 
tar:
	tar -czvf $(ARCHIVE) $(SRCS) *.h Makefile
 
.PHONY: all run clean tar

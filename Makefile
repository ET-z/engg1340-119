CXX = g++
FLAGS = -Wall -pedantic-errors -std=c++11
ENGFLAG = -lncursesw

# Add all relevant .cpp files here
SRCS = main.cpp \
        game.cpp \
        draw_characters.cpp \
        pause.cpp \
        tutorial_pages/tutorial1.cpp \
        tutorial_pages/tutorial2.cpp \
        tutorial_pages/tutorial3.cpp \
				draw_healthbar.cpp \
				dealerAI.cpp \
				draw_item.cpp \
				random_items.cpp \
				dealer_use_items.cpp
 
OBJS = $(SRCS:.cpp=.o)
 
TARGET = main
ARCHIVE = main.tgz
 
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(FLAGS) $^ -o $@ $(ENGFLAG)

%.o: %.cpp
	$(CXX) $(FLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJS) $(ARCHIVE)

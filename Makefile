CXX = clang++
CXXFLAGS = -Wall -g -std=c++11 -lncurses
SRC_DIR = src
INCLUDE_DIR = include

TARGET = autocomplete
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp,%.o,$(SRCS))
INCLUDES = -I$(INCLUDE_DIR)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^

%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)

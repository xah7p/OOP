CXX      := g++
CXXFLAGS := -std=c++23 -Wall -Wextra -Wpedantic -Werror -O2

INCLUDES := -ISet -IException -IIterator -IConcepts

TARGET := app.exe
OUT    := out

SRCS := main.cpp

OBJS := $(SRCS:%.cpp=$(OUT)/%.o)

.PHONY: all clean run

all: $(OUT) $(TARGET)

$(OUT):
	mkdir -p $(OUT)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(OUT)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(OUT) $(TARGET) *.o

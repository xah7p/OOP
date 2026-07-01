CPP := clang++

CPPFLAGS := -std=c++20 -O3 -Iinc -fsanitize=address,undefined -Wall -Werror

SRC_PATH := src
OUT_PATH := out

SRCS := $(wildcard $(SRC_PATH)/*.cpp)
OBJS := $(SRCS:$(SRC_PATH)/%.cpp=$(OUT_PATH)/%.o)

app.exe: $(OBJS)
	$(CPP) $(CPPFLAGS) -o $@ $^ -lSDL2

$(OUT_PATH)/%.o: $(SRC_PATH)/%.cpp | $(OUT_PATH)
	$(CPP) $(CPPFLAGS) -c $< -o $@

$(OUT_PATH):
	mkdir -p $@

.PHONY: clean
clean:
	rm -rf $(OUT_PATH) *.exe

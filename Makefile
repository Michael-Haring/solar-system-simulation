CXX = g++
CXXFLAGS = -g3 -Wall -Wextra -std=c++17 -Iinclude -Wunreachable-code -Wno-unused-parameter \
		 -Wredundant-decls -Wno-unused-variable -Wshadow

SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build

SRCS_CPP = $(wildcard $(SRC_DIR)/*.cpp) 
SRCS_C = $(wildcard $(SRC_DIR)/*.c) 

OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS_CPP)) \
	$(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS_C))

TARGET = $(BUILD_DIR)/simulation

LIBS = -lglfw -lGL -ldl -lm

all: $(TARGET)

$(TARGET): $(OBJS) | $(BUILD_DIR)
	$(CXX) $(OBJS) -o $@ $(LIBS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)/*.o $(TARGET)

.PHONY: all clean

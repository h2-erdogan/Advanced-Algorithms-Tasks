# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall

# Paths
SRC_DIR = src
BUILD_DIR = build
LIB_DIR = /opt/homebrew/lib
POCO_DIR = /opt/homebrew

# Include and library paths for POCO
INCLUDES = -I$(POCO_DIR)/include -Isrc -Isrc/web
LIBS = -L$(LIB_DIR) -lPocoNet -lPocoUtil -lPocoFoundation -lPocoJSON -ljsoncpp -lpthread
LDFLAGS = -Wl,-rpath,$(LIB_DIR)

# Target executables
SERVER_TARGET = ebikeGateway
CLIENT_TARGET = ebikeClient
GENERATOR_TARGET = generateEBikeFile

# Source files
SERVER_SRCS = $(wildcard $(SRC_DIR)/ebikeGateway.cpp) $(wildcard $(SRC_DIR)/web/*.cpp)
CLIENT_SRCS = $(wildcard $(SRC_DIR)/ebikeClient.cpp)
GENERATOR_SRCS = $(wildcard $(SRC_DIR)/util/generateEBikeFile.cpp)

# Object files
SERVER_OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SERVER_SRCS))
CLIENT_OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(CLIENT_SRCS))
GENERATOR_OBJS = $(patsubst $(SRC_DIR)/util/%.cpp, $(BUILD_DIR)/util/%.o, $(GENERATOR_SRCS))

# Build rules
all: $(BUILD_DIR) $(SERVER_TARGET) $(CLIENT_TARGET) $(GENERATOR_TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)
	mkdir -p $(BUILD_DIR)/web
	mkdir -p $(BUILD_DIR)/util

$(SERVER_TARGET): $(SERVER_OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^ $(LIBS) $(LDFLAGS)

$(CLIENT_TARGET): $(CLIENT_OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^ -L$(LIB_DIR) -ljsoncpp -Wl,-rpath,$(LIB_DIR)

$(GENERATOR_TARGET): $(GENERATOR_OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/web/%.o: $(SRC_DIR)/web/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/util/%.o: $(SRC_DIR)/util/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Clean up build files
clean:
	rm -rf $(BUILD_DIR) $(CLIENT_TARGET) $(SERVER_TARGET) $(GENERATOR_TARGET)

SRC_DIR = src
OBJ_DIR = .obj
EXEC = game.exe

SFML_DIR = D:/res/libraries/SFML-3.1.0
INC_DIR = $(SFML_DIR)/include
LIB_DIR = $(SFML_DIR)/lib

CXX = g++
CXXFLAGS = -g -Wall -std=c++17 -I$(INC_DIR)

LDFLAGS = -L$(LIB_DIR)
LDLIBS = -lmingw32 -lsfml-main -lsfml-graphics -lsfml-window -lsfml-system -mwindows

SOURCES = $(wildcard $(SRC_DIR)/*.cpp) \
          $(wildcard $(SRC_DIR)/*/*.cpp) \
          $(wildcard $(SRC_DIR)/*/*/*.cpp)

OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))

run: $(EXEC)
	./$(EXEC)

check:
	@$(CXX) -fsyntax-only $(CXXFLAGS) $(SOURCES)

$(EXEC): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(EXEC) $(LDFLAGS) $(LDLIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@if not exist "$(subst /,\,$(@D))" mkdir "$(subst /,\,$(@D))"
	$(CXX) -c $(CXXFLAGS) $< -o $@

clean:
	@if exist $(EXEC) del $(EXEC)
	@if exist $(OBJ_DIR) rmdir /S /Q $(OBJ_DIR)

.PHONY: run clean check
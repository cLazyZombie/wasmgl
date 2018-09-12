CC = emcc
CFLAGS = -O3 -std=c++14 -s USE_SDL=2 -s WASM=1
SRC = src
DIST = bin
TMP = intermediate
TARGET = $(DIST)/wasmgl.js
SOURCES = $(wildcard $(SRC)/*.cpp $(SRC)/*.c)
OBJECTS = $(patsubst $(SRC)/%.cpp, $(TMP)/%.o, $(SOURCES))

$(TARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET)

$(OBJECTS) : $(TMP)/%.o : $(SRC)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(TMP) : 
	mkdir -p $@

clean :
	rm -rf $(OBJECTS)

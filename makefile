CC = emcc
CFLAGS = -O3
SRC = src
DIST = bin
TMP = intermediate
TARGET = $(DIST)/wasmgl.html

$(TARGET) : $(TMP)/main.o
	$(CC) $(CFLAGS) $(TMP)/main.o -s WASM=1 -o $(TARGET) 

$(TMP)/main.o : $(SRC)/main.cpp
	$(CC) $(CFLAGS) $(SRC)/main.cpp -o $(TMP)/main.o


$(TMP) : 
	mkdir -p $@


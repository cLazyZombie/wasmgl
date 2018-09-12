CC = emcc
CFLAGS = -O3 -std=c++14 -s USE_SDL=2 -s USE_WEBGL2=1
LDFLAGS = -s WASM=1
SRC = src
DIST = bin
TMP = intermediate
TARGET = $(DIST)/wasmgl.js
SOURCES = $(wildcard $(SRC)/*.cpp) $(wildcard $(SRC)/*.c)
OBJECTS = $(patsubst $(SRC)/%.cpp, $(TMP)/%.o, $(SOURCES))
DEP = $(OBJECTS:.o=.d)  # one dependency file for each source

$(TARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJECTS) -o $(TARGET)

-include $(DEP) 
%.d : %.cpp %.c
	 @$(CC) $(CFLAGS) $< -MM -MT $(@:.d=.o) >$@

$(OBJECTS) : $(TMP)/%.o : $(SRC)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(TMP) : 
	mkdir -p $@

.PHONY: clean
clean :
	rm -rf $(OBJECTS)
	rm -rf $(DEP)

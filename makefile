CC = emcc
CFLAGS = -O3 -std=c++14 -s USE_SDL=2 -s USE_WEBGL2=1 -I./src/thirdparty -I./src
LDFLAGS = -s WASM=1
SRC = src
DIST = bin
TMP = intermediate
TARGET = $(DIST)/wasmgl.js

SOURCES = $(shell find ./src -name "*.cpp")
OBJECTS = $(patsubst ./src/%.cpp, ./intermediate/%.o, $(SOURCES))
TMPDIRS = $(foreach f, $(OBJECTS), $(dir $(f)))

DEP = $(OBJECTS:.o=.d)  # one dependency file for each source

$(TARGET) : $(OBJECTS) stdafx.h.gch $(CreateTmpDirs)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJECTS) -o $(TARGET)

stdafx.h.gch : src/stdafx.h
	$(CC) $(CFLAGS) -x c++-header src/stdafx.h -o stdafx.h.gch

$(TMPDIRS) : 
	mkdir -p $(TMPDIRS)

-include $(DEP) 
%.d : %.cpp %.c
	 @$(CC) $(CFLAGS) $< -MM -MT $(@:.d=.o) >$@

$(OBJECTS) : $(TMP)/%.o : $(SRC)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

#$(TMP) : 
#	mkdir -p $@

.PHONY: print
print :
	@echo $(TMPDIRS)

.PHONY: clean
clean :
	echo $(SOURCES)
	rm -rf $(OBJECTS)
	rm -rf $(DEP)
	rm -rf stdafx.h.gch

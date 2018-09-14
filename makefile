CC = emcc
CFLAGS = -std=c++14 -stdlib=libc++ -s USE_SDL=2 -s USE_WEBGL2=1 -I./src/Thirdparty -I./src/VoxerEngine -I./src
LDFLAGS = -s WASM=1
SRC = src
DIST = bin
TMP = intermediate
TARGET = $(DIST)/wasmgl.js
#DBG_FLAGS = -O3

ifeq ($(RELEASE), 1)
DBG_FLAGS = -O3
else
DBG_FLAGS = -O1 -s ASSERTIONS=1 -DDEBUG 
endif

SOURCES = $(shell find ./src -name "*.cpp")
OBJECTS = $(patsubst ./src/%.cpp, ./intermediate/%.o, $(SOURCES))
TMPDIRS = $(sort $(foreach f, $(OBJECTS), $(dir $(f))))

DEP = $(OBJECTS:.o=.d)  # one dependency file for each source

$(TARGET) : $(TMPDIRS) stdafx.h.gch $(OBJECTS) 
	$(CC) $(CFLAGS) $(DBG_FLAGS) $(LDFLAGS) $(OBJECTS) -o $(TARGET)

stdafx.h.gch : src/stdafx.h
	$(CC) $(CFLAGS) $(DBG_FLAGS) -x c++-header src/stdafx.h -o stdafx.h.gch

$(TMPDIRS) : 
	mkdir -p $(TMPDIRS)

-include $(DEP) 
%.d : %.cpp %.c
	 @$(CC) $(CFLAGS) $(DBG_FLAGS) $< -MM -MT $(@:.d=.o) >$@

$(OBJECTS) : $(TMP)/%.o : $(SRC)/%.cpp
	$(CC) $(CFLAGS) $(DBG_FLAGS) -c $< -o $@

#$(TMP) : 
#	mkdir -p $@

.PHONY: print
print :
	@echo $(TMPDIRS)

.PHONY: clean
clean :
	rm -rf $(OBJECTS)
	rm -rf $(DEP)
	rm -rf stdafx.h.gch

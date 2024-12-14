CXXFLAGS=-std=c++11 -c -g -Wall
CXXFLAGS+=$(shell pkg-config --cflags gtkmm-2.4)
LDLIBS=$(shell pkg-config --libs gtkmm-2.4)

ifeq ($(DEBUG),1)
CXXFLAGS+=-g
endif

OBJ:=win.o main.o
EXE=touchme

COMPILE.1=$(CXX) $(CXXFLAGS) -o $@ $<
ifeq ($(VERBOSE),)
COMPILE=@printf "  > compiling %s\n" $(<F) && $(COMPILE.1)
else
COMPILE=$(COMPILE.1)
endif

%.o: %.cpp
	$(COMPILE)

.PHONY: all clean rebuild

all: $(EXE)

$(EXE): $(OBJ) $(OUTPUT_DIR)
	$(CXX) -o $@ $(OBJ) $(LDLIBS)

clean:
	$(RM) $(EXE) $(OBJ)

rebuild: clean all

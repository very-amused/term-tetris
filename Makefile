O=-O2
CFLAGS = $(O) -Iinclude
LDFLAGS= -lncursesw -lsqlite3
CXXFLAGS = $(CFLAGS) -std=gnu++11
CXX=clang++

# Source and object files
src=$(shell find src/*.cpp) $(shell find src/widgets/*.cpp)
asm=src/schema.s
objects=$(src:.cpp=.o)

outdir=build
# Ensure outdir exists
$(shell if [ ! -d $(outdir) ]; then mkdir $(outdir); fi)

# Targets
tetris=$(outdir)/tetris

$(tetris): $(objects) $(asm)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o$@ $^

src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c -o$@ $<

clean:
	rm -f $(objects) $(asm) $(tetris)
.PHONY: clean

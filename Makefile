O=-O3
CFLAGS = $(O) -Wall
LDFLAGS=-lncursesw -lsqlite3
CXXFLAGS=$(CFLAGS) -std=gnu++11

# Prefer building with clang
ifneq (,$(shell which clang))
	override CXX=clang++
endif

# Source and object files
src=$(shell find src/ -name *.cpp)
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
	rm -f $(objects) $(tetris)
.PHONY: clean

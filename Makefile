O=-O2
CFLAGS = $(O) -Iinclude
LDFLAGS= -lncursesw
CXXFLAGS = $(CFLAGS) -std=gnu++11
CXX=clang++

# Source and object files
src=src/main.cpp src/ui.cpp src/main_menu.cpp $(shell find src/widgets/*.cpp)
objects=$(src:.cpp=.o)

outdir=build
# Ensure outdir exists
$(shell if [ ! -d $(outdir) ]; then mkdir $(outdir); fi)

# Targets
tetris=$(outdir)/tetris

$(tetris): $(objects)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o$@ $^

src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c -o$@ $<

clean:
	rm -f $(objects) $(tetris)
.PHONY: clean

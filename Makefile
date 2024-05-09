O=-O3
LTO=-flto
CFLAGS = $(O) $(LTO) -Wall
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

# Additional files we want to include in build/source archives
sql=$(shell find sql/ -name *.sql)
headers=$(shell find src/ -name *.hpp)
src-extra=Makefile README.md LICENSE $(sql) $(headers)

outdir=build
# Ensure outdir exists
$(shell if [ ! -d $(outdir) ]; then mkdir $(outdir); fi)

# Targets
tetris=$(outdir)/tetris
archive=$(outdir)/term-tetris.tar.gz

$(tetris): $(objects) $(asm)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o$@ $^

run: $(tetris)
	./$<
.PHONY: run

debug: O=-O1
debug: LTO=
debug: CFLAGS += -g -DDEBUG
debug: $(tetris)
	./$<
.PHONY: debug

# Thanks Maggie :)
debug-sanitize: O=-O1
debug: LTO=
debug-sanitize: CFLAGS  += -g -fsanitize=address -fno-omit-frame-pointer -DDEBUG
debug-sanitize: $(tetris)
	./$<
.PHONY: debug-sanitize

tar: $(archive)
.PHONY: tar

$(archive): $(src) $(asm) $(src-extra)
	tar czvf $@ $^

src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c -o$@ $<

clean:
	rm -f $(objects) $(tetris) $(archive); \
	rm -f $(shell find src/ -name *.o)
.PHONY: clean

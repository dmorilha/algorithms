CXXFLAGS += -O0
CXXFLAGS += -g
CXXFLAGS += -std=c++17

added-removed: added-removed.cc
	g++ ${CXXFLAGS} -o $@ $<;
	gdb -batch -ex r --args ./$@;

match-n: match-n.cc
	g++ ${CXXFLAGS} -o $@ $<;
	gdb -batch -ex r --args ./$@;

graph: graph.cc
	g++ ${CXXFLAGS} -o $@ $<;
	gdb -batch -ex r --args ./$@;

quick-sort: quick-sort.cc
	g++ ${CXXFLAGS} -o $@ $<;
	#gdb -batch -ex r --args ./$@;
	./$@ 2>/dev/null;

red-black-tree: red-black-tree.cc
	g++ ${CXXFLAGS} -o $@ $<;
	gdb -batch -ex r --args ./$@;

merge-sort: merge-sort.cc
	g++ ${CXXFLAGS} -o $@ $<;
	gdb -batch -ex r --args ./$@;

exponentiation: exponentiation.cc
	g++ ${CXXFLAGS} -o $@ $<;
	gdb -batch -ex r --args ./$@;

sieve-eratosthenes: sieve-eratosthenes.cc sieve-eratosthenes.h
	g++ ${CXXFLAGS} -o $@ $<;
	gdb -batch -ex r --args ./$@;

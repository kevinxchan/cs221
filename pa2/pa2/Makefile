# Settings
CXX := clang++
CXXFLAGS := -g -Wall -std=c++1y -stdlib=libc++

# Utility variables
OBJS := containertests interpretertest containertests.o interpretertest.o interpreter.o

# Utility targets
all: containertests interpretertest

clean:
	$(RM) $(OBJS)

# Binary targets
containertests: containertests.o
	$(CXX) $(CXXFLAGS) -g -o $@ $^

interpretertest: interpretertest.o interpreter.o
	$(CXX) $(CXXFLAGS) -g -o $@ $^

# Object targets
containertests.o: arrayclass.h stack.h queue.h

interpretertest.o: interpreter.h

interpreter.o: interpreter.h

# Dependency "targets"
arrayclass.h: arrayclassprivate.h arrayclass.cpp
	touch $@

stack.h: arrayclass.h stackprivate.h stack.cpp
	touch $@

queue.h: arrayclass.h queueprivate.h queue.cpp
	touch $@

interpreter.h: stack.h queue.h interpreterprivate.h interpertersecretfunctions.h
	touch $@

# Mark utility targets as phony
.PHONY: all clean
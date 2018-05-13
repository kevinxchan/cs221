EXENAME = tests
OBJS = tests.o linkedlist.o kebab.o grill.o 

CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lpthread -lm

all : $(EXENAME)

$(EXENAME) : $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

tests.o : tests.cpp catch.hpp linkedlist.h kebab.h grill.h
	$(CXX) $(CXXFLAGS) tests.cpp 

linkedlist.o : linkedlist.cpp kebab.h 
	$(CXX) $(CXXFLAGS) linkedlist.cpp

grill.o : grill.cpp linkedlist.h
	$(CXX) $(CXXFLAGS) grill.cpp

kebab.o : kebab.cpp 
	$(CXX) $(CXXFLAGS) kebab.cpp


clean :
	-rm -f *.o $(EXENAME)

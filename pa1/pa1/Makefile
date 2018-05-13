EXENAME = pa1
OBJS = main.o linkedlist.o kebab.o grill.o 

CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lpthread -lm

all : $(EXENAME)

$(EXENAME) : $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

main.o : main.cpp linkedlist.h kebab.h grill.h
	$(CXX) $(CXXFLAGS) main.cpp 

linkedlist.o : linkedlist.cpp kebab.h 
	$(CXX) $(CXXFLAGS) linkedlist.cpp

grill.o : grill.cpp linkedlist.h
	$(CXX) $(CXXFLAGS) grill.cpp

kebab.o : kebab.cpp 
	$(CXX) $(CXXFLAGS) kebab.cpp


test: basic.o PNG.o HSLAPixel.o lodepng.o lab_intro.o
	$(LD) basic.o PNG.o HSLAPixel.o lodepng.o lab_intro.o $(LDFLAGS) -o test

basic.o : tests/basic.cpp tests/catch.hpp
	$(CXX) $(CXXFLAGS) tests/basic.cpp


clean :
	-rm -f *.o $(EXENAME) test

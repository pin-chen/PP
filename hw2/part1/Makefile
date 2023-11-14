CXX := g++
CXXFLAGS := -I./common -O3 -std=c++17 -Wall -pthread -march=native -mavx2

ifeq (/usr/bin/g++-10,$(wildcard /usr/bin/g++-10*))
    CXX=g++-10
endif

all: pi.out

pi.out: pi.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f *.o pi.out *~

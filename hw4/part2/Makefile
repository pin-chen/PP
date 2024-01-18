CXX := mpicxx
CXXFLAGS := -I./common -O3

all: matmul

matmul: main.cc matmul.cc
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f *.o matmul *~

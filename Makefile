appname := bitpool.a
CXX := g++
CXXFLAGS := -Wall -g -std=c++11
srcfiles := $(wildcard *.cpp)
objects := $(patsubst %.cpp, %.o, $(srcfiles))

all: $(appname)

$(appname): $(objects)
	$(CXX) $(CXXFLAGS) -o $(appname) $(objects)

clean:
	rm -f $(objects)
	rm -f $(appname)


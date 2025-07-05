# define compiler
CXX = g++

# define standard
CXXFLAGS = -std=c++23 -Wall -Wextra -g

driver: driver.o
	$(CXX) $(CXXFLAGS) -o driver driver.o

driver.o: driver.cpp
	$(CXX) $(CXXFLAGS) -c driver.cpp

clean:
	rm -f *.o driver

new:
	make clean
	make
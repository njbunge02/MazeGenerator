CXX = g++
OPTIONS = -Wall
PROGRAM = main.out

all: $(PROGRAM)

run: $(PROGRAM)
	./$(PROGRAM)

$(PROGRAM): main.cpp 
	$(CXX) $(OPTIONS) main.cpp -o $(PROGRAM) 

clean:
	rm -f $(PROGRAM)

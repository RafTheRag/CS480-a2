# for c++ compiler
CXX = g++

# -std=c++11  C/C++ variant to use, e.g. C++ 2011
# -Wall       show the necessary warning files
# -g3         include information for symbolic debugger e.g. gdb 
CXXFLAGS = -std=c++11 -Wall -g3 -c

# object files
OBJS = countvocabstrings.o tree.o #readvocab.o readlines.o countvocabstrings.o

# Program name
PROGRAM = countvocabstrings

# instead of calling countsubstrings, can just make all
all: $(PROGRAM)

# The program depends upon its object files
$(PROGRAM) : $(OBJS)
	$(CC) -pthread -o $(PROGRAM) $(OBJS)

main.o : main.cpp
	$(CXX) $(CXXFLAGS) main.cpp

readvocab.o : readvocab.cpp readvocab.h
	$(CXX) $(CXXFLAGS) readvocab.cpp

readlines.o: readlines.cpp readlines.h
	$(CXX) $(CXXFLAGS) readlines.cpp
    
countvocabstrings.o: countvocabstrings.cpp countvocabstrings.h
	$(CXX) $(CXXFLAGS) countvocabstrings.cpp

tree.o : tree.h tree.cpp
	$(CXX) $(CXXFLAGS) tree.cpp

clean :
	rm -f *.o $(PROGRAM)

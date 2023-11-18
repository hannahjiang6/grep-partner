###
### Makefile for gerp project
### gerp is a simplified version of grep
###
### Author:  Hannah Jiang (hjiang03) and Zachary White (zwhite03)

MAKEFLAGS += -L

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3 

# Compiles gerp
gerp: main.o gerp.o hash.o FSTree.o DirNode.o
	$(CXX) $(LDFLAGS) -o gerp main.o gerp.o hash.o FSTree.o DirNode.o

# This rule builds main.o
main.o: main.cpp 
	$(CXX) $(CXXFLAGS) -c main.cpp

# This rule builds gerp.o
gerp.o: gerp.cpp gerp.h
	$(CXX) $(CXXFLAGS) -c gerp.cpp

# This rule builds hash.o
hash.o: hash.cpp hash.h 
	$(CXX) $(CXXFLAGS) -c hash.cpp

# Compiles and runs treeTraversal
treeTraversal: FSTreeTraversal.cpp DirNode.o FSTree.o
	$(CXX) $(CXXFLAGS) -o treeTraversal FSTreeTraversal.cpp DirNode.o FSTree.o

# This rule builds stringProcessing.o
stringProcessing.o: stringProcessing.cpp stringProcessing.h
	$(CXX) $(CXXFLAGS) -c stringProcessing.cpp

# Compiles and runs unit_test
unit_test: unit_test_driver.o DirNode.o FSTree.o stringProcessing.o \
           hash.o gerp.o
	$(CXX) $(CXXFLAGS) $^


# # This rule provides my final submission 
provide:
	provide comp15 proj4_gerp \
				   unit_tests.h README Makefile \
				   gerp.cpp gerp.h hash.cpp hash.h \
				   main.cpp commands.txt
				   

# clean: 
# 	rm main.o *~ a.out
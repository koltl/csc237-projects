cc=g++
debugFlag=-g

tree: BinarySearchTree.o term.o Treetest.o 
	$(cc) -o tree Treetest.o BinarySearchTree.o term.o $(debugFlag)

Treetest.o: Treetest.cpp  BinarySearchTree.h
	$(cc) -c Treetest.cpp $(debugFlag)

term.o: term.cpp  term.h
	$(cc) -c term.cpp $(debugFlag)

BinarySearchTree.o: BinarySearchTree.cpp BinarySearchTree.h 
	$(cc) -c BinarySearchTree.cpp $(debugFlag)


clean: 
	\rm -f *.o testdate

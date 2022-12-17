COMPILER  = g++

DEBUG  = 

EXE  = app

HDRS  = term.h\
	TermArrayList.h\
	TermVectorList.h\
	TermDblLinkList.h\
	DblLink.h\
	TermList.h\

OBJS  = term.o\
	TermArrayList.o\
	TermVectorList.o\
	TermDblLinkList.o\
	app.o\

SRC  = 	term.cpp\
	TermArrayList.cpp\
	TermVectorList.cpp\
	TermDblLinkList.cpp\
	app.cpp\


##########################################################################
$(EXE): $(OBJS) $(HDRS) $(SRC)
	$(COMPILER) -o $(EXE) $(OBJS) $(DEBUG)

term.o:  term.cpp term.h 
	$(COMPILER) -c term.cpp $(DEBUG)

TermArrayList.o:  term.h TermArrayList.cpp TermArrayList.h TermList.h 
	$(COMPILER) -c TermArrayList.cpp $(DEBUG)

TermVectorList.o: term.h TermVectorList.cpp TermVectorList.h TermList.h
	$(COMPILER) -c TermVectorList.cpp $(DEBUG)

TermDblLinkList.o: term.h TermDblLinkList.cpp TermDblLinkList.h TermList.h
	$(COMPILER) -c TermDblLinkList.cpp $(DEBUG)

app.o:  TermArrayList.h TermVectorList.h TermDblLinkList.h TermList.h app.cpp 
	$(COMPILER) -c app.cpp $(DEBUG)


clean:
	del *.o $(EXE)


# Project: AM71113363
# Makefile created by Dev-C++ 4.9.9.2

CC   = gcc.exe
WINDRES = windres.exe
RES  = main.res
OBJ  = main.o listview.o scandir.o delfiles.o verifydir.o $(RES)
LINKOBJ  = main.o listview.o scandir.o delfiles.o verifydir.o $(RES)
LIBS =  -L"C:/Dev-Cpp/lib" -mwindows -lcomctl32  
INCS =  -I"C:/Dev-Cpp/include" 
BIN  = DirCleanUp.exe
CFLAGS = $(INCS)  
RM = rm -f

.PHONY: all all-before all-after clean clean-custom

all: all-before DirCleanUp.exe all-after


clean: clean-custom
	${RM} $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CC) $(LINKOBJ) -o "DirCleanUp.exe" $(LIBS)

main.o: main.c
	$(CC) -c main.c -o main.o $(CFLAGS)

listview.o: listview.c
	$(CC) -c listview.c -o listview.o $(CFLAGS)

scandir.o: scandir.c
	$(CC) -c scandir.c -o scandir.o $(CFLAGS)

delfiles.o: delfiles.c
	$(CC) -c delfiles.c -o delfiles.o $(CFLAGS)

verifydir.o: verifydir.c
	$(CC) -c verifydir.c -o verifydir.o $(CFLAGS)

main.res: main.rc 
	$(WINDRES) -i main.rc --input-format=rc -o main.res -O coff 

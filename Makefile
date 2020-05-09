CC = gcc
CFLAGS = -O1 -g -Wall -std=c99 -pedantic -lgsl -lgslcblas -DHW8
CORFLAGS = -O1 -g -Wall -std=c99 -pedantic
MFLAGS = -O1 -g -Wall -std=c99 -pedantic -lgsl -lgslcblas -DHW8
SOURCE = hw11.c DynamicArrays.c 
CORSRC = correction.c
OBJ = $(patsubst %.c, %.o, $(SOURCE))
EXE = hw11
EXECOR = correction
EXEREAL = realDevice
EXEDETERR = detError
EXEDIFFVAL = diffVal
EXEMYPLOT = myplot
EXEMEM = hw11_mem
VALGRIND = valgrind --tool=memcheck --leak-check=yes --track-origins=yes
DATATXT = data.txt 
ALLDATATXT = alldata.txt
REALTXT = realdevice.txt
CORTXT = correction.txt
PNG = plot.png
RESULTS = out.txt
MEMTXT = mem.txt
VERB = VERBOSE

.SILENT:
all: $(EXE) $(EXEMEM) $(EXECOR)

$(EXE): $(SOURCE)
	@echo "Compiling hw11"
	$(CC) $(CFLAGS) $(SOURCE) -o $(EXE)

$(EXECOR): $(CORSRC)
	@echo "Compiling correction order 4"
	$(CC) $(CORFLAGS) -DORD=4 $(CORSRC) -o $(EXECOR)

$(EXEMEM): $(SOURCE)
	@echo "Compiling hw11_mem"
	$(CC) $(MFLAGS) $(SOURCE) -o $(EXEMEM)

base: $(EXEREAL) $(EXEDETERR) $(EXEDIFFVAL)
	@echo "Calculating error from realDevice using detError"
	./$(EXEREAL) | ./$(EXEDETERR)
	@echo "Creating data.txt"
	./$(EXEREAL) | ./$(EXEDIFFVAL) > $(DATATXT)

correct: $(EXEREAL) $(EXECOR) $(EXEDETERR) 
	@echo "Calculating the error"
	./$(EXEREAL) | ./$(EXECOR) | ./$(EXEDETERR) 

plot: $(EXEMYPLOT) $(EXECOR) $(EXEREAL)
	./$(EXEREAL) > $(REALTXT)
	./$(EXEREAL) | ./$(EXECOR) > $(CORTXT)
	paste $(REALTXT) $(CORTXT) > $(ALLDATATXT)
	./$(EXEMYPLOT) -i $(ALLDATATXT) -o $(PNG) 
	@echo "View the plot in plot.png"

x: $(EXEREAL) $(EXEDETERR) $(EXEMYPLOT) $(EXEDIFFVAL)
	@echo "chmod +x"
	chmod +x $(EXEREAL)
	chmod +x $(EXEDETERR)
	chmod +x $(EXEMYPLOT)
	chmod +x $(EXEDIFFVAL)
	 
.PHONY: mem clean test all help
mem: $(EXEMEM)
	@echo "running valgrind..."
	$(VALGRIND) ./$(EXEMEM) -o 3 -p $(DATATXT) > $(MEMTXT) 2>&1
	@echo "valgrind output in mem.txt"

clean: 
	-rm -f $(EXE) $(RESULTS) $(MEMTXT) $(EXEMEM) $(EXECOR) $(CORTXT) $(ALLDATATXT) $(PNG) $(REALTXT) 

help:
	@echo "make options are: all, clean, mem, base, correct, plot"



IDIR = include/
SRCDIR = src/
DEPS := $(wildcard $(IDIR)*.hpp) #find hpp files
CSRC := $(wildcard $(SRCDIR)*.cpp) #find all cpp files

CC=g++
CFLAGS=-I$(IDIR) -std=c++11
EXSRC = $(shell if [ ! -d "$(SRCDIR)" ]; then echo "Create src directory!" ; fi)
EXOBJ = $(shell if [ ! -d "$(ODIR)" ]; then mkdir $(ODIR) && echo "obj dir created" ; fi)
EXINCL = $(shell if [ ! -d "$(IDIR)" ]; then echo "Create include directory!" ; fi)
#object file folder
ODIR = obj/
OBJ := $(CSRC:.cpp=.o) #replace .cpp with .o
OBJ := $(OBJ:$(SRCDIR)%=$(ODIR)%) #replace /src with /obj  
	
$(ODIR)%.o: $(SRCDIR)%.cpp $(DEPS) 	#Define rule that creates object files
# Compile cpp files and names as the name from left of :
	$(CC) -c -o $@ $< $(CFLAGS) 	
	
result: rule $(OBJ)
	$(CC) -o $@ $(OBJ) $(CFLAGS)
	@echo "Success!"

rule:
	@echo $(EXOBJ)
	@echo $(EXSRC)
	@echo $(EXINCL)
	
# make "clean" to be an out-of-date target for make, in case of a "clean" file
#	in your main directory it will not be considered by make
.PHONY: clean
clean:
		rm -f $(ODIR)*.o

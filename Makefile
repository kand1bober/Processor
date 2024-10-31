

all: make run



make: assembler processor

assembler: 
	cd Assembl && make 

processor:
	cd Proc && make 




run : run_assembler run_processor

run_assembler: 
	cd Assembl && ./Assembler

run_processor:
	cd Proc && ./Processor 



clean: 
	cd Assembl && make clean 
	cd Proc && make clean
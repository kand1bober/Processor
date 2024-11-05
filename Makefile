
all: make run



make: assembler processor

assembler: 
	cd Assembl && make DEB_ASM=1

processor:
	cd Proc && make DEB=0 PRINT=0



run : run_assembler run_processor

run_assembler: 
	cd Assembl && ./Assembler

run_processor:
	cd Proc && ./Processor 


clean: 
	cd Assembl && make clean 
	cd Proc && make clean
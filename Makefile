CC = clang
CCPLUS=clang++
CFLAGS=-emit-llvm -S
FILE=main
FOLDER=tests

all: instrument sdg

clean: 
	rm -f $(FOLDER)/*.bc $(FOLDER)/*.ll $(FOLDER)/*.dot $(FOLDER)/*.s $(FOLDER)/*_instr $(FOLDER)/*.stats

instrument: $(FOLDER)/$(FILE).c
	$(CC) $(CFLAGS) $(FOLDER)/$(FILE).c -o $(FOLDER)/$(FILE).bc 
	opt -load /home/sharjeel/llvm-build/lib/LLVMDDG.so -DDG $(FOLDER)/$(FILE).bc -o $(FOLDER)/$(FILE)_instr.bc
	llc -o $(FOLDER)/$(FILE)_instr.s $(FOLDER)/$(FILE)_instr.bc
	$(CCPLUS) $(FOLDER)/$(FILE)_instr.s -o $(FOLDER)/$(FILE)_instr -L /home/sharjeel/lib -lmy_lib

sdg: $(FOLDER)/$(FILE).c
	$(CC) $(CFLAGS) $(FOLDER)/$(FILE).c -o $(FOLDER)/$(FILE).bc 
	./llvm-dg-dump $(FOLDER)/$(FILE).bc > $(FOLDER)/$(FILE).dot

ddg: $(FOLDER)/$(FILE).dot $(FOLDER)/$(FILE).stats ddg.py
	python ddg.py -graph $(FOLDER)/$(FILE).dot -dynamic $(FOLDER)/$(FILE).stats -save $(FOLDER)/$(FILE)_new.dot

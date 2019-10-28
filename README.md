# Dynamic Dependence Graph (DDG)

Dynamic Dependence Graph (DDG) help software engineers with numerous tasks like debugging, code refactoring or analysis. DDG show both data dependency (value computed at one instruction is dependent on the value computed from previous instruction) and control dependency (instruction is computed based on a value being set). I created the DDG by implementing Approach 1 and 2 from [Hiralal Agrawal and Joseph R. Horg's Dynamic Program Slicing paper](https://www.cs.columbia.edu/~junfeng/08fa-e6998/sched/readings/slicing.pdf). I implemented it using LLVM (project to write compiler based technologies), LLVM instrumentation and DG tool (tool written in LLVM to create static dependence grap).

## Getting Started

These instructions will get you a copy of the project up and running on your local machine.

### Prerequisites

These are the software needed:
* Python (2.7+)
* LLVM (4.5+)
* Cmake

### Installing

A step by step series of examples that tell you how to begin running the program

#### LLVM 

Firstly, you must clone a [LLVM repo](https://github.com/llvm-mirror/llvm). 

```
git clone https://github.com/llvm-mirror/llvm.git
```

Secondly, create a directory and cmake the build into it.

```
mkdir llvm_build
```

Thirdly, copy the DDG folder into llvm git repo folder

```
cp -rf DDG/ <path>/llvm/lib/Transforms/.
```

Fourthly, edit the CMakeLists.txt by adding the below line.

```
add_subdirectory(DDG)
```

Fifthly, head to the build folder and run make to build all the files into the build folder. If you have a stronger computer, you can run make with numerous threads.

```
make 
```

or 

```
make -j16
```

Sixthly, head to DDG_runtime folder and run make to create the library function.

Seventhly, edit your LD_LIBRARY_PATH on Linux or DYLD_LIBRARY_PATH on Mac so it points to libmy_lib.so.

Lastly, edit the Makefile to change paths to LLVMDDG.so and the library folder.
 

#### Python

If you do not have python, you can install it from https://www.python.org/downloads/

For creating the DDG, we need pygraphviz so use pip to install it.

```
pip install pygraphviz
```

## Running the tests

Once everything is installed, run make.

```
make
```

This will generate both main.dot and main_instr. Run main_instr to generate main.stats

```
./main_instr 0 5
```

After this, run the python script to generate the DDG in main_new.dot .

```
make ddg
```

For your own test cases, edit the Makefile and change FILE.

## Built With

* [DG Tool](https://github.com/mchalupa/dg) - Tool used to generate initial DG
* [LLVM](https://www.llvm.org/) - Compiler Infrastructure to run DG tool and instrument the DDG pass
* [Pygraphviz](https://pygraphviz.github.io/) - Library to read DG and generate DDG

## Authors

* **Sharjeel Khan**

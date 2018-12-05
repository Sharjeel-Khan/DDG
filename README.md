# Dynamic Dependence Graph (DDG)

Dynamic Dependence Graph (DDG) help software engineers with numerous tasks like debugging, code refactoring or analysis. DDG show both data dependency (value computed at one instruction is dependent on the value computed from previous instruction) and control dependency (instruction is computed based on a value being set). We create DDG by implementing Approach 1 and 2 from [Hiralal Agrawal and Joseph R. Horg's Dynamic Program Slicing paper](https://www.cs.columbia.edu/~junfeng/08fa-e6998/sched/readings/slicing.pdf). We implemented it using LLVM (project to write compiler based technologies), LLVM instrumentation and DG tool (tool written in LLVM to create static dependence grap).

## Getting Started

These instructions will get you a copy of the project up and running on your local machine.

### Prerequisites

These are the software needed:
* Python (2.7+)
* LLVM (4.5+)

### Installing

A step by step series of examples that tell you how to begin running the program



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

## Built With

* [DG Tool](https://github.com/mchalupa/dg) - Tool used to generate initial DG
* [LLVM](https://www.llvm.org/) - Compiler Infrastructure to run DG tool and instrument the DDG pass
* [Pygraphviz](https://pygraphviz.github.io/) - Library to read DG and generate DDG

## Authors

* **Sharjeel Khan**

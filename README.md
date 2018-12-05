# Dynamic Dependence Graph (DDG)

Dynamic Dependence Graph (DDG) help software engineers with numerous tasks like debugging, code refactoring or analysis. DDG show both data dependency (value computed at one instruction is dependent on the value computed from previous instruction) and control dependency (instruction is computed based on a value being set). We create DDG by implementing Approach 1 and 2 from Hiralal Agrawal and Joseph R. Horg's Dynamic Program Slicing paper (https://www.cs.columbia.edu/~junfeng/08fa-e6998/sched/readings/slicing.pdf). We implemented it using LLVM (project to write compiler based technologies), LLVM instrumentation and DG tool (tool written in LLVM to create static dependence grap).

## Getting Started

These instructions will get you a copy of the project up and running on your local machine.

### Prerequisites

What things you need to install the software and how to install them

```
Give examples
```

### Installing

A step by step series of examples that tell you how to get a development env running

Say what the step will be

```
Give the example
```

And repeat

```
until finished
```

End with an example of getting some data out of the system or using it for a little demo

## Running the tests

Explain how to run the automated tests for this system

## Built With

* [DG Tool](https://github.com/mchalupa/dg) - Tool used to generate initial DG
* [LLVM](https://www.llvm.org/) - Compiler Infrastructure to run DG tool and instrument the DDG pass
* [Pygraphviz](https://maven.apache.org/) - Library to read DG and generate DDG

## Authors

* **Sharjeel Khan**

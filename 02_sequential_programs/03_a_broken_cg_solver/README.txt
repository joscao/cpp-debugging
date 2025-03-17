Exercise: A broken CG solver (Cpp)

This exercise is longer than the others and the code is more complex.

It runs an iterative solver of a linear algebra system. Showcased are the solving process of two sytems of equations. What are the expected solutions?

It has some problems, though.

1. Compilation errors

Try compiling the program with

g++ -g -O2 main.cpp conjugate_gradient.cpp -o cg_solver

The code does not compile. Can you find the problems following hints from the compiler or your IDE? What about common erorr flags?

2. Segfault

Once you manage to compile it, run the program with

./cg_solver

Now there’s a corrupted top size fault! Experiment which tool is reasonable to find this error. Can you fix it?

Looks like it works! But does it, actually?

3. Logic Error

Not all errors are implementation errors, sometimes there is a logic problem. Compare with a standard CG Algorith, is there a difference?
Exercise: The double pendulum (C) - by rantahar

This exercise is longer than the others and the code is more complex.

The code is at double_pendulum.c It runs a simulation of a double pendulum. It has some problems, though.

1. Compilation errors

Try compiling the program with

cd examples

gcc -g -O2 double_pendulum.c -lm -o double_pendulum

The code does not compile. Can you find the problems following hints from the compiler or your IDE? What about common erorr flags?

2. Segfault

Once you manage to compile it, run the program with

./double_pendulum

Now there’s a segmentation fault! Use a debugger to find where the segfault happens. Can you fix it?

Looks like it works! But does it, actually?

3. Memory leak

You have received complaints from users. When the program runs for a long time, it takes a lot of memory. Maybe there is a memory leak.

Hint: You can separate valgrind output (and other errors) to a file using

valgrind --leak-check=full double_pendulum 2> valgrind_errors

4. More?

Can you find another memory issue?

Hint: Use valgrind tool=memcheck and let the simulation run for a while.

Hint: What happens when a pendulum does not fit on the screen?

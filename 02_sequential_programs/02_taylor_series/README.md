# How to Debug Using GDB

We are going to use two programs to illustrate how GDB can be used to debug code.

## Debugging a program with a logical error

The first sample program has some logical errors. The program is supposed to output the summation of:

\[(X^0)/0! + (X^1)/1! + (X^2)/2! + (X^3)/3! + (X^4)/4! + ... + (X^n)/n!\]

given `x` and `n` as inputs. However, the program outputs `inf`, regardless of the inputs. We will go step by step through the debugging process and trace the errors.

### Steps to Debug

1. Compile and execute the program 'taylor_series.cpp':

    ```sh
    g++ -g taylor_series.cpp -o taylor_series
    ./taylor_series
    ```
   
   The `-g` option enables meaningful GDB debugging.
2. Start the debugger:

    ```sh
    gdb taylor_series
    ```
   
   This starts the debugger but does not run the program.
3. Look at the source code and set a breakpoint at line 43:

    ```sh
    (gdb) b 43
    ```
   
   This line contains:

    ```cpp
    double seriesValue = ComputeSeriesValue(x, n);
    ```
4. Run the program in the debugger:

    ```sh
    (gdb) run
    ```
   
   If the program requires command-line arguments, include them after `run`.
5. Enter values `x=2` and `n=3`. The expected output is `5`. The program should pause at the breakpoint:

    ```sh
    Breakpoint 1, main () at taylor_series.cpp:43
    43  double seriesValue = ComputeSeriesValue(x, n);
    ```
6. Step into the `ComputeSeriesValue()` function:

    ```sh
    (gdb) step
    ComputeSeriesValue (x=2, n=3) at taylor_series.cpp:17
    17  double seriesValue=0.0;
    ```
7. Step through the function until reaching `ComputeFactorial()`:

    ```sh
    (gdb) next
    18  double xpow=1;
    (gdb) n
    20  for (int k = 0; k <= n; k++) {
    (gdb) 
    21    seriesValue += xpow / ComputeFactorial(k) ;
    (gdb) step
    ComputeFactorial (number=0) at taylor_series.cpp:7
    7  int fact=0;
    ```
8. View the call stack using `backtrace`:

    ```sh
    (gdb) bt
    #0  ComputeFactorial (number=0) at taylor_series.cpp:7
    #1  0x08048907 in ComputeSeriesValue (x=3, n=2) at taylor_series.cpp:21
    #2  0x08048a31 in main () at taylor_series.cpp:43
    ```
9. Watch variable changes using `print`:

    ```sh
    (gdb) next
    9  for (int j = 0; j <= number; j++) {
    (gdb) n
    10    fact = fact * j;
    (gdb) n
    9  for (int j = 0; j <= number; j++) {
    (gdb) print fact
    $2 = 0
    (gdb) n
    13  return fact;
    (gdb) quit
    ```

### Fixing the Error

The `print` command shows `fact = 0`, which causes the function to return `0` incorrectly. The issue is:

```cpp
int fact = 0;
```

This should be changed to:

```cpp
int fact = 1;
```

Recompile and run the program again to get the expected output.

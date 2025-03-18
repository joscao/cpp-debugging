// Modified Program originally by donahoo - https://cs.baylor.edu/~donahoo/tools/gdb/tutorial.html

#include <iostream>
#include <cmath>

int ComputeFactorial(int number) {
  int fact = 0;

  for (int j = 1; j <= number; j++) {
    fact = fact * j;
  }

  return fact;
}

double ComputeSeriesValue(double x, int n) {
  double seriesValue = 0.0;
  double xpow = 1;

  for (int k = 0; k <= n; k++) {
    seriesValue += xpow / ComputeFactorial(k);
    xpow = xpow * x;
  }

  return seriesValue;
}

int main() {
  std::cout << "This program is used to compute the value of the following series : " << '\n';

  std::cout << "(x^0)/0! + (x^1)/1! + (x^2)/2! + (x^3)/3! + (x^4)/4! + ........ + (x^n)/n! " << '\n';

  std::cout << "Please enter the value of x : " ;
  
  double x;
  std::cin >> x;

  int n;
  std::cout << '\n' << "Please enter an integer value for n : " ;
  std::cin >> n;
  std::cout << '\n';

  double seriesValue = ComputeSeriesValue(x, n);
  std::cout << "The value of the series for the values entered is " 
	<< seriesValue << '\n';

  return 0;
}

/*
 * WARNING: THIS IS AN INTENTIALLY FAULTY PROGRAM TO DEMONSTRATE DEBUGGING TECHNIQUES
 */

#include<iostream>

long factorial(int n)
{
    long result(1);
    while(n>0)
    {
        result*=n;
        n--;
    }
    return result;
}

int main()
{
    int n(0);
    std::cout << "Input n to n!: ";
    std::cin >> n;
    long val=factorial(n);
    std::cout << "Input n = " << n;
    std::cout << " , n! = " << val << "\n";
    return 0;
}
#include <iostream>

int fib(int n)
{
    if (n <= 2)
        return n;
    return fib(n - 1) + fib(n - 2);
}

int main()
{
    int n = 5;
    std::cout << fib(n);
}
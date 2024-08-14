#include <vector>
#include <iostream>

void max_heapify(std::vector<int> &rhs, int index, int n)
{
    int largest = index;
    int left = index * 2 + 1;
    int right = index * 2 + 2;

    if (largest < n && rhs[left] > rhs[largest])
    {
        largest = left;
    }

    if (largest < n && rhs[right] > rhs[largest])
    {
        largest = right;
    }
    if (largest != index)
    {
        std::swap(rhs[largest], rhs[index]);
        max_heapify(rhs, largest, n);
    }
}

void make_heap(std::vector<int> &rhs)
{
    int n = rhs.size();
    for (int i = (n / 2 - 1); i >= 0; i--)
    {
        max_heapify(rhs, i, n);
    }
}

int pop(std::vector<int> &rhs, int &n)
{
    int largest = rhs[0];
    rhs[0] = rhs[n];
    n--;
    max_heapify(rhs, 0, n);
    return largest;
}

int main(void)
{
    std::vector<int> arr = {2, 4, 1, 5, 7, 6, 9, 3};
    make_heap(arr);
    int n = arr.size() - 1;
    int m = n;
    for (int i = 0; i < m; i++)
    {
        std::cout << pop(arr, n) << " ";
    }
    return 0;
}
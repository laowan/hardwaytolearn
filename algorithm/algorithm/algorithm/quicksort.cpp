#include "common.h"

void quick_sort_wan(int a[], int m, int n)
{
    int i = m + 1, j = n;
    if (i > j)
        return;

    if (i == j && a[m] > a[i])
    {
        swapInt(a, m, i);
        return;
    }

    while (i < j)
    {
        while (a[i] < a[m]) i++;
        while (a[j] > a[m]) j--;

        if (i < j)
        {
            swapInt(a, i, j);
        }
    }

    if (i > j) swapInt(a, m, j);

    quick_sort_wan(a, m, j - 1);
    quick_sort_wan(a, j + 1, n);
}

void quick_sort_std(int s[], int l, int r)
{
    if (l < r)
    {
        int i = l, j = r, x = s[l];
        while (i < j)
        {
            while (i < j && s[j] >= x)
                j--;
            if (i < j)
                s[i++] = s[j];

            while (i < j && s[i] < x)
                i++;
            if (i < j)
                s[j--] = s[i];
        }
        s[i] = x;
        quick_sort_std(s, l, i - 1);
        quick_sort_std(s, i + 1, r);
    }
}

void quicksort(int a[], int sz)
{
    quick_sort_std(a, 0, sz - 1);
} 

void test_quicksort()
{
    int a[] = { 5, 1, 2, 8, 4, 6, 3, 7 };
    printIntArray(a, 8);

    quicksort(a, 8);
    printIntArray(a, 8);
}
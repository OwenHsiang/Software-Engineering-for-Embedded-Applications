#include <stdio.h>

int main()
{
    int number[15];
    int n;
    printf("Input the number of elements to store in the array (max 15):");
    scanf("%d", &n);
    
    if (n > 15)
    printf("The maximum of number must be 15");
    else
    printf("Input %d number of elements in the array: \n", n);

    for (int i=0; i< n; ++i)
    {
        printf("element - %d:", i+1);
        scanf("%d", &number[i]);
    }
    printf("The elements of array in reverse order are :");
    for (int i=n-1; i>= 0; --i)
    {
        printf(" element - %d: %d ", i+1, number[i]);
    }
    return 0;
}
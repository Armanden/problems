// so it is a really basic formula for finding the sqrt 

#include <stdio.h>

float squareRoot(float n)
{
    float x = n;
    float y = 1;
    float e = 0.000001; /* e decides the accuracy level*/
    while (x - y > e) {
        x = (x + y) / 2;
        y = n / x;
    }
    return x;
}

int main()
{

	int n;
	printf("enter number to find the sqrt of: ");
	scanf("%d", &n);
    //int n = 12;
    printf("Square root of %d is %f", n, squareRoot(n));
    getchar();
}

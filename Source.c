#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <math.h>


int measurement(const char* name);

int main(void)
{
    setlocale(LC_ALL, "RUS");
    measurement("QUE");
    measurement("TLS");
    measurement("DNS");

    return 0;
}

int measurement(const char* name)
{
    double pastX, x, Q;

    printf("%s:\n", name);
    printf("X[0] = ");
    scanf("%lf", &pastX);

    for (int i = 1; i < 5; i++)
    {
        printf("X[%d] = ", i);
        scanf("%lf", &x);

        Q = x / pastX;
        pastX = x;

        if (fabs(Q) > 0.8)
        {
            printf("Q[%d] = %.2f ТРЕВОГА\n", i, Q);
        }
        else
        {
            printf("Q[%d] = %.2f НОРМА\n", i, Q);
        }
    }

    return 0;
}

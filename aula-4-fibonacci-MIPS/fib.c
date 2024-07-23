#include <stdio.h>

int fib(int n) {
    if (n < 2) {
        return n;
    } else
        return fib(n - 1) + fib(n - 2);
}

int main() {
    int n;
    printf("Digite o numero de fibonacci\n");
    scanf("%d", &n);
    printf("O resultado e: %d", fib(n));
    return 0;
}
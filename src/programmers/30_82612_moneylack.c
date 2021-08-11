#include <math.h>
#include <stdio.h>

#include "libtap/tap.h"

long long solution(int price, int money, int count) {
    long long n = price * ((pow(count, 2) + count) / 2) - money;
    return n < 0 ? 0 : n;
}

int main() {
    ok(solution(3, 20, 4) == 10);
    return 0;
}
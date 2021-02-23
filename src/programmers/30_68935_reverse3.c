// https://programmers.co.kr/learn/courses/30/lessons/68935
#include <math.h>
#include <stdio.h>

#include "libtap/tap.h"

int solution(int n) {
    int digit = 0, ret = 0;
    while (pow(3, ++digit) <= n) {}
    do {
        ret += n % 3 * pow(3, --digit);
        n /= 3;
    } while (digit);
    return ret;
}

int main(void) {
    ok(solution(45) == 7);
    ok(solution(125) == 229);
    return 0;
}

// https://programmers.co.kr/learn/courses/30/lessons/70128?language=c
#include <stdlib.h>

#include "libtap/tap.h"

int solution(int a[], size_t a_len, int b[], size_t b_len) {
    int ret = 0;
    for (size_t i = 0; i < a_len; i++) {
        ret += a[i] * b[i];
    }
    return ret;
}

int main() {
    int arr1[] = {1, 2, 3, 4};
    int arr2[] = {-3, -1, 0, 2};
    ok(solution(arr1, sizeof(arr1) / sizeof(int), arr2, sizeof(arr2) / sizeof(int)) == 3);
    return 0;
}
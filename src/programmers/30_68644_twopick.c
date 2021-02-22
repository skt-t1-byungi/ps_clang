// https://programmers.co.kr/learn/courses/30/lessons/68644
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libtap/tap.h"

bool map[200] = {
    false,
};

int cmp(const void *ap, const void *bp) {
    int a = *(int *)ap;
    int b = *(int *)bp;
    return a - b;
}

int *solution(int numbers[], size_t numbers_len) {
    int *ret = (int *)malloc(sizeof(int));
    int ret_len = 0, tmp;

    for (size_t i = 0; i < numbers_len; i++) {
        for (size_t j = i + 1; j < numbers_len; j++) {
            tmp = numbers[i] + numbers[j];
            if (!map[tmp]) {
                map[tmp] = true;
                ret = realloc(ret, (++ret_len) * sizeof(int));
                ret[ret_len - 1] = tmp;
            }
        }
    }
    qsort(ret, ret_len, sizeof(int), cmp);
    return ret;
}

int main(void) {
    int arr1[] = {2, 1, 3, 4, 1};
    size_t arr1_len = sizeof(arr1) / sizeof(int);
    int *got1 = solution(arr1, arr1_len);
    int expected1[] = {2, 3, 4, 5, 6, 7};
    cmp_mem(got1, expected1, sizeof(expected1));
    free(got1);

    memset(map, false, sizeof(map));

    int arr2[] = {5, 0, 2, 7};
    size_t arr2_len = sizeof(arr2) / sizeof(int);
    int *got2 = solution(arr2, arr2_len);
    int expected2[] = {2, 5, 7, 9, 12};
    cmp_mem(got2, expected2, sizeof(expected2));
    free(got2);
}

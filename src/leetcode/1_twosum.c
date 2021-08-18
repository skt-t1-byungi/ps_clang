// https://leetcode.com/problems/two-sum/
#include <stdio.h>
#include <stdlib.h>

#include "libtap/tap.h"

int* twosum(int* nums, int len, int target, int* ret_len) {
    int* ret = malloc(2 * sizeof(int));
    size_t i, j;
    for (i = 0; i < len; i++) {
        for (j = i + 1; j < len; j++) {
            if (nums[j] == target - nums[i])
                goto EXIT;
        }
    }
EXIT:
    ret[0] = i;
    ret[1] = j;
    *ret_len = 2;
    return ret;
}

int main(void) {
    int nums[] = {2, 7, 11, 15};
    int ret_len;
    int nums_len = (int)(sizeof(nums) / sizeof(int));
    int* got = twosum(nums, nums_len, 9, &ret_len);
    int expected[] = {0, 1};
    cmp_mem(got, expected, sizeof(expected));
    free(got);
    return 0;
}

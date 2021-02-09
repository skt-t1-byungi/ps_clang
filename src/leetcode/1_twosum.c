// https://leetcode.com/problems/two-sum/
#include <stdio.h>
#include <stdlib.h>

int *twoSum(int *nums, int numsSize, int target, int *returnSize) {
  int *arr = malloc(2 * sizeof(int));
  size_t i, j;
  for (i = 0; i < numsSize; i++) {
    for (j = i + 1; j < numsSize; j++) {
      if (nums[j] == target - nums[i])
        goto OUT;
    }
  }
OUT:
  arr[0] = i;
  arr[1] = j;
  *returnSize = 2;
  return arr;
}

int main(void) {
  int len;
  int nums[] = {2, 7, 11, 15};
  int numsSize = (int)(sizeof(nums) / sizeof(int));
  int *arr = twoSum(nums, numsSize, 9, &len);
  for (size_t i = 0; i < len; i++) {
    printf("%d\n", arr[i]);
  }
  free(arr);
  return 0;
}

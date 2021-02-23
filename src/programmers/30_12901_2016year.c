// https://programmers.co.kr/learn/courses/30/lessons/12901
#include <stdlib.h>

#include "libtap/tap.h"

char* solution(int a, int b) {
    char* str = (char*)malloc(sizeof(char) * 3);
    while (--a) b += a == 2 ? 29 : (int[]){30, 31}[a > 7 ? !(a % 2) : a % 2];
    return str = (char*[]){"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"}[(4 + b) % 7];
}

int main(void) {
    is(solution(5, 24), "TUE");
    return 0;
}

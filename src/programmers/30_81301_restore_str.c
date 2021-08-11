// https://programmers.co.kr/learn/courses/30/lessons/81301
#include <stdlib.h>
#include <string.h>

#include "libtap/tap.h"

char* words[] = {
    "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine",
};

int solution(const char* s) {
    int ret = 0;
    char ch = 0;
    while ((ch = *s)) {
        if (ch >= '0' && ch <= '9') {
            ret *= 10;
            ret += ch - '0';
            s++;
            continue;
        }
        int n = 0;
        for (; n < 10; n++) {
            char* word = words[n];
            size_t word_len = strlen(word);
            if (!strncmp(s, word, word_len)) {
                ret *= 10;
                ret += n;
                s += word_len;
                break;
            }
        }
    }
    return ret;
}

int main() {
    ok(solution("one4seveneight") == 1478);
    ok(solution("23four5six7") == 234567);
    ok(solution("2three45sixseven") == 234567);
    ok(solution("123") == 123);
    return 0;
}
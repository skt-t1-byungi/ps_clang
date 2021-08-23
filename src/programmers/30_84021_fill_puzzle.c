// https://programmers.co.kr/learn/courses/30/lessons/84021?language=c
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "libtap/tap.h"

typedef struct {
    char* items;
    size_t item_size;
    size_t length;
    size_t cap;
} vector;

vector vector_create(size_t item_size) {
    return (vector){
        .items = malloc(sizeof(char) * item_size),
        .item_size = item_size,
        .length = 0,
        .cap = 1,
    };
}

void vector_destroy(vector* vec) {
    free(vec->items);
    vec->length = vec->cap = 0;
}

void vector_push(vector* vec, void* item) {
    if (vec->cap == vec->length) {
        size_t cap = vec->cap = vec->cap * 2 + 1;
        vec->items = realloc(vec->items, sizeof(char) * vec->item_size * cap);
    }
    memcpy(vec->items + (vec->length++) * vec->item_size, item, vec->item_size);
}

void* vector_get(vector* vec, size_t index) {
    return vec->items + index * vec->item_size;
}

void vector_remove(vector* vec, size_t index) {
    vec->length--;
    char* dst = vec->items + index * vec->item_size;
    char* src = dst + vec->item_size;
    memmove(dst, src, sizeof(char) * (vec->length - index) * vec->item_size);
}

struct point {
    int x;
    int y;
};

void normalize(vector piece, int table_size) {
    int x_min = table_size, y_min = table_size;
    for (size_t i = 0; i < piece.length; i++) {
        struct point* p = (struct point*)vector_get(&piece, i);
        x_min = p->x < x_min ? p->x : x_min;
        y_min = p->y < y_min ? p->y : y_min;
    }
    for (size_t i = 0; i < piece.length; i++) {
        struct point* p = (struct point*)vector_get(&piece, i);
        p->x -= x_min;
        p->y -= y_min;
    }
}

void traverse(int** table, size_t table_size, int target, int x, int y, vector* piece) {
    int max = table_size - 1;
    if (table[y][x] == target) {
        table[y][x] = ~target;
        vector_push(piece, &(struct point){10, y});
        if (x > 0)
            traverse(table, table_size, target, x - 1, y, piece);
        if (x < max)
            traverse(table, table_size, target, x + 1, y, piece);
        if (y > 0)
            traverse(table, table_size, target, x, y - 1, piece);
        if (y < max)
            traverse(table, table_size, target, x, y + 1, piece);
    }
}

void collect(int** table, size_t table_size, int target, vector* pieces) {
    for (size_t y = 0; y < table_size; y++) {
        for (size_t x = 0; x < table_size; x++) {
            if (table[y][x] == target) {
                vector p = vector_create(sizeof(vector));
                traverse(table, table_size, target, x, y, &p);
                normalize(p, table_size);
                vector_push(pieces, &p);
            }
        }
    }
    return;
}

vector rotate(vector piece) {
    for (size_t i = 0; i < piece.length; i++) {
        struct point* p = (struct point*)vector_get(&piece, i);
        size_t tmp = p->x;
        p->x = -p->y;
        p->y = tmp;
    }
    return piece;
}

bool equal(vector a, vector b) {
    if (a.length != b.length) {
        return false;
    }
    for (size_t i = 0; i < a.length; i++) {
        struct point* ap = (struct point*)vector_get(&a, i);
        for (size_t j = 0; j < b.length; j++) {
            struct point* bp = (struct point*)vector_get(&b, j);
            if (!memcmp(ap, bp, sizeof(struct point))) {
                goto NEXT;
            }
        }
        return false;
    NEXT:
        continue;
    }
    return true;
}

int solution(int** game_board,
             size_t game_board_rows,
             size_t game_board_cols,
             int** table,
             size_t table_rows,
             size_t table_cols) {
    vector pieces1 = vector_create(sizeof(vector));
    collect(game_board, game_board_rows, 0, &pieces1);
    vector pieces2 = vector_create(sizeof(vector));
    collect(table, table_rows, 1, &pieces2);

    int sum = 0;
    for (size_t i = 0; i < pieces1.length; i++) {
        vector a = *(vector*)vector_get(&pieces1, i);
        for (size_t j = 0; j < pieces2.length; j++) {
            vector b = *(vector*)vector_get(&pieces2, j);
            if (equal(a, b) || equal(a, rotate(b)) || equal(a, rotate(b)) || equal(a, rotate(b))) {
                sum += a.length;
                vector_remove(&pieces2, j);
                vector_destroy(&b);
            }
        }
        vector_destroy(&a);
    }
    for (size_t i = 0; i < pieces2.length; i++) {
        vector_destroy((vector*)vector_get(&pieces2, i));
    }
    vector_destroy(&pieces1);
    vector_destroy(&pieces2);
    return sum;
}

int main(int argc, char const* argv[]) {
    size_t size = 6;
    int a1[] = {1, 1, 0, 0, 1, 0};
    int a2[] = {0, 0, 1, 0, 1, 0};
    int a3[] = {0, 1, 1, 0, 0, 1};
    int a4[] = {1, 1, 0, 1, 1, 1};
    int a5[] = {1, 0, 0, 0, 1, 0};
    int a6[] = {0, 1, 1, 1, 0, 0};
    int* game_board[] = {a1, a2, a3, a4, a5, a6};
    int b1[] = {1, 0, 0, 1, 1, 0};
    int b2[] = {1, 0, 1, 0, 1, 0};
    int b3[] = {0, 1, 1, 0, 1, 1};
    int b4[] = {0, 0, 1, 0, 0, 0};
    int b5[] = {1, 1, 0, 1, 1, 0};
    int b6[] = {0, 1, 0, 0, 0, 0};
    int* table[] = {b1, b2, b3, b4, b5, b6};
    ok(solution(game_board, size, size, table, size, size) == 14);
    return 0;
}

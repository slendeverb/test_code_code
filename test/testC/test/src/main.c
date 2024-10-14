#include <ctype.h>
#include <malloc.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define start_capacity 10
#define plus_capacity 10

typedef struct Array {
    void** ptr;
    int capacity;
    int num;
} Array;

Array* init_array(int capacity) {
    Array* array = (Array*)malloc(sizeof(Array));
    if (array == NULL) {
        return NULL;
    }
    array->ptr = (void**)malloc(sizeof(void*) * capacity);
    if (array->ptr == NULL) {
        return NULL;
    }
    array->capacity = capacity;
    array->num = 0;
    return array;
}

void insert_data(Array* array, int pos, void* data) {
    if (pos < 0) {
        fprintf(stderr, "insert location fault\n");
        return;
    }
    if (array->capacity == array->num) {
        int new_capacity = array->capacity + plus_capacity;
        void** new_space = (void**)malloc(sizeof(void*) * new_capacity);
        if (new_space == NULL) {
            fprintf(stderr, "fail to expand array\n");
            return;
        }
        memcpy(new_space, array->ptr, sizeof(void*) * array->capacity);
        free(array->ptr);
        array->ptr = new_space;
        array->capacity = new_capacity;
    }
    if (pos >= array->num) {
        pos = array->num;
    }
    for (int i = array->num - 1; i >= pos; i--) {
        array->ptr[i + 1] = array->ptr[i];
    }
    memcpy(array->ptr + pos, &data, sizeof(data));
    array->num++;
}

void delete_data(Array* array, int pos) {
    if (pos >= array->num) {
        return;
    }
    for (int i = pos; i < array->num - 1; i++) {
        array->ptr[i] = array->ptr[i + 1];
    }
    array->num--;
}

void destroy_array(Array* array) {
    for (int i = 0; i < array->num; i++) {
        free(array->ptr[i]);
        array->ptr[i] = NULL;
    }
    free(array->ptr);
    array->ptr = NULL;
    array->num = 0;
    array->capacity = 0;
}

int maxScoreSightseeingPair(int** values, int valuesSize) {
    int ans = 0;
    int mx = *values[0];
    for (int j = 1; j < valuesSize; j++) {
        ans = __max(ans, mx + *values[j] - j);
        mx = __max(mx, *values[j] + j);
    }
    return ans;
}

int main() {
    FILE* input_fp = NULL;
    input_fp = fopen("C:/Users/slendeverb/Documents/code_code/test/in.txt", "r");
    if (input_fp == NULL) {
        fprintf(stderr, "open file failed");
        exit(EXIT_FAILURE);
    }
    Array* array = init_array(start_capacity);
    if (array == NULL) {
        fprintf(stderr, "create array failed");
        exit(EXIT_FAILURE);
    }
    char ch = 0;
    int num = 0;
    while ((ch = getc(input_fp)) != EOF) {
        if (isdigit(ch)) {
            num = num * 10 + ch - '0';
        } else {
            int* x = (int*)malloc(sizeof(int));
            *x = num;
            insert_data(array, array->num, x);
            num = 0;
        }
    }
    fclose(input_fp);
    input_fp = NULL;

    double start = clock() * 1e6;
    int ans = maxScoreSightseeingPair((int**)array->ptr, array->num);
    double end = clock() * 1e6;
    double elapsed_time = end - start;
    printf("ans: %d, time: %lf\n", ans, elapsed_time);

    destroy_array(array);
    free(array);
    array = NULL;
}
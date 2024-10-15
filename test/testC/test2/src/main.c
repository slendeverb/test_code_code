#include <math.h>
#include <stdio.h>
#include <time.h>

int helper(int x, int y) {
    for (int i = 1;; i++) {
        if (i & 1) {
            x -= i;
            if (x < 0) {
                return i - 1;
            }
        } else {
            y -= i;
            if (y < 0) {
                return i - 1;
            }
        }
    }
}

int max_height_of_triangle(int red, int blue) {
    return fmax(helper(red, blue), helper(blue, red));
}

int main(int argc, char** argv) {
    clock_t start = clock();
    int red = 10;
    int blue = 20;
    printf("%d\n", max_height_of_triangle(red, blue));
    clock_t end = clock();
    printf("%ld\n", (end - start));
}
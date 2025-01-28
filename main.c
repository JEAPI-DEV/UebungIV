#include <stdio.h>
#include <float.h>
#include <time.h>

/* Machine precision functions */
float fmasch(int a);
double dmasch(int a);

/* Recursive functions */
int f1(int n);
int f2(int n);
int f3(int n);
int f4(int n);

/* Binomial coefficient functions */
int recursiveC(int n, int k);
int iterativeC(int n, int k);
static int call_counter = 0;

int main() {
    int n;
    int test_n = 5, test_k = 2;
    clock_t start_time = 0, end_time = 0;
    double time_recursive = 0, time_iterative = 0;
    int result_recursive = 0, result_iterative = 0;

    /* Maschinengenauigkeit */
    printf("Maschinengenauigkeit (float):\n");
    printf("a=2:  %e\n", fmasch(2));
    printf("a=10: %e\n", fmasch(10));
    printf("a=16: %e\n\n", fmasch(16));

    printf("Maschinengenauigkeit (double):\n");
    printf("a=2:  %e\n", dmasch(2));
    printf("a=10: %e\n", dmasch(10));
    printf("a=16: %e\n\n", dmasch(16));

    printf("Vergleich mit float.h:\n");
    printf("FLT_EPSILON: %e, DBL_EPSILON: %e\n", FLT_EPSILON, DBL_EPSILON);
    printf("FLT_MIN: %e, DBL_MIN: %e\n\n", FLT_MIN, DBL_MIN);

    /* Rekursive Funktionen */
    printf("Rekursive Funktionen:\n");

    printf("1. Funktion (Collatz-ähnlich):\n");
    for (n = 1; n <= 7; n++) {
        printf("f1(%d): ", n);
        f1(n);
        printf("\n");
    }

    printf("\n2. Funktion (Quadratzahlen):\n");
    for (n = 1; n <= 7; n++) {
        printf("f2(%d) = %d\n", n, f2(n));
    }

    printf("\n3. Funktion (Komplexe Rekursion):\n");
    for (n = 1; n <= 7; n++) {
        printf("f3(%d) = %d\n", n, f3(n));
    }

    printf("\n4. Funktion (McCarthy 91):\n");
    for (n = 1; n <= 7; n++) {
        printf("f4(%d) = %d\n", n, f4(n));
    }

    /*  Mehrdimensionale rekursive Funktionen */
    printf("\nBinomialkoeffizienten:\n");

    /* Measure recursive function time */
    start_time = clock();
    result_recursive = recursiveC(test_n, test_k);
    end_time = clock();
    time_recursive = ((double)(end_time - start_time) / CLOCKS_PER_SEC) * 1000.0;

    /* Measure iterative function time */
    start_time = clock();
    result_iterative = iterativeC(test_n, test_k);
    end_time = clock();
    time_iterative = ((double)(end_time - start_time) / CLOCKS_PER_SEC) * 1000.0;

    printf("Recursive: C(%d,%d) = %d  | calls: %d, time taken : %.3f ms\n",
           test_n, test_k, result_recursive, call_counter, time_recursive);

    printf("Iterative: C(%d,%d) = %d  | time taken : %.3f ms\n",
           test_n, test_k, result_iterative, time_iterative);

    return 0;
}

float fmasch(int a) {
    float x = 1.0f;
    float prev_x;
    do {
        prev_x = x;
        x /= a;
    } while (1.0f + x != 1.0f);
    return prev_x;
}

double dmasch(int a) {
    double x = 1.0;
    double prev_x;
    do {
        prev_x = x;
        x /= a;
    } while (1.0 + x != 1.0);
    return prev_x;
}

int f1(int n) { /*  Collatz conjecture sequence. */
    printf("%d ", n);
    if (n == 1) return 1;
    return (n % 2 == 0) ? f1(n / 2) : f1(3 * n + 1);
}

int f2(int n) { /* Calculate square numbers */
    return (n == 1) ? 1 : f2(n - 1) + 2 * n - 1;
}

int f3(int n) { /* Hofstadter Q sequence */
    if (n == 1 || n == 2) return 1;
    return f3(n - f3(n - 1)) + f3(n - f3(n - 2));
}

int f4(int n) { /* McCarthy 91 */
    if (n > 100) return n - 10;
    return f4(f4(n + 11));
}

int recursiveC(int n, int k) {
    call_counter++;
    if (k < 0 || k > n) return 0;
    if (k == 0 || k == n) return 1;
    return recursiveC(n-1, k-1) + recursiveC(n-1, k);
}

int iterativeC(int n, int k) {
    int i = 1;
    if (k < 0 || k > n) return 0;
    if (k == 0 || k == n) return 1;

    int result = 1;
    for (; i <= k; i++) {
        result = result * (n - k + i) / i;
    }
    return result;
}
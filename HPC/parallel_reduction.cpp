#include <stdio.h>
#include <omp.h>

void reductionDemo(int arr[], int n) {
    int sum = 0, min = arr[0], max = arr[0];

    #pragma omp parallel for reduction(+:sum) reduction(min:min) reduction(max:max)
    for (int i = 0; i < n; i++) {
        sum += arr[i];
        if (arr[i] < min) min = arr[i];
        if (arr[i] > max) max = arr[i];
    }

    printf("Sum = %d, Avg = %.2f, Min = %d, Max = %d\n", sum, (float)sum/n, min, max);
}

int main() {
    int n, i;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter the elements: ");
    for (i = 0; i < n; i++) scanf("%d", &arr[i]);

    reductionDemo(arr, n);

    return 0;
}

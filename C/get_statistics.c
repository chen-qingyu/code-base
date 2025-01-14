#include <stdio.h>

struct statistics
{
    int count;
    double sum;
    double mean;
    double max;
    double min;
};

struct statistics get_statistics(double arr[], int n)
{
    struct statistics ret;
    ret.count = n;
    ret.sum = 0;
    ret.max = arr[0];
    ret.min = arr[0];
    for (int i = 0; i < n; i++)
    {
        ret.max = ret.max > arr[i] ? ret.max : arr[i];
        ret.min = ret.min < arr[i] ? ret.min : arr[i];
        ret.sum += arr[i];
    }
    ret.mean = ret.sum / n;
    return ret;
}

int main(void)
{
    double arr[] = {1, 2, 3, 4, 5};
    int arr_len = sizeof(arr) / sizeof(arr[0]);
    for (int i = 0; i < arr_len; i++)
    {
        printf("%lf ", arr[i]);
    }
    printf("\n\n");

    struct statistics ret = get_statistics(arr, arr_len);
    printf("count:\t%d\nsum:\t%.2lf\nmean:\t%.2lf\nmax:\t%.2lf\nmin:\t%.2lf\n", ret.count, ret.sum, ret.mean, ret.max, ret.min);

    return 0;
}

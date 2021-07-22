#include <stdio.h>

struct value
{
    int count;
    double sum;
    double mean;
    double maxval;
    double minval;
};

struct value get_array_values(double arr[], int n)
{
    struct value ret;
    ret.count = n;
    ret.sum = 0;
    ret.maxval = arr[0];
    ret.minval = arr[0];
    for (int i = 0; i < n; i++)
    {
        ret.maxval = ret.maxval > arr[i] ? ret.maxval : arr[i];
        ret.minval = ret.minval < arr[i] ? ret.minval : arr[i];
        ret.sum += arr[i];
    }
    ret.mean = ret.sum / n;
    return ret;
}

int main(void)
{
    double arr[] = {1, 2, 3, 4, 5};
    struct value ret = get_array_values(arr, sizeof(arr) / sizeof(arr[0]));
    printf("count:\t%d\nsum:\t%.2lf\n", ret.count, ret.sum);
    printf("mean:\t%.2lf\nmax:\t%.2lf\nmin:\t%.2lf\n", ret.mean, ret.maxval, ret.minval);
    return 0;
}

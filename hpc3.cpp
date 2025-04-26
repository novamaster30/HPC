
#include <iostream>
#include <omp.h>
#include <climits>
using namespace std;

void calculate_reductions(int arr[], int n) {
    int min_value = INT_MAX, max_value = INT_MIN, sum = 0;

    #pragma omp parallel for reduction(min: min_value) reduction(max: max_value) reduction(+: sum)
    for (int i = 0; i < n; i++) {
        min_value = min(min_value, arr[i]);
        max_value = max(max_value, arr[i]);
        sum += arr[i];
    }

    cout << "Minimum value: " << min_value << endl;
    cout << "Maximum value: " << max_value << endl;
    cout << "Sum: " << sum << endl;
    cout << "Average: " << (double)sum / n << endl;
}

int main() {
    int n;
    cout << "Enter total number of elements: ";
    cin >> n;

    int *arr = new int[n];
    cout << "Enter elements: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    calculate_reductions(arr, n);
}

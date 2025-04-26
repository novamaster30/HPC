//bubble sort


#include <iostream>
#include <omp.h>
using namespace std;

void pbs(int* arr, int n){
    for (int i=0; i<n; i++){
        int phase = i%2;
        #pragma omp parallel for
        for(int j=phase; j<n-1; j+=2){
            if (arr[j]>arr[j+1]){
                swap(arr[j],arr[j+1]);
            }
        }
    }
}

int main(){
    int n;
    cout<<"enter the no of elements: ";
    cin>>n;
    int* arr = new int[n];
    cout<<"enter elements: ";
    for(int i=0; i<n; i++){
        cin>>arr[i];
    }
    pbs(arr,n);
    cout<<"sorted array is: ";
    for(int i=0; i<n; i++){
        cout<<arr[i]<<" ";
    }
}

//merge sort

#include <iostream>
#include <omp.h>
using namespace std;

void merge(int* arr, int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    int* L = new int[n1], *R = new int[n2];
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int i = 0; i < n2; i++) R[i] = arr[m + 1 + i];
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
    delete[] L; delete[] R;
}

void mergeSort(int* arr, int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        #pragma omp parallel sections
        {
            #pragma omp section
            mergeSort(arr, l, m);
            #pragma omp section
            mergeSort(arr, m + 1, r);
        }
        merge(arr, l, m, r);
    }
}

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;
    int* arr = new int[n];
    cout << "Enter elements:\n";
    for (int i = 0; i < n; cin >> arr[i++]);
    
    double start = omp_get_wtime();
    mergeSort(arr, 0, n - 1);
    double end = omp_get_wtime();

    cout << "Sorted array: ";
    for (int i = 0; i < n; cout << arr[i++] << " ");
    cout << "\nTime: " << end - start << " sec\n";

    delete[] arr;
    return 0;
}
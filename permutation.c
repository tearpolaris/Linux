#include <stdio.h>

void buble_sort(int arr[], int n);
void swap(int arr[], int i, int j);
void print_arr(int arr[], int n);
int permutation(int arr[], int n);
void inverse (int arr[], int x, int y);

int main() {
    int i, k, n;
    int arr[10];
  
    printf("Input n: ");
    scanf("%d",&n);

    for (int i=0; i<n;i++) {
        printf("Input element %d: ", i+1);
        scanf("%d", &arr[i]);
    }

    //print_arr(arr,n);
    buble_sort(arr, n);
    //print_arr(arr,n);
    do {
        print_arr(arr,n);
    }
    while (permutation(arr,n));
    //permutation(arr,n);
    //print_arr(arr,n);
    //permutation(arr,n);
    //print_arr(arr,n);
    //permutation(arr,n);
    //print_arr(arr,n);


 }

void buble_sort(int arr[], int n) {
    for (int i = 0; i < n;i++) {
        unsigned int sorted = 0;
        for (int j = 0 ; j < (n-i-1);j++) {
            if (arr[j+1] < arr[j]) {
                swap(arr, j, j+1);
                sorted = 1;
            }
        }
        if (sorted == 0) {
            break; 
        }
   }
}

void swap(int arr[], int i, int j) {
    int temp; 
    temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
    //printf("i: %d and j: %d\n",arr[i], arr[j]);
}

void inverse(int arr[], int x, int y) {
    while (x <y) {
        swap(arr, x, y);
        x++;
        y--;
    }
}


//****************************//
//   Function: permutation    //
//****************************//
int permutation (int arr[], int n) {
    int inv = -1;
    int ret = 0;
    for (int i=0; i < n; i++) {
        if (arr[i] < arr[i+1]) {
            inv = i;
        }
    }
  
    if (inv != -1) {
        for (int i=n-1; i>inv; i--) {
            if (arr[inv] < arr[i]) {
                swap(arr, inv, i);
                break;
            }
        }
       inverse(arr, inv+1, n-1);
       ret = 1;
    }
    else {
       ret = 0;
    }
    return ret;
}

void print_arr (int arr[], int n) {
    for (int i=0; i<n;i++) {
        printf ("%d ", arr[i]);
    } 
    printf("\n");
}

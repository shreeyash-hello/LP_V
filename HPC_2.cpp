#include <iostream>
#include <vector>
#include <chrono>
#include <omp.h>

using namespace std;

// Function to perform Bubble Sort
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Function to perform Parallel Bubble Sort
void parallelBubbleSort(vector<int>& arr) {
    int n = arr.size();
    bool swapped;

    #pragma omp parallel shared(arr, swapped)
    {
        do {
            swapped = false;

            #pragma omp for
            for (int i = 0; i < n - 1; i++) {
                if (arr[i] > arr[i + 1]) {
                    swap(arr[i], arr[i + 1]);
                    swapped = true;
                }
            }

            #pragma omp barrier
        } while (swapped);
    }
}

// Function to perform Merge Sort
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> leftArr(n1), rightArr(n2);

    for (int i = 0; i < n1; i++) {
        leftArr[i] = arr[left + i];
    }

    for (int i = 0; i < n2; i++) {
        rightArr[i] = arr[mid + 1 + i];
    }

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

// Function to perform Parallel Merge Sort
void parallelMergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            {
                parallelMergeSort(arr, left, mid);
            }

            #pragma omp section
            {
                parallelMergeSort(arr, mid + 1, right);
            }
        }

        merge(arr, left, mid, right);
    }
}

// Function to print the elements of an array
void printArray(const vector<int>& arr) {
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
}

int main() {
    int size;
    cout << "Enter the size of the array: ";
    cin >> size;

    vector<int> arr(size);
    cout << "Enter the elements of the array: ";
    for (int i = 0; i < size; i++) {
        cin >> arr[i];
    }

    // Sequential Bubble Sort
    vector<int> seqBubbleArr(arr);
    auto startSeqBubble = chrono::steady_clock::now();
    bubbleSort(seqBubbleArr);
    auto endSeqBubble = chrono::steady_clock::now();
    chrono::duration<double> seqBubbleTime = endSeqBubble - startSeqBubble;

    cout << "Sequential Bubble Sort:" << endl;
    cout << "Sorted array: ";
    printArray(seqBubbleArr);
    cout << "Time taken: " << seqBubbleTime.count() << " seconds" << endl;

    // Parallel Bubble Sort
    vector<int> parBubbleArr(arr);
    auto startParBubble = chrono::steady_clock::now();
    parallelBubbleSort(parBubbleArr);
    auto endParBubble = chrono::steady_clock::now();
    chrono::duration<double> parBubbleTime = endParBubble - startParBubble;

    cout << "Parallel Bubble Sort:" << endl;
    cout << "Sorted array: ";
    printArray(parBubbleArr);
    cout << "Time taken: " << parBubbleTime.count() << " seconds" << endl;

    // Sequential Merge Sort
    vector<int> seqMergeArr(arr);
    auto startSeqMerge = chrono::steady_clock::now();
    mergeSort(seqMergeArr, 0, size - 1);
    auto endSeqMerge = chrono::steady_clock::now();
    chrono::duration<double> seqMergeTime = endSeqMerge - startSeqMerge;

    cout << "Sequential Merge Sort:" << endl;
    cout << "Sorted array: ";
    printArray(seqMergeArr);
    cout << "Time taken: " << seqMergeTime.count() << " seconds" << endl;

    // Parallel Merge Sort
    vector<int> parMergeArr(arr);
    auto startParMerge = chrono::steady_clock::now();
    parallelMergeSort(parMergeArr, 0, size - 1);
    auto endParMerge = chrono::steady_clock::now();
    chrono::duration<double> parMergeTime = endParMerge - startParMerge;

    cout << "Parallel Merge Sort:" << endl;
    cout << "Sorted array: ";
    printArray(parMergeArr);
    cout << "Time taken: " << parMergeTime.count() << " seconds" << endl;

    return 0;
}

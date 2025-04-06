#include <pthread.h>
#include <iostream>
using namespace std;

int *arr = nullptr;

void* run(void* arg) {
    int index = *(int*)arg;
    int oldVal = arr[index];

    if (index % 2 == 0) {
        arr[index] = arr[index] * arr[index] * arr[index];
    } else {
      arr[index] = -arr[index];
    }

    delete (int*)arg;
    return nullptr;
}

int main(int argc, char* argv[]) {
    if (argc == 1) {
        cerr << "No integers provided" << endl;
        return 1;
    }

    int n = argc - 1;
    arr = new int[n];
    pthread_t* threads = new pthread_t[n];

    for (int i = 0; i < n; i++) {
        arr[i] = atoi(argv[i + 1]);
    }

    for (int i = 0; i < n; i++) {
        int* index = new int(i);
        pthread_create(&threads[i], nullptr, run, index);
    }

    for (int i = 0; i < n; i++) {
        pthread_join(threads[i], nullptr);
    }

    for (int i = 0; i < n; i++) {
        cout << "arr[" << i << "](" << atoi(argv[i + 1]) 
        << ") has been replaced with arr[" << i << "](" 
        << arr[i] << ")" << endl;
    }

    delete[] arr;
    delete[] threads;
    return 0;
}
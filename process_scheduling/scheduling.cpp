#include <iostream>
#include <fstream>
#include <utility>
using namespace std;

void FCFS();
void SJF();
void SRTF();
void P();
void RR();

void count_sort(int array[][3]);

string line;
ifstream input("input.txt");
ofstream output("output.txt");
int test;
int process_cnt;
int q;
int arrival, burst, priority;
int time_elapsed = 0;
int cpu_time = 0;

int main()
{
    input >> line;
    int tests = atoi(line.c_str());

    for (test = 1; test <= tests; test++)
    {
        string algo;
        string meta[2];
        time_elapsed = 0;
        cpu_time = 0;

        output << test << endl;

        input >> meta[0] >> algo;
        process_cnt = atoi(meta[0].c_str());
        if (algo == "RR")
        {
            input >> meta[1];
            q = atoi(meta[1].c_str());
        }

        string process_inputs[3];
        int processes[process_cnt][3];
        for (int p = 1; p <= process_cnt; p++)
        {
            input >> process_inputs[0] >> process_inputs[1] >> process_inputs[2];
            arrival = atoi(process_inputs[0].c_str());
            burst = atoi(process_inputs[1].c_str());
            priority = atoi(process_inputs[2].c_str());
            processes[p - 1][0] = arrival;
            processes[p - 1][1] = burst;
            processes[p - 1][2] = priority;
        }

        // sort arrival time
        count_sort(processes);

        // if (algo == "FCFS")
        //     FCFS();
        // else if (algo == "SJF")
        //     SJF();
        // else if (algo == "SRTF")
        //     SRTF();
        // else if (algo == "P")
        //     P();
        // else if (algo == "RR")
        //     RR();
    }

    input.close();
    output.close();
    return 0;
}

void FCFS() {
};
void SJF() {
};
void SRTF() {
};
void P() {
};
void RR() {
};

// https://www.geeksforgeeks.org/counting-sort/
void count_sort(int inputArray[][3])
{
    int N = process_cnt;

    // Finding the maximum element of array inputArray[].
    int M = 0;

    for (int i = 0; i < N; i++)
        M = max(M, inputArray[i][0]);

    // Initializing countArray[] with 0
    int countArray[M + 1] = {0};

    // Mapping each element of inputArray[] as an index
    // of countArray[] array
    for (int i = 0; i < N; i++)
        countArray[inputArray[i][0]]++;

    // Calculating prefix sum at every index
    // of array countArray[]
    for (int i = 1; i <= M; i++)
        countArray[i] += countArray[i - 1];

    // Creating outputArray[] from countArray[] array
    int outputArray[N][3];

    for (int i = N - 1; i >= 0; i--)
    {
        outputArray[countArray[inputArray[i][0]] - 1][0] = inputArray[i][0];
        outputArray[countArray[inputArray[i][0]] - 1][1] = inputArray[i][1];
        outputArray[countArray[inputArray[i][0]] - 1][2] = inputArray[i][2];

        countArray[inputArray[i][0]]--;
    }

    // Copy outputArray to inputArray
    for (int i = N - 1; i >= 0; i--)
    {
        inputArray[i][0] = outputArray[i][0];
        inputArray[i][1] = outputArray[i][1];
        inputArray[i][2] = outputArray[i][2];
    }
}
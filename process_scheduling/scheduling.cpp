#include <iostream>
#include <fstream>
#include <utility>
using namespace std;

void FCFS(int processes[][4]);
void SJF(int processes[][4]);
void SRTF(int processes[][4]);
void P(int processes[][4]);
void RR(int processes[][4]);

void count_sort(int array[][4]);

string line;
ifstream input("input.txt");
ofstream output("output.txt");

int test;
int q;

int process_cnt;
int arrival, burst, priority;

int time_elapsed = 0;
int cpu_time = 0;

int cpu_util = 0;
int throughput = 0;
int waiting_time = 0;
int turnaround_time = 0;
int response_time = 0;

int main()
{
    input >> line;
    int tests = atoi(line.c_str());

    for (test = 1; test <= tests; test++)
    {
        string algo;
        string meta[2]; // [process_cnt, q] as string
        time_elapsed = 0;
        cpu_time = 0;

        output << test << endl;

        input >> meta[0] >> algo;
        process_cnt = atoi(meta[0].c_str());
        int processes[process_cnt][4];
        if (algo == "RR")
        {
            input >> meta[1];
            q = atoi(meta[1].c_str());
        }

        string process_inputs[3];
        for (int p = 1; p <= process_cnt; p++)
        {
            input >> process_inputs[0] >> process_inputs[1] >> process_inputs[2];
            arrival = atoi(process_inputs[0].c_str());
            burst = atoi(process_inputs[1].c_str());
            priority = atoi(process_inputs[2].c_str());
            processes[p - 1][0] = p;
            processes[p - 1][1] = arrival;
            processes[p - 1][2] = burst;
            processes[p - 1][3] = priority;
        }

        // sort by arrival time
        count_sort(processes);
        for (int i = 0; i < process_cnt; i++)
        {
            cout << processes[i][0] << " " << processes[i][1] << " " << processes[i][2] << " " << processes[i][3] << endl;
        }
        cout << "--" << endl;

        if (algo == "FCFS")
            FCFS(processes);
        else if (algo == "SJF")
            SJF(processes);
        else if (algo == "SRTF")
            SRTF(processes);
        else if (algo == "P")
            P(processes);
        else if (algo == "RR")
            RR(processes);
    }

    input.close();
    output.close();
    return 0;
}

void FCFS(int processes[][4])
{
    for (int i = 1; i <= process_cnt; i++)
    {
        int index = processes[i][0];
        int arrival = processes[i][1];
        int burst = processes[i][2];
        int waiting = abs(arrival - time_elapsed);
        time_elapsed += burst + waiting;
        cpu_time += burst;
        output << time_elapsed << " " << index << " " << cpu_time << "X" << endl;
    }
};
void SJF(int processes[][4]) {
};
void SRTF(int processes[][4]) {
};
void P(int processes[][4]) {
};
void RR(int processes[][4]) {
};

// https://www.geeksforgeeks.org/counting-sort/
void count_sort(int inputArray[][4])
{
    int N = process_cnt;

    // Finding the maximum element of array inputArray[].
    int M = 0;

    for (int i = 0; i < N; i++)
        M = max(M, inputArray[i][1]);

    // Initializing countArray[] with 0
    int countArray[M + 1] = {0};

    // Mapping each element of inputArray[] as an index
    // of countArray[] array
    for (int i = 0; i < N; i++)
        countArray[inputArray[i][1]]++;

    // Calculating prefix sum at every index
    // of array countArray[]
    for (int i = 1; i <= M; i++)
        countArray[i] += countArray[i - 1];

    // Creating outputArray[] from countArray[] array
    int outputArray[N][4];

    for (int i = N - 1; i >= 0; i--)
    {
        outputArray[countArray[inputArray[i][1]] - 1][0] = inputArray[i][0];
        outputArray[countArray[inputArray[i][1]] - 1][1] = inputArray[i][1];
        outputArray[countArray[inputArray[i][1]] - 1][2] = inputArray[i][2];
        outputArray[countArray[inputArray[i][1]] - 1][3] = inputArray[i][3];

        countArray[inputArray[i][1]]--;
    }

    // Copy outputArray to inputArray
    for (int i = N - 1; i >= 0; i--)
    {
        inputArray[i][0] = outputArray[i][0];
        inputArray[i][1] = outputArray[i][1];
        inputArray[i][2] = outputArray[i][2];
        inputArray[i][3] = outputArray[i][3];
    }
}
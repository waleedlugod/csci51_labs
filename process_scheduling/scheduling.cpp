#include <iostream>
#include <fstream>
#include <utility>
using namespace std;

string line;
ifstream input("input.txt");
ofstream output("output.txt");

int test;
int q;

int process_cnt;
const int att_cnt = 7; // index, arrival, burst, priority, waiting, turnaround, response_time
int p_i, arrival, burst, priority;

int time_elapsed = 0;
int cpu_time = 0;

int cpu_util = 0;
int throughput = 0;
int waiting_time = 0;
int turnaround_time = 0;
int response_time = 0;

void FCFS(int processes[][att_cnt]);
void SJF(int processes[][att_cnt]);
void SRTF(int processes[][att_cnt]);
void P(int processes[][att_cnt]);
void RR(int processes[][att_cnt]);

void print_criteria(int processes[][att_cnt]);

void count_sort(int array[][att_cnt]);

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
        int processes[process_cnt][att_cnt] = {0};
        if (algo == "RR")
        {
            input >> meta[1];
            q = atoi(meta[1].c_str());
        }

        string process_inputs[3];
        for (int p = 1; p <= process_cnt; p++)
        {
            input >> process_inputs[0] >> process_inputs[1] >> process_inputs[2];
            processes[p - 1][0] = p;                               // index
            processes[p - 1][1] = atoi(process_inputs[0].c_str()); // arrival
            processes[p - 1][2] = atoi(process_inputs[1].c_str()); // burst
            processes[p - 1][3] = atoi(process_inputs[2].c_str()); // priority
        }

        // sort by arrival time
        count_sort(processes);
        // print processes
        // for (int i = 0; i < process_cnt; i++)
        // {
        //     cout << processes[i][0] << " " << processes[i][1] << " " << processes[i][2] << " " << processes[i][3] << endl;
        // }
        // cout << "--" << endl;

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

        print_criteria(processes);
    }

    input.close();
    output.close();
    return 0;
}

void FCFS(int processes[][att_cnt])
{
    for (int i = 0; i < process_cnt; i++)
    {
        p_i = processes[i][0];
        arrival = processes[i][1];
        burst = processes[i][2];

        time_elapsed = max(time_elapsed, arrival);        // 0 if arrived before
        processes[i][4] = max(0, time_elapsed - arrival); // waiting time
        processes[i][6] = processes[i][4];                // response time

        output << time_elapsed << " " << p_i << " " << burst << "X" << endl;

        cpu_time += burst;
        time_elapsed += burst;
        processes[i][5] = time_elapsed - arrival; // turnaround time
    }
};
void SJF(int processes[][att_cnt]) {
};
void SRTF(int processes[][att_cnt]) {
};
void P(int processes[][att_cnt]) {
};
void RR(int processes[][att_cnt]) {
};

void print_criteria(int processes[][att_cnt])
{
}

// https://www.geeksforgeeks.org/counting-sort/
// sorts based on arrival time
void count_sort(int inputArray[][att_cnt])
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
    int outputArray[N][att_cnt];

    for (int i = N - 1; i >= 0; i--)
    {
        for (int att = 0; att < att_cnt; att++)
        {
            outputArray[countArray[inputArray[i][1]] - 1][att] = inputArray[i][att];
        }
        countArray[inputArray[i][1]]--;
    }

    // Copy outputArray to inputArray
    for (int i = N - 1; i >= 0; i--)
    {
        for (int att = 0; att < att_cnt; att++)
        {
            inputArray[i][att] = outputArray[i][att];
        }
    }
}
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
const int att_cnt = 8; // index, arrival, burst, priority, remaining, waiting, turnaround, response_time
int p_i, arrival, burst, priority;

int time_elapsed = 0;
int cpu_time = 0;

void FCFS(int processes[][att_cnt]);
void SJF(int processes[][att_cnt]);
void SRTF(int processes[][att_cnt]);
void P(int processes[][att_cnt]);
void RR(int processes[][att_cnt]);

void print_criteria(int processes[][att_cnt]);

void count_sort(int array[][att_cnt], int sort_att);

int main()
{
    input >> line;
    int tests = atoi(line.c_str());

    for (test = 1; test <= tests; test++)
    {
        string algo;
        string buffer;
        time_elapsed = 0;
        cpu_time = 0;

        output << test << endl;

        input >> buffer >> algo;
        process_cnt = atoi(buffer.c_str());
        int processes[process_cnt][att_cnt] = {0};
        if (algo == "RR")
        {
            input >> buffer;
            q = atoi(buffer.c_str());
        }

        string process_inputs[3];
        for (int p = 1; p <= process_cnt; p++)
        {
            input >> process_inputs[0] >> process_inputs[1] >> process_inputs[2];
            processes[p - 1][0] = p;                               // index
            processes[p - 1][1] = atoi(process_inputs[0].c_str()); // arrival
            processes[p - 1][2] = atoi(process_inputs[1].c_str()); // burst
            processes[p - 1][3] = atoi(process_inputs[2].c_str()); // priority
            processes[p - 1][4] = atoi(process_inputs[1].c_str()); // remaining
        }

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

        // sort by index
        count_sort(processes, 0);
        print_criteria(processes);
    }

    input.close();
    output.close();
    return 0;
}

void FCFS(int processes[][att_cnt])
{
    // sort by arrival time
    count_sort(processes, 1);
    for (int i = 0; i < process_cnt; i++)
    {
        p_i = processes[i][0];
        arrival = processes[i][1];
        burst = processes[i][2];

        time_elapsed = max(time_elapsed, arrival);        // 0 if arrived before
        processes[i][5] = max(0, time_elapsed - arrival); // waiting time
        processes[i][7] = processes[i][5];                // response time

        output << time_elapsed << " " << p_i << " " << burst << "X" << endl;

        cpu_time += burst;
        time_elapsed += burst;
        processes[i][6] = time_elapsed - arrival; // turnaround time
    }
};
void SJF(int processes[][att_cnt])
{
    // sort by arrival time
    count_sort(processes, 1);

    // print processes
    for (int i = 0; i < process_cnt; i++)
    {
        cout << processes[i][0] << " " << processes[i][1] << " " << processes[i][2] << " " << processes[i][3] << endl;
    }
    cout << "--" << endl;
};
void SRTF(int processes[][att_cnt]) {
};
void P(int processes[][att_cnt]) {
};
void RR(int processes[][att_cnt]) {
};

void print_criteria(int processes[][att_cnt])
{
    char buffer[50];

    int cpu_util = 0;
    float throughput = 0;
    int waiting_time = 0;
    int turnaround_time = 0;
    int response_time = 0;

    // cpu utilization
    cpu_util = (cpu_time * 100) / (float)time_elapsed;
    sprintf(buffer, "CPU Utilization: %i%%", cpu_util);
    output << buffer << endl;

    // throughput
    throughput = process_cnt / (float)time_elapsed;
    sprintf(buffer, "Throughput: %.2f processes/ns", throughput);
    output << buffer << endl;

    // waiting time
    int total_waiting = 0;
    output << "Waiting Time:" << endl;
    for (int i = 0; i < process_cnt; i++)
    {
        total_waiting += processes[i][5];
        sprintf(buffer, "\tProcess %i: %ins", processes[i][0], processes[i][5]);
        output << buffer << endl;
    }
    float avg_waiting = total_waiting / (float)process_cnt;
    sprintf(buffer, "Average waiting time: %.2fns", avg_waiting);
    output << buffer << endl;

    // turnaround time
    int total_turnaround = 0;
    output << "Turnaround Time:" << endl;
    for (int i = 0; i < process_cnt; i++)
    {
        total_turnaround += processes[i][6];
        sprintf(buffer, "\tProcess %i: %ins", processes[i][0], processes[i][6]);
        output << buffer << endl;
    }
    float avg_turnaround = total_turnaround / (float)process_cnt;
    sprintf(buffer, "Average turnaround time: %.2fns", avg_turnaround);
    output << buffer << endl;

    // response time
    int total_response = 0;
    output << "Response Time:" << endl;
    for (int i = 0; i < process_cnt; i++)
    {
        total_response += processes[i][7];
        sprintf(buffer, "\tProcess %i: %ins", processes[i][0], processes[i][7]);
        output << buffer << endl;
    }
    float avg_response = total_response / (float)process_cnt;
    sprintf(buffer, "Average response time: %.2fns", avg_response);
    output << buffer << endl;
}

// https://www.geeksforgeeks.org/counting-sort/
// sorts based on sort_att
void count_sort(int inputArray[][att_cnt], int sort_att)
{
    int N = process_cnt;

    // Finding the maximum element of array inputArray[].
    int M = 0;

    for (int i = 0; i < N; i++)
        M = max(M, inputArray[i][sort_att]);

    // Initializing countArray[] with 0
    int countArray[M + 1] = {0};

    // Mapping each element of inputArray[] as an index
    // of countArray[] array
    for (int i = 0; i < N; i++)
        countArray[inputArray[i][sort_att]]++;

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
            outputArray[countArray[inputArray[i][sort_att]] - 1][att] = inputArray[i][att];
        }
        countArray[inputArray[i][sort_att]]--;
    }

    // Copy outputArray[] to inputArray[]
    for (int i = N - 1; i >= 0; i--)
    {
        for (int att = 0; att < att_cnt; att++)
        {
            inputArray[i][att] = outputArray[i][att];
        }
    }
}
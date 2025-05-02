#include <iostream>
#include <fstream>
#include <utility>
#include <queue>
using namespace std;

string line;
ifstream input("input.txt");
ofstream output("output.txt");

int test;
int quantum;

int process_cnt;
const int att_cnt = 8; // index, arrival, burst, priority, remaining, waiting, turnaround, response_time

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
            quantum = atoi(buffer.c_str());
        }

        string process_inputs[3];
        for (int p = 1; p <= process_cnt; p++)
        {
            input >> process_inputs[0] >> process_inputs[1] >> process_inputs[2];
            processes[p - 1][0] = p;                               // index
            processes[p - 1][1] = atoi(process_inputs[0].c_str()); // arrival
            processes[p - 1][2] = atoi(process_inputs[1].c_str()); // burst
            processes[p - 1][3] = atoi(process_inputs[2].c_str()); // priority
            processes[p - 1][4] = processes[p - 1][2];             // remaining
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
        int p_i = processes[i][0];
        int arrival = processes[i][1];
        int burst = processes[i][2];

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
    int completed_processes = 0;
    while (completed_processes < process_cnt)
    {
        // find shortest job of arrived processes
        int min_job_idx = -1;
        int i = 0;
        while (i < process_cnt && processes[i][1] <= time_elapsed)
        {
            // if process has remaining work
            if (processes[i][4] > 0)
            {
                if (min_job_idx == -1)
                    min_job_idx = i;
                // update index for shortest job
                else if (processes[i][2] < processes[min_job_idx][2])
                {
                    min_job_idx = i;
                }
            }
            i++;
        }

        if (min_job_idx != -1)
        {
            int i = min_job_idx;
            int p_i = processes[i][0];
            int arrival = processes[i][1];
            int burst = processes[i][2];

            processes[i][4] = 0;                              // clear remaining
            processes[i][5] = max(0, time_elapsed - arrival); // waiting time
            processes[i][7] = processes[i][5];                // response time

            output << time_elapsed << " " << p_i << " " << burst << "X" << endl;

            cpu_time += burst;
            time_elapsed += burst;
            processes[i][6] = time_elapsed - arrival; // turnaround time
            completed_processes++;
        }
        else
        {
            time_elapsed++;
        }
    }
};

void SRTF(int processes[][att_cnt])
{
    // sort by arrival time
    count_sort(processes, 1);
    int completed_processes = 0;
    char buffer[10];
    int min_job_idx = -1;
    int work_done = 0;
    int block_start = 0;
    while (completed_processes < process_cnt)
    {
        // find shortest job of arrived processes
        int i = 0;
        int prev_min_job_idx = min_job_idx;
        while (i < process_cnt && processes[i][1] <= time_elapsed)
        {
            // if process has remaining work
            if (processes[i][4] > 0)
            {
                if (min_job_idx == -1)
                    min_job_idx = i;
                // update index for shortest remaining
                else if (processes[i][4] < processes[min_job_idx][4])
                {
                    min_job_idx = i;
                }
            }
            i++;
        }

        // if a running process is interrupted
        if (prev_min_job_idx != -1 && prev_min_job_idx != min_job_idx)
        {
            output << buffer << endl;
            work_done = 0;
            block_start = time_elapsed;
        }

        if (min_job_idx != -1)
        {
            int i = min_job_idx;
            int p_i = processes[i][0];
            int arrival = processes[i][1];
            int burst = processes[i][2];
            int remaining = processes[i][4];

            if (processes[i][4] == processes[i][2]) // if this is first response
            {
                processes[i][7] = max(0, time_elapsed - arrival); // response time
            }

            work_done++;
            sprintf(buffer, "%i %i %i", block_start, p_i, work_done);
            processes[i][4]--; // decrement remaining

            if (processes[i][4] <= 0) // if process is complete
            {
                processes[i][6] = time_elapsed + 1 - arrival; // turnaround time
                processes[i][5] = processes[i][6] - burst;    // waiting time
                output << buffer << "X" << endl;
                completed_processes++;
                work_done = 0;
                block_start = time_elapsed;
                min_job_idx = -1;
            }

            cpu_time++;
        }
        time_elapsed++;
    }
};

void P(int processes[][att_cnt])
{
    // sort by arrival time
    count_sort(processes, 1);
    int completed_processes = 0;
    char buffer[10];
    int max_prio_idx = -1;
    int work_done = 0;
    int block_start = 0;
    while (completed_processes < process_cnt)
    {
        // find highest priority of arrived processes
        int i = 0;
        int prev_max_prio_idx = max_prio_idx;
        while (i < process_cnt && processes[i][1] <= time_elapsed)
        {
            // if process has remaining work
            if (processes[i][4] > 0)
            {
                if (max_prio_idx == -1)
                    max_prio_idx = i;
                else if (
                    // get higher priority
                    (processes[i][3] > processes[max_prio_idx][3]) ||
                    // get shortest burst if priorities are equal
                    // if bursts are equal, keep current, which arrived earlier
                    (processes[i][3] == processes[max_prio_idx][3] && processes[i][2] < processes[max_prio_idx][2]))
                {
                    max_prio_idx = i;
                }
            }
            i++;
        }

        // if a running process is interrupted
        if (prev_max_prio_idx != -1 && prev_max_prio_idx != max_prio_idx)
        {
            output << buffer << endl;
            work_done = 0;
            block_start = time_elapsed;
        }

        if (max_prio_idx != -1)
        {
            int i = max_prio_idx;
            int p_i = processes[i][0];
            int arrival = processes[i][1];
            int burst = processes[i][2];
            int remaining = processes[i][4];

            if (processes[i][4] == processes[i][2]) // if this is first response
            {
                processes[i][7] = max(0, time_elapsed - arrival); // response time
            }

            work_done++;
            sprintf(buffer, "%i %i %i", block_start, p_i, work_done);
            processes[i][4]--; // decrement remaining

            if (processes[i][4] <= 0) // if process is complete
            {
                processes[i][6] = time_elapsed + 1 - arrival; // turnaround time
                processes[i][5] = processes[i][6] - burst;    // waiting time
                output << buffer << "X" << endl;
                completed_processes++;
                work_done = 0;
                block_start = time_elapsed + 1;
                max_prio_idx = -1;
            }

            cpu_time++;
        }
        time_elapsed++;
    }
};

void RR(int processes[][att_cnt])
{

    // sort by arrival time
    count_sort(processes, 1);
    queue<int> p_queue;
    queue<int> end_queue; // worked processes which are added to end of queue
    bool in_queue[process_cnt] = {false};
    int completed_processes = 0;
    char buffer[10];

    while (completed_processes < process_cnt)
    {
        // add arrived processes to queue
        int i = 0;
        while (i < process_cnt && processes[i][1] <= time_elapsed)
        {
            if (!in_queue[i])
            {
                p_queue.push(i);
                in_queue[i] = true;
            }
            i++;
        }

        // add processes from previous quantum cycle to end of queue
        while (!end_queue.empty())
        {
            int p = end_queue.front();
            end_queue.pop();
            p_queue.push(p);
        }

        int quantum_work = quantum;
        while (quantum_work > 0 && !p_queue.empty())
        {
            int p = p_queue.front();
            p_queue.pop();

            int p_i = processes[p][0];
            int i_remainder = processes[p][4];

            // if first resonse; remainder == burst
            if (processes[p][4] == processes[p][2])
            {
                // response time = time elapsed - arrival
                processes[p][7] = time_elapsed - processes[p][1];
                // update waiting time
                processes[p][5] = processes[p][7];
            }

            // remove remainder from quantum
            quantum_work = max(0, quantum_work - processes[p][4]);
            // update remainder
            processes[p][4] = max(0, processes[p][4] - quantum);

            int work_done = i_remainder - processes[p][4];
            sprintf(buffer, "%i %i %i", time_elapsed, p_i, work_done);
            output << buffer;

            cpu_time += work_done;
            time_elapsed += work_done;

            // if process is compelete
            if (processes[p][4] <= 0)
            {
                // turnaround
                processes[p][6] = time_elapsed - processes[p][1];

                completed_processes++;
                output << "X";
            }
            else
                end_queue.push(p);

            output << endl;
        }

        // update waiting times
        queue<int> t_queue = p_queue;
        while (!t_queue.empty())
        {
            int p = t_queue.front();
            t_queue.pop();
            processes[p][5] += quantum;
        }

        // if no work was done
        if (quantum == quantum_work)
            time_elapsed += quantum;
    }
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
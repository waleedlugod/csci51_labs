#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

void FCFS();
void SJF();
void SRTF();
void P();
void RR();

string line;
ifstream input("input.txt");
ofstream output("output.txt");
int process_cnt;
int q;
int arrival, burst, priority;
string process[3];

int main()
{
    getline(input, line);
    int tests = atoi(line.c_str());

    for (int test = 1; test <= tests; test++)
    {
        getline(input, line);
        stringstream ss(line);

        string algo;
        string meta[2];

        ss >> meta[0] >> algo;
        process_cnt = atoi(meta[0].c_str());
        if (algo == "RR")
        {
            ss >> meta[1];
            q = atoi(meta[1].c_str());
        }

        if (algo == "FCFS")
            FCFS();
        else if (algo == "SJF")
            SJF();
        else if (algo == "SRTF")
            SRTF();
        else if (algo == "P")
            P();
        else if (algo == "RR")
            RR();
    }

    input.close();
    output.close();
    return 0;
}

void FCFS()
{
    for (int p = 1; p <= process_cnt; p++)
    {
        getline(input, line);
        stringstream ss(line);
        ss >> process[0] >> process[1] >> process[2];
        arrival = atoi(process[0].c_str());
        burst = atoi(process[1].c_str());
        priority = atoi(process[2].c_str());
    }
};
void SJF()
{
    for (int p = 1; p <= process_cnt; p++)
    {
        getline(input, line);
        stringstream ss(line);
        ss >> process[0] >> process[1] >> process[2];
        arrival = atoi(process[0].c_str());
        burst = atoi(process[1].c_str());
        priority = atoi(process[2].c_str());
    }
};
void SRTF()
{
    for (int p = 1; p <= process_cnt; p++)
    {
        getline(input, line);
        stringstream ss(line);
        ss >> process[0] >> process[1] >> process[2];
        arrival = atoi(process[0].c_str());
        burst = atoi(process[1].c_str());
        priority = atoi(process[2].c_str());
    }
};
void P()
{
    for (int p = 1; p <= process_cnt; p++)
    {
        getline(input, line);
        stringstream ss(line);
        ss >> process[0] >> process[1] >> process[2];
        arrival = atoi(process[0].c_str());
        burst = atoi(process[1].c_str());
        priority = atoi(process[2].c_str());
    }
};
void RR()
{
    for (int p = 1; p <= process_cnt; p++)
    {
        getline(input, line);
        stringstream ss(line);
        ss >> process[0] >> process[1] >> process[2];
        arrival = atoi(process[0].c_str());
        burst = atoi(process[1].c_str());
        priority = atoi(process[2].c_str());
    }
};

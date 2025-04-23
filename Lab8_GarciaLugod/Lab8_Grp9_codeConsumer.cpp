#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <fstream>
#include <cstring>
#include <unistd.h>
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("Not enough arguments\n");
        return 1;
    }

    // Flags for initializing shared memory
    int init_flags = 0666;

    // -- Semaphore initialization (match4s producer) --
    key_t sem_key = 1111;
    int sem_id = semget(sem_key, 1, init_flags);
    if (sem_id == -1)
    {
        perror("Could not access semaphore");
        return 1;
    }

    // -- Semaphore operations --
    struct sembuf sem_enter[2];
    struct sembuf sem_exit[1];

    sem_enter[0].sem_num = 0;
    sem_enter[0].sem_op = 0;
    sem_enter[0].sem_flg = SEM_UNDO;

    sem_enter[1].sem_num = 0;
    sem_enter[1].sem_op = 1;
    sem_enter[1].sem_flg = SEM_UNDO | IPC_NOWAIT;

    sem_exit[0].sem_num = 0;
    sem_exit[0].sem_op = -1;
    sem_exit[0].sem_flg = SEM_UNDO | IPC_NOWAIT;

    int op_res;

    // -- Shared memory segment A (data buffer) --
    key_t shm_main_key = 2222;
    int shm_main_size = atoi(argv[2]);
    int shm_main_id = shmget(shm_main_key, shm_main_size, init_flags);
    if (shm_main_id == -1)
    {
        perror("Could not access main shared memory");
        return 1;
    }

    char *shm_main = (char *)shmat(shm_main_id, NULL, 0);
    if ((int *)shm_main == (int *)-1)
    {
        perror("Could not attach to main shared memory");
        return 1;
    }

    // -- Shared memory segment B (status) --
    key_t shm_state_key = 3333;
    int shm_state_size = 1;
    int shm_state_id = shmget(shm_state_key, shm_state_size, init_flags);
    if (shm_state_id == -1)
    {
        perror("Could not access state shared memory");
        return 1;
    }

    char *shm_state = (char *)shmat(shm_state_id, NULL, 0);
    if ((int *)shm_state == (int *)-1)
    {
        perror("Could not attach to state shared memory");
        return 1;
    }

    // -- Output file --
    ofstream ofs(argv[1], ios::out | ios::trunc);
    if (!ofs.is_open())
    {
        perror("Could not open output file");
        return 1;
    }

    while (true)
    {
        op_res = semop(sem_id, sem_enter, 2);
        if (op_res == 0)
        {
            char state = shm_state[0];

            if (state == 'W') // Producer has written data
            {
                ofs.write(shm_main, strlen(shm_main));
                ofs.flush();
                printf("Read \"%s\" from shared memory\n", shm_main);

                // Set status to R (read)
                strcpy(shm_state, "R");
            }
            else if (state == 'F') // Producer has finished
            {
                ofs.write(shm_main, strlen(shm_main));
                ofs.flush();
                printf("Final read and exiting: \"%s\"\n", shm_main);
                break;
            }

            op_res = semop(sem_id, sem_exit, 1);
            if (op_res == -1)
            {
                perror("Error exiting semaphore");
                return 1;
            }
            else
            {
                sleep(1);
            }
        }
        else
        {
            perror("Error entering semaphore");
            return 1;
        }
    }

    ofs.close();
    return 0;
}

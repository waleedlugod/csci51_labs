#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <fstream>
#include <sstream>
#include <cstring>
#include <unistd.h>
using namespace std;

#include <iostream>

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("Not enough arguments\n");
        return 1;
    }

    // -- Text buffer initialization --
    ifstream ifs(argv[1]);
    stringstream ss;
    ss << ifs.rdbuf();
    string text = ss.str();

    // Flags for initializing semaphore and shared memory
    int init_flags = IPC_CREAT | 0666;

    // -- Semaphore initialization --
    key_t sem_key = 1111;
    int sem_id = semget(sem_key, 1, init_flags);
    if (sem_id == -1)
    {
        perror("Could not initialize semaphore");
        return 1;
    }

    // -- Semaphore accessing --
    struct sembuf sem_enter[2]; // Struct to enter semaphore
    struct sembuf sem_exit[1];  // Struct to exit semaphore

    // Wait for semaphore control
    sem_enter[0].sem_num = 0;
    sem_enter[0].sem_op = 0;
    sem_enter[0].sem_flg = SEM_UNDO;

    // Start semaphore control
    sem_enter[1].sem_num = 0;
    sem_enter[1].sem_op = 1;
    sem_enter[1].sem_flg = SEM_UNDO | IPC_NOWAIT;

    // End semaphore control
    sem_exit[0].sem_num = 0;
    sem_exit[0].sem_op = -1;
    sem_exit[0].sem_flg = SEM_UNDO | IPC_NOWAIT;

    // Result of semaphore operation
    int op_res;

    // -- Shared memory main initialization --
    key_t shm_main_key = 2222;
    int shm_main_size = atoi(argv[2]);
    int shm_main_id = shmget(shm_main_key, shm_main_size, init_flags);
    if (shm_main_id == -1)
    {
        perror("Could not initialize main shared memory");
        return 1;
    }
    char *shm_main = (char *)shmat(shm_main_id, NULL, 0);
    if ((int *)shm_main == (int *)-1)
    {
        perror("Could not attach to main shared memory");
        return 1;
    }

    // -- Shared memory state initialization --
    // I = initial, no text written
    // W = written to shared memory
    // R = shared memory is read
    // F = finished writing all file contents
    key_t shm_state_key = 3333;
    int shm_state_size = 1;
    int shm_state_id = shmget(shm_state_key, shm_state_size, init_flags);
    if (shm_state_id == -1)
    {
        perror("Could not initialize state shared memory");
        return 1;
    }
    char *shm_state = (char *)shmat(shm_state_id, NULL, 0);
    if ((int *)shm_state == (int *)-1)
    {
        perror("Could not attach to state shared memory");
        return 1;
    }
    strcpy(shm_state, "I");

    int text_idx = 0;
    while (text_idx < text.length())
    {
        // Enter semaphore
        op_res = semop(sem_id, sem_enter, 2);
        if (op_res == 0)
        {
            // Get state
            char *state;
            strcpy(state, shm_state);

            // Get buffer text
            string substr = text.substr(text_idx, shm_main_size);
            const char *buffer = substr.c_str();

            if (*state == 'R' || *state == 'I')
            {
                // Write to shared memory
                strcpy(shm_main, buffer);
                printf("Wrote \"%s\" to shared memory\n", buffer);

                if (text_idx + shm_main_size < text.length())
                    strcpy(shm_state, "W"); // Written state
                else
                {
                    strcpy(shm_state, "F"); // Done state
                    printf("Finished writing file contents\n");
                }
                text_idx += shm_main_size;
            }
            else
                printf("Waiting for shared memory to be read (text: \"%s\")\n", buffer);

            // Exit semaphore
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
    return 0;
}
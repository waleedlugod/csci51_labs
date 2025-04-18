#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

#include <cstdio>
#include <cstring>
using namespace std;

int main(int argc, char *argv[])
{
    // -- Semaphore initialization --
    key_t sem_key = IPC_PRIVATE;
    int sem_flag = IPC_CREAT | 0666;
    int sem_id = semget(sem_key, 1, sem_flag);
    if (sem_id == -1)
    {
        perror("Could not initialize semaphore.");
        return 1;
    }

    // -- Semaphore accessing --
    struct sembuf sema[2];

    // Wait for semaphore control
    sema[0].sem_num = 0;
    sema[0].sem_op = 0;
    sema[0].sem_flg = SEM_UNDO;

    // Start semaphore control
    sema[1].sem_num = 0;
    sema[1].sem_op = 1;
    sema[1].sem_flg = SEM_UNDO | IPC_NOWAIT;

    int op_res = semop(sem_id, sema, 2);

    if (op_res != -1)
    {

        // End semaphore control
        sema[0].sem_num = 0;
        sema[0].sem_op = -1;
        sema[0].sem_flg = SEM_UNDO | IPC_NOWAIT;

        op_res = semop(sem_id, sema, 1);
        if (op_res == -1)
        {
            perror("Error exiting semaphore");
            return 1;
        }
        else
            printf("success\n");
    }
    else
    {
        perror("Error entering semaphore");
        return 1;
    }
    return 0;
}
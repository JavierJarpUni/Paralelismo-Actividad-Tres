#include <iostream>
#include <vector>
#include <thread>
#include <semaphore.h>
#include <fcntl.h>
#include <unistd.h>

const int NUM_THREADS = 5;
const int ITERACIONES = 1000;
const char *SEMAPHORE_NAME = "/mi_semaforo";

int variableCompartida = 0;
sem_t *semaforo;

void incrementarVariable()
{
    for (int i = 0; i < ITERACIONES; ++i)
    {
        if (sem_wait(semaforo) == -1)
        {
            perror("sem_wait error");
            exit(EXIT_FAILURE);
        }
        variableCompartida++;
        if (sem_post(semaforo) == -1)
        {
            perror("sem_post error");
            exit(EXIT_FAILURE);
        }
    }
}

int main()
{
    sem_unlink(SEMAPHORE_NAME);

    semaforo = sem_open(SEMAPHORE_NAME, O_CREAT | O_EXCL, 0666, 1);
    if (semaforo == SEM_FAILED)
    {
        perror("sem_open error");
        return 1;
    }

    std::vector<std::thread> hilos(NUM_THREADS);
    for (int i = 0; i < NUM_THREADS; ++i)
    {
        hilos[i] = std::thread(incrementarVariable);
    }

    for (int i = 0; i < NUM_THREADS; ++i)
    {
        hilos[i].join();
    }

    std::cout << "Valor final de la variable compartida: " << variableCompartida << std::endl;

    if (sem_close(semaforo) == -1)
    {
        perror("sem_close error");
    }
    if (sem_unlink(SEMAPHORE_NAME) == -1)
    {
        perror("sem_unlink error");
    }

    return 0;
}
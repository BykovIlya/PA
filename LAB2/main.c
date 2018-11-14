//
// Created by ilya on 11/14/18.
//

#include <stdio.h>
#include <unistd.h> //pipe
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <sys/timeb.h>

double findPi(unsigned i, unsigned n, unsigned k);
double currentTime();

int main() {
    unsigned n;     // число слагаемых
    unsigned k;     // число процессов
    int fd[2];      // в fd[0] будет занесен файловый дескриптор, соответствующий выходному
                    // потоку данных pip'a и позволяющий выполнять только операцию чтения
                    // в fd[1] будет занесен файловый дескриптор, соответствующий входному
                    // потоку данных и позволяющий выполнять только операцию записи.
    const double PI = 3.1415926535;
  //  n = 1000000000;
  //  for (k = 1; k <= 25; k++) {
    printf("Введи количество слагаемых: ");
    scanf("%d", &n);
    printf("Введи количество процессов: ");
    scanf("%d", &k);
    pid_t processes[k]; // массив процессов

    if (pipe(fd) < 0) {
        printf("\nОшибка при вызове pipe()\n");
        exit(EXIT_FAILURE);
    }
    double begin = currentTime();
    for (int i = 0; i < k; i++) {
        processes[i] = fork();
        switch (processes[i]) {
            case 0: {
                close(fd[0]);
                double res = findPi(i, n, k);
                write(fd[1], &res, sizeof(double));
                close(fd[1]);
                exit(EXIT_SUCCESS);
            }
            case -1: {
                printf("\nОшибка при создании процесса # %d\n", i);
                exit(EXIT_FAILURE);
            } break;
            default: {
          //      printf("Процесс %d с pid: %d\n", i, processes[i]);
            } break;
        }
    }
    for (int i = 0; i < k; ++i) {
        int status;
        waitpid(processes[i], &status, 0);
        if (status == -1) {
            printf("Ошибка при ожидании дочернего процесса %d", processes[i]);
            exit(EXIT_FAILURE);
        }
    }
    double result = 0.0;
    double tmp = 0.0;
    for (int i = 0; i < k; ++i) {
        read(fd[0], &tmp, sizeof(double));
        result += tmp;
    }
    double end = currentTime();
    double time_spent = (end - begin);
    printf("Время: %.5f\n", time_spent);
    printf("Ответ: %.10f\nПогрешность: %.10f\n", result, fabs(result - PI));
    //}
    return 0;
}

/*
 * Фунция нахождения частичных сумм числа пи для заданного процесса.
 * Входные данные: k - кол-во процессов; n - кол-во слагаемых; i - текуший процесс
 * Возвращает: число пи
 */
double findPi(unsigned i, unsigned n, unsigned k) {
    double pi = 0.0;
    double addend = 0.0;
    for (int j = n * i / k + 1; j  <= n * (i + 1) / k; j++) {
        if ( j % 2 == 1) {
            addend = 4.0 / (2.0 * j - 1.0);
        } else {
            addend = -4.0 / (2.0 * j - 1.0);
        }
        pi += addend;
    }
    return pi;
}

double currentTime() {
    struct timeb tmb;
    ftime(&tmb);
    return (double) tmb.time * 1000 + tmb.millitm;
}

//
// Created by ilya on 11/14/18.
//

#include "header.h"

int main() {
    pid_t pid;
    printProcess(1);                // выводим родительский процесс 1
    /*
     * pid_t fork() -   Возвращает 0 в дочернем процессе, идентификатор
     *                  дочернего процесса – в родительском, –1 в случае ошибки
     */
    pid = fork();
    if (pid == 0) {
        printProcess(2);
        pid = fork();
        if (pid == 0) {
            printProcess(3);
            pid = fork();
            if (pid == 0) {
                printProcess(4);
                pid = fork();
            } else if (pid > 0) {
                wait(NULL);
            } else {
                printError(4);
            }
        } else if (pid > 0) {
            wait(NULL);
        } else {
            printError(3);
        }
    } else if (pid > 0) {
        wait(NULL);
    } else {
        printError(2);
    }
}


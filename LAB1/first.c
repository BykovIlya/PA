/*lr1. 1st processes. Bykov Ilya 6383*/
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
        printProcess(2);            // выводим дочерний процесс 2
        pid = fork();
        if (pid == 0) {
            printProcess(3);         // выводим дочерний процесс 3
        } else if (pid > 0) {
            pid = fork();
            if (pid == 0) {
                printProcess(4);    // выводим дочерний процесс 4
            } else if (pid > 0) {
                wait(NULL);         // ожидаем завершение дочернего процесса
            } else {
                printError(4);      // если pid отрицательный, произошла ошибка
            }
        } else {
            printError(3);
        }
    } else if (pid > 0) {
        wait(NULL);
    } else {
        printError(2);
    }
}
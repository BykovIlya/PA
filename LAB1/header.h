//
// Created by ilya on 11/13/18.
//

#ifndef LAB1_HEADER_H
#define LAB1_HEADER_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>


void printProcess(int number) {
    printf("Process # %d with pid: %d and with ppid: %d\n", number, getpid(), getppid());
}

void printError(int number) {
    printf("Error with creating process # %d\n", number);
}

#endif //LAB1_HEADER_H

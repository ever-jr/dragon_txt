#include "term_helper.h"
#include <stdlib.h>
#include <stdio.h>

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#endif

void th_clear() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void th_stop() {
    printf("press any key to continue...");
#ifdef _WIN32
    _getch();
#else
    getchar();
#endif
}

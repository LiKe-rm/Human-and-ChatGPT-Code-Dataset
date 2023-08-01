#include <stdio.h>
#include <stdlib.h>
#include "snap7/snap7.h"

#define BUFFER_SIZE 256

void PrepareBuffer(uint8_t* buffer, int size) {
    for (int i = 0; i < size; i++) {
        buffer[i] = (uint8_t)i;
    }
}

void SysSleep(int millisec) {
    #ifdef WIN32
        Sleep(millisec);
    #else
        usleep(millisec * 1000);
    #endif
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s PassiveIP\n", argv[0]);
        return 1;
    }

    printf("snap7 library version: %s\n", Snap7LibraryVersion());

    TS7Partner Partner;
    Partner.StartTo(argv[1], 0x1002, 0, 0);

    while (Partner.Connected()) {
        uint8_t buffer[BUFFER_SIZE];
        PrepareBuffer(buffer, BUFFER_SIZE);
        Partner.BSend(buffer, BUFFER_SIZE);

        SysSleep(1000);
    }

    Partner.Stop();

    return 0;
}

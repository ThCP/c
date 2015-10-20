#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <unistd.h>


int main()
{
    const int SIZE = 4096; // size in bytes of shared memory object
    const char * name = "OS"; // name of the shared memory object

    // strings written in the shared memory
    const char * message_0 = "First message!";
    const char * message_1 = "Second message!";

    // shared memory file descriptor
    int shm_fd;
    // pointer to shared memory object
    void *p;

    shm_fd = shm_open()


    return 0;
}

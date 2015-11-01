/*
	ex6

*/

int mydup2 ( int oldfd, int newfd ) {

    if ( dup (oldfd) == -1) {
        fprintf(stderr, "Error: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    if ( oldfd == newfd ) {
        return newfd;
    } else {
        if ( dup (newfd) == -1) {
            fprintf(stderr, "Error: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
        close(newfd);
        newfd = dup(oldfd);
    }
    return newfd;
}


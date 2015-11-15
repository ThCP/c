/*
	ex6

	Create a function mydup2() able to give the same functionalities of the
	dup2(), but written using only the function dup().

	Riccardo Cappuzzo
	
	s231643

*/

int mydup2 ( int oldfd, int newfd ) {

    if ( dup (oldfd) == -1) { // oldfd is a bad file descriptor
        fprintf(stderr, "Error: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    if ( oldfd == newfd ) { // the fd's are the same
        return newfd;
    } else {
        if ( dup (newfd) == -1) { 
            fprintf(stderr, "Error: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
        close(newfd); // close the newfd passed as parameter
        newfd = dup(oldfd);
    }
    return newfd;
}


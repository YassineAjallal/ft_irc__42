#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netdb.h>
#include <cstdlib>
#include <unistd.h>

void	_bzero(void *ptr, size_t size) {

	if (ptr) {
		for (size_t i = 0; i < size; i++) {
			*((char *)ptr + i) = 0;
		}
	}
}

int main(int ac, char **av) {
    if (ac == 2) {
        struct addrinfo hints, *res;
        int socket_fd;
        char buff[2];

        _bzero(&hints, sizeof(hints));
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;

        if (getaddrinfo(NULL, av[1], &hints, &res)) {
            std::cerr << "Error: Couldn't acquire address info!" << std::endl;
            return 1;
        }
        std::cout << "Attacking Server...\n";
        // while (1) {

            socket_fd = socket(hints.ai_family, hints.ai_socktype, hints.ai_protocol);
                if (socket_fd == -1) {
            std::cerr << "Error: Socket creation has failed!" << std::endl;
            return 1;
            }

            connect(socket_fd, res->ai_addr, res->ai_addrlen);
            //send(socket_fd, "QUIT: zebi\r\n", 12, 0);
            //close(socket_fd);
        // }
        pause();
    } 
    else {
        std::cout << "USAGE: client port" << std::endl;
        return 1;
    }
}
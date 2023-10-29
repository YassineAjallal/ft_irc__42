#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netdb.h>
#include <cstdlib>
#include <fcntl.h>
#include <unistd.h>

struct addrinfo hints, *res;

#define SPAM_CLIENT_SIZE 75

void	_bzero(void *ptr, size_t size) {

	if (ptr) {
		for (size_t i = 0; i < size; i++) {
			*((char *)ptr + i) = 0;
		}
	}
}

std::string generateRandomString(int length) {
    std::string result;
    for (int i = 0; i < length; ++i) {
        result += static_cast<char>(arc4random() + '0');
    }
    result += "\r\n";
    return result;
}

int    test_one() {
    std::cout << "TEST 1: Testing Multiple Clients." << std::endl;
    int sockets[SPAM_CLIENT_SIZE];
    for (int i = 0; i < SPAM_CLIENT_SIZE; i++) {
        sockets[i] = socket(AF_INET, SOCK_STREAM, 0);
        if (sockets[i] == -1) {
            std::cerr << "Error: Socket creation has failed!" << std::endl;
            exit(1);
        }
    }
    for (int i = 0; i < SPAM_CLIENT_SIZE; i++) {
        if (connect(sockets[i], res->ai_addr, res->ai_addrlen) == -1) {
            std::cerr << "Server can't withstand multiple clients!" << std::endl;
            return 1;
        }
    }
    for (int i = 0; i < SPAM_CLIENT_SIZE; i++)
        close(sockets[i]);
    std::cout << "TEST 1: PASSED V" << std::endl;
    sleep(1);
    return 0;
}

int test_two() {
    std::cout << "TEST 2: Testing Buffer Overflow." << std::endl;
    for (int i = 1; i < 9; i++) {
        std::cout << "Testing a buffer size of: " << i * 512 << std::endl;
        std::string rand_str = generateRandomString(512 * i);
        int sockets[SPAM_CLIENT_SIZE];
        for (int i = 0; i < SPAM_CLIENT_SIZE; i++) {
            sockets[i] = socket(AF_INET, SOCK_STREAM, 0);
            if (sockets[i] == -1) {
                std::cerr << "Error: Socket creation has failed!" << std::endl;
                exit(1);
            }
        }
        for (int i = 0; i < SPAM_CLIENT_SIZE; i++) {
            if (connect(sockets[i], res->ai_addr, res->ai_addrlen) == -1) {
                std::cerr << "Server Disconnected!" << std::endl;
                return 1;
            }
            if (send(sockets[i], rand_str.c_str(), rand_str.length(), 0) == -1) {
                std::cerr << "Server can't withstand Buffer size of: " << 512 * i << std::endl;
                return 1;
            }
        }
        for (int i = 0; i < SPAM_CLIENT_SIZE; i++)
            close(sockets[i]);
        sleep(1);
    }
    std::cout << "TEST 2: PASSED V" << std::endl;
    sleep(1);
    return 0;
}

int    test_three() {
    std::cout << "TEST 3: Joining Random Channels." << std::endl;
    int sockets[SPAM_CLIENT_SIZE];
    for (int i = 0; i < SPAM_CLIENT_SIZE; i++) {
        sockets[i] = socket(AF_INET, SOCK_STREAM, 0);
        if (sockets[i] == -1) {
            std::cerr << "Error: Socket creation has failed!" << std::endl;
            exit(1);
        }
    }
    for (int i = 0; i < SPAM_CLIENT_SIZE; i++) {
        std::string rand_str = generateRandomString(128);
        if (connect(sockets[i], res->ai_addr, res->ai_addrlen) == -1) {
            std::cerr << "Server can't withstand multiple clients!" << std::endl;
            return 1;
        }
        if (send(sockets[i], rand_str.c_str(), rand_str.length(), 0) == -1) {
            std::cerr << "Server Disconnected when joining random channels!\nCase: [" + rand_str + "]" << std::endl;
            return 1;
        }
    }
    for (int i = 0; i < SPAM_CLIENT_SIZE; i++)
        close(sockets[i]);
    std::cout << "TEST 3: PASSED V" << std::endl;
    sleep(1);
    return 0;
}


int    test_four() {
    std::cout << "TEST 4: Overloading Server With Clients." << std::endl;

    for (int i = 0; i * SPAM_CLIENT_SIZE < SPAM_CLIENT_SIZE * 10; i++) {
        std::cout << "Testing client count of: " << i * SPAM_CLIENT_SIZE << std::endl;
        int sockets[SPAM_CLIENT_SIZE * i];
        for (int j = 0; j < SPAM_CLIENT_SIZE * i; j++) {
            sockets[j] = socket(AF_INET, SOCK_STREAM, 0);
            if (sockets[j] == -1) {
                std::cerr << "Error: Socket creation has failed!" << std::endl;
                return 1;
            }
        }
        for (int j = 0; j < SPAM_CLIENT_SIZE * i; j++) {
            if (connect(sockets[j], res->ai_addr, res->ai_addrlen) == -1) {
                std::cerr << "Server Disconnected!" << std::endl;
                return 1;
            }
            std::string rand_str = generateRandomString(1024);
            if (send(sockets[j], rand_str.c_str(), rand_str.length(), 0) == -1) {
                std::cerr << "Server Closed Connection\nCase: [" << j << " Clients]" << std::endl;
                return 1;
            }
        }
        for (int j = 0; j < SPAM_CLIENT_SIZE * i; j++)
            close(sockets[j]);
        sleep(1);
    }
    std::cout << "TEST 4: PASSED V" << std::endl;
    sleep(1);
    return 0;
}

int    test_five() {
    std::cout << "TEST 5: testing random commands to crash the server." << std::endl;
    std::string cmds[9] = { "NICK", "JOIN", "WHO", "MODE", "PRIVMSG", "TOPIC", "INVITE", "KICK", "USER" };
    int socketfd[1000];
    for (int i = 0; i < 1000; i++) {
        socketfd[i] = socket(AF_INET, SOCK_STREAM, 0);
        if (socketfd[i] == -1) {
            std::cerr << "Error: Socket creation has failed!" << std::endl;
            return 1;
        }
        if (connect(socketfd[i], res->ai_addr, res->ai_addrlen) == -1) {
            std::cerr << "Server Disconnected!" << std::endl;
            return 1;
        }
        std::string buf = "NICK HvH" + generateRandomString(1024) + "\r\nUSER HvH 0 * :HvH\r\nPASS 0000\r\n";
        if (send(socketfd[i], buf.c_str(), buf.length(), 0) == -1) {
            std::cerr << "Server Closed Connection\nCase: [" << i << " Clients]" << std::endl;
            return 1;
        }
    }
    sleep(1);
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 1000; j++) {
            for (int k = 0; k + i < 9; k++) {
                std::string buf = cmds[k + i] + " " + generateRandomString(768) + "\r\n";
                if (send(socketfd[j], buf.c_str(), buf.length(), 0) == -1) {
                    std::cout << "Problem with command: [" << buf << "]" << std::endl;
                    return 1;
                }
            }
        }
    }

    for (int i = 0; i < 1000; i++) {
        close(socketfd[i]);
    }
    std::cout << "TEST 5: PASSED V" << std::endl;
    sleep(1);
    return 0;
}

int test_six() {
    std::cout << "TEST 6: Testing Server with empty commands." << std::endl;
    std::string cmds[9] = { "NICK", "JOIN", "WHO", "MODE", "PRIVMSG", "TOPIC", "INVITE", "KICK", "USER" };
    int socketfd[1000];
    for (int i = 0; i < 1000; i++) {
        socketfd[i] = socket(AF_INET, SOCK_STREAM, 0);
        if (socketfd[i] == -1) {
            std::cerr << "Error: Socket creation has failed!" << std::endl;
            return 1;
        }
        if (connect(socketfd[i], res->ai_addr, res->ai_addrlen) == -1) {
            std::cerr << "Server Disconnected!" << std::endl;
            return 1;
        }
        std::string buf = "NICK\r\nUSER\r\nPASS 0000\r\n";
        if (send(socketfd[i], buf.c_str(), buf.length(), 0) == -1) {
            std::cerr << "Server Closed Connection while logging in with empty credentials" << std::endl;
            return 1;
        }
        usleep(10);
    }
    sleep(1);
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 1000; j++) {
            for (int k = 0; k + i < 9; k++) {
                std::string buf = cmds[k + i] + "\r\n";
                if (cmds[k + i] == "KICK" || cmds[k + i] == "PRIVMSG" || cmds[k + i] == "TOPIC") {
                    if (j % 2 == 0)
                        buf = cmds[k + i] + "\r\n";
                    else
                        buf = cmds[k + i] + " "+ " :" + generateRandomString(128) + "\r\n";
                }
                if (send(socketfd[j], buf.c_str(), buf.length(), 0) == -1) {
                    std::cout << "Problem with command: [" << buf << "]" << std::endl;
                    return 1;
                }
            }
        }
    }
    for (int i = 0; i < 1000; i++) {
        close(socketfd[i]);
    }
    std::cout << "TEST 6: PASSED V" << std::endl;
    sleep(1);
    return 0;
}

int main(int ac, char **av) {
    if (ac == 2) {
        int    (*Tests[6])() = {&test_one, &test_two, &test_three, &test_four, &test_five, &test_six};
        _bzero(&hints, sizeof(hints));
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;

        if (getaddrinfo(NULL, av[1], &hints, &res)) {
            std::cerr << "Error: Couldn't acquire address info!" << std::endl;
            return 1;
        }
        std::cout << "Preforming Tests. Please Wait..." << std::endl;
        sleep(3);
        for (int i = 0; i < 6; i++)
            if ((*Tests[i])())
                std::cout << "Unfortuantely Test " << i + 1 << " Failed! Check the test case and make sure to handle it." << std::endl;
        // test_six();
    } 
    else {
        std::cout << "USAGE: client port" << std::endl;
        return 1;
    }
}

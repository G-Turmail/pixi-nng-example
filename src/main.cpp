#include <nng/nng.h>
#include <nng/protocol/pair0/pair.h>

#include <iostream>
#include <thread>
#include <chrono>
#include <string>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: main.exe [server|client]\n";
        return 1;
    }

    std::string mode = argv[1];
    bool isServer = (mode == "server");
    bool isClient = (mode == "client");

    if (!isServer && !isClient) {
        std::cout << "Invalid argument. Use 'server' or 'client'.\n";
        return 1;
    }

    const char* url = "tcp://127.0.0.1:5555";

    nng_socket sock;
    int rv;

    // Open pair0 socket
    if ((rv = nng_pair0_open(&sock)) != 0) {
        std::cerr << "Failed to open socket: " << nng_strerror(rv) << "\n";
        return 1;
    }

    // Setup connection
    if (isServer) {
        std::cout << "[SERVER] Listening on " << url << "\n";
        if ((rv = nng_listen(sock, url, nullptr, 0)) != 0) {
            std::cerr << "Listen error: " << nng_strerror(rv) << "\n";
            return 1;
        }
    } else {
        std::cout << "[CLIENT] Connecting to " << url << "\n";
        if ((rv = nng_dial(sock, url, nullptr, 0)) != 0) {
            std::cerr << "Dial error: " << nng_strerror(rv) << "\n";
            return 1;
        }
    }

    int counter = 0;

    while (true) {
        if (isServer) {
            // Server: receive first, then send
            char* buf = nullptr;
            size_t sz;

            rv = nng_recv(sock, &buf, &sz, NNG_FLAG_ALLOC);
            if (rv == 0) {
                std::string received(buf, sz);
                std::cout << "[SERVER] Received: " << received << "\n";
                nng_free(buf, sz);
            } else {
                std::cerr << "[SERVER] Receive error: " << nng_strerror(rv) << "\n";
            }

            std::string msg = "Reply from server #" + std::to_string(counter);
            if ((rv = nng_send(sock, (void*)msg.data(), msg.size(), 0)) != 0) {
                std::cerr << "[SERVER] Send error: " << nng_strerror(rv) << "\n";
            } else {
                std::cout << "[SERVER] Sent: " << msg << "\n";
            }
        } else {
            // Client: send first, then receive
            std::string msg = "Hello from client #" + std::to_string(counter);

            if ((rv = nng_send(sock, (void*)msg.data(), msg.size(), 0)) != 0) {
                std::cerr << "[CLIENT] Send error: " << nng_strerror(rv) << "\n";
            } else {
                std::cout << "[CLIENT] Sent: " << msg << "\n";
            }

            char* buf = nullptr;
            size_t sz;

            rv = nng_recv(sock, &buf, &sz, NNG_FLAG_ALLOC);
            if (rv == 0) {
                std::string received(buf, sz);
                std::cout << "[CLIENT] Received: " << received << "\n";
                nng_free(buf, sz);
            } else {
                std::cerr << "[CLIENT] Receive error: " << nng_strerror(rv) << "\n";
            }
        }

        counter++;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    nng_close(sock);
    return 0;
}
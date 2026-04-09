#include "pixinng.h"
#include <nng/nng.h>
#include <nng/protocol/pair0/pair.h>
#include <iostream>

namespace pixinng {

void hello_nng(const std::string& msg) {
    nng_socket sock;
    if (nng_pair0_open(&sock) != 0) return;
    const char* cmsg = msg.c_str();
    nng_send(sock, const_cast<char*>(cmsg), msg.size(), 0);
    nng_close(sock);
}

} // namespace pixinng
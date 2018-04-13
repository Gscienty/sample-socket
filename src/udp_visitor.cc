#include "udp_visitor.h"

namespace eys {
    udp_visitor::udp_visitor(address local, address remote, std::shared_ptr<connection> &conn, const char *buffer, const size_t buffer_size)
        : local(local)
        , buffer(const_cast<char *>(buffer))
        , remote(remote)
        , buffer_size(buffer_size)
        , seek(0)
        , conn(conn) {
    }

    udp_visitor &udp_visitor::operator>> (address &addr) {
        addr = remote;
        return (*this);
    }

    size_t udp_visitor::remainder() const {
        return this->buffer_size - this->seek;
    }

    udp_sender udp_visitor::send() {
        return udp_sender(this->conn);
    }

    int udp_visitor::get_fd() const {
        return this->conn->get_fd();
    }
}
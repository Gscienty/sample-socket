#ifndef _EYS_TCP_SENDER_
#define _EYS_TCP_SENDER_

#include "address.h"
#include "base_fd.h"
#include "serializer.h"

namespace eys {
    class tcp_sender : public base_fd {
    private:
        address remote;
    public:
        tcp_sender(address remote);
        tcp_sender(std::shared_ptr<connection> conn);
        tcp_sender(tcp_sender &&sender)
            : base_fd(sender)
            , remote(sender.remote) { }

        fd_type get_fd_type() const { return fd_type::fd_type_tcp_sender; }

        template <typename E = char, typename OP_serializer = serializer<E> >
        tcp_sender &operator<< (E e) {
            size_t size;
            std::unique_ptr<char> bytes(OP_serializer::serialize(e, size));
            sockaddr_in addr = this->remote.get();
            send(this->conn->get_fd(), bytes.get(), size + 1, 0);
            return (*this);
        }
    };
}

#endif
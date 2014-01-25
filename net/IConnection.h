#ifndef _I_CONNECTION_H_
#define _I_CONNECTION_H_


struct connection_id {
    int _fd;
    int _timestamp;

    bool operator!=(const connection_id& id) {
        return (id._fd != _fd || id._timestamp != _timestamp);
    }

    bool operator==(const connection_id& id) {
        return ((id._fd == _fd) && (id._timestamp == _timestamp));
    }
};


class io_handler {
    public:
        virtual int on_read() = 0;
        virtual int on_write() = 0;
        virtual int on_error() = 0;
};

class IConnection: public io_handler {
    public:
        virtual bool connected()=0;
        virtual int on_read() {
        }
        ;
        virtual int on_write() {
        }
        ;
        virtual int on_error() {
        }
        ;
        virtual int send_data(const char*, int)=0;

        virtual int get_connection_id()=0;
};

#endif

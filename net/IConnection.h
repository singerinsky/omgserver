#ifndef _I_CONNECTION_H_
#define _I_CONNECTION_H_
class io_handler {
public:
	virtual void on_read() = 0;
	virtual void on_write() = 0;
	virtual void on_error() = 0;
};

class IConnection: public io_handler {
public:
	virtual bool connected()=0;
	virtual void on_read() {
	}
	;
	virtual void on_write() {
	}
	;
	virtual void on_error() {
	}
	;
	virtual int send_data(const char*, int)=0;

	virtual int get_connection_id()=0;
};

#endif

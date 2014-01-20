#ifndef _I_CONNECTION_H_
#define _I_CONNECTION_H_
class IConnection{
	public:
		virtual bool connected()=0;
        virtual void on_read(int fd){};
        virtual void on_write(int fd){};
		virtual int  send_data(const char*,int)=0;

	public:
		virtual int get_connection_id()=0;
};

#endif

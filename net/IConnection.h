#ifndef _I_CONNECTION_H_
#define _I_CONNECTION_H_
class IConnection{
	public:
		virtual int sendData(const char*,int)=0;
		virtual bool connected()=0;
        virtual void on_read(int fd){};
        virtual void on_write(int fd){};

	public:
		virtual int getConnectionId()=0;
};

#endif

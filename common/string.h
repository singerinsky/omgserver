#ifndef _SFL_STRING_H_
#define _SFL_STRING_H_
#include "head.h"

#define SFLSTRING_COPY_FROM(str) copy_from(#str, sizeof(#str) - 1)

#pragma pack(push, 1)

namespace omg
{

class StringBuilder
{
public:
    StringBuilder(uint32_t total_len)
    {
        _total_len = total_len;
        _buffer = new char[_total_len];
        _len = 0;
    }

    ~StringBuilder(void)
    {
        delete[] _buffer;
        _buffer = NULL;
        _len = -1;
        _total_len = -1;
    }

    int append_char(char ch)
    {
        if (int(_total_len - _len) < 2)
        {
            return -1;
        }

        _buffer[_len] = ch;
        ++_len;
        _buffer[_len] = '\0';

        return 0;
    }

    int append(const char *str, int len)
    {
        if (int(_total_len - _len) < len + 1)
        {
            return -1;
        }

        memcpy(_buffer + _len, str, len + 1);
        _len += len;

        return 0;
    }

    int append_format(const char *fmt, ...)
    {
        char buf[1024];
        va_list arg;

        va_start(arg, fmt);
        int len = vsnprintf(buf, sizeof(buf), fmt, arg);
        va_end(arg);

        if (len == sizeof(buf) - 1)
        {
            return -1;
        }

        if (int(_total_len - _len) < len + 1)
        {
            return -1;
        }

        memcpy(_buffer + _len, buf, len + 1);
        _len += len;

        return 0;
    }

    inline const char *c_str(void) const
    {
        return _buffer;
    }

    inline uint32_t len(void) const
    {
        return _len;
    }

    char* get_buffer(){
	return _buffer;	
    }

private:
    uint32_t _total_len;
    uint32_t _len;
    char *_buffer;
};

class String
{
public:
    String(void)
    {
        _buffer = NULL;
        _len = 0;
        _dispose = false;
    }

    ~String(void)
    {
        dispose();
    }

    void set(char *str, uint32_t len, bool free_on_dispose)
    {
        dispose();

        _buffer = str;
        _len = len;
        _dispose = free_on_dispose;
    }

    void copy_from_to(const char *str, uint32_t len)
    {
    	_len += len;
    	char *rt = new char[sizeof(char) * (strlen(_buffer) + strlen(str))];
    	strcpy(rt, _buffer);
    	strcat(rt, str);

    	_buffer = rt;
    }

    void copy_from(const char *str, uint32_t len)
    {
        dispose();
        _len = len;
        _buffer = new char[_len + 1];
        _dispose = true;
        memcpy(_buffer, str, _len + 1);
    }

    void format(uint32_t buf_len, const char *fmt, ...)
    {
        dispose();
        _buffer = new char[buf_len];
        _dispose = true;
        va_list arg;
        va_start(arg, fmt);
        _len = vsnprintf(_buffer, buf_len, fmt, arg);
        va_end(arg);
    }

    void dispose(void)
    {
        if (_dispose && _buffer)
        {
            delete[] _buffer;
            _buffer = NULL;
        }
    }

    inline char *c_str(void) const
    {
        return _buffer;
    }

    inline uint32_t len(void) const
    {
        return _len;
    }

private:
    bool _dispose;
    uint32_t _len;
    char *_buffer;
};

} // namespace omg

#pragma pack(pop)

#endif /* _SFL_STRING_H_ */

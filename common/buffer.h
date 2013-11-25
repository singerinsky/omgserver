#ifndef _SFL_BUFFER_H_
#define _SFL_BUFFER_H_

namespace omg
{

// 手工释放的缓存区
struct ManualBuffer
{
    ManualBuffer(void)
    {
        buffer = NULL;
        this->size = 0;
    }

    ~ManualBuffer(void)
    {
        buffer = NULL;
        this->size = -1;
    }

    void bzero(void)
    {
        assert(buffer != NULL);

        memset(buffer, 0, this->size);
    }

    void copy_from(uint32_t dest, const char *src, uint32_t size)
    {
        assert(buffer != NULL);
        assert(dest + size <= this->size);

        memcpy(buffer + dest, src, size);
    }

    void copy_to(char *dest, uint32_t src, uint32_t size)
    {
        assert(buffer != NULL);
        assert(src + size <= this->size);

        memcpy(dest, buffer + src, size);
    }

    char *buffer;
    uint32_t size;
};

// 缓存区
class Buffer
{
public:
    Buffer(uint32_t size)
    {
        _init_size = size;
        _size = size;
        _buffer = new char[_size];
    }

    ~Buffer(void)
    {
        delete [] _buffer;
    }

    char *buffer(void)
    {
    	return _buffer;
    }

    inline const char *buffer(void) const
    {
    	return _buffer;
    }

    uint32_t size(void) const
    {
    	return _size;
    }

    void size(uint32_t size)
    {
        assert(_size <= _init_size);
        _size = size;
    }

    void bzero(void)
    {
        memset(_buffer, 0, _size);
    }

    void copy_from(uint32_t dest, const char *src, uint32_t size)
    {
        assert(dest + size <= _size);

        memcpy(_buffer + dest, src, size);
    }

    void copy_to(char *dest, uint32_t src, uint32_t size)
    {
        assert(src + size <= _size);

        memcpy(dest, _buffer + src, size);
    }

private:
    uint32_t _init_size;
    uint32_t _size;
    char *_buffer;
};

// 在堆空间分配的缓存块
template<uint32_t Size>
class AutoBuffer
{
public:
    AutoBuffer(void)
    {
    	_size = Size;
    }

    char *buffer(void)
    {
    	return _buffer;
    }

    const char *buffer(void) const
    {
    	return _buffer;
    }

    uint32_t size(void) const
    {
    	return _size;
    }

    void size(uint32_t size)
    {
        assert(_size <= Size);
        _size = size;
    }

    void bzero(void)
    {
        memset(_buffer, 0, _size);
    }

    void copy_from(uint32_t dest, const char *src, uint32_t size)
    {
        assert(dest + size <= _size);

        memcpy(_buffer + dest, src, size);
    }

    void copy_to(char *dest, uint32_t src, uint32_t size)
    {
        assert(src + size <= _size);

        memcpy(dest, _buffer + src, size);
    }

private:
    uint32_t _size;
    char _buffer[Size];
};

}

#endif /* _SFL_BUFFER_H_ */

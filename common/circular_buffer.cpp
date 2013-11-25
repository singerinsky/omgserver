#include "circular_buffer.h"

#include "head.h"

namespace omg
{

CircularBuffer::CircularBuffer(void)
{
}

CircularBuffer::~CircularBuffer(void)
{
    free();
}

void CircularBuffer::init(uint32_t size, bool zero)
{
    assert(_buffer.buffer == NULL);
    assert(size > 0);

    _buffer.size = size;
    _buffer.buffer = new char[_buffer.size];
    assert(_buffer.buffer);

    _rewind = _buffer.size;
    _data_length = _head = _tail = 0;

    if (zero)
    {
        _buffer.bzero();
    }
}

void CircularBuffer::free(void)
{
    if (_buffer.buffer != NULL)
    {
        delete[] _buffer.buffer;
        _buffer.buffer = NULL;
    }

    _data_length = _head = _tail = _rewind = -1;
}

int CircularBuffer::push(const char *buffer, uint32_t size)
{
    assert(size > 0);
    assert(buffer != NULL);

    if (_head >= _tail)
    {
        if (_head + size <= _buffer.size)
        {
            _buffer.copy_from(_head, buffer, size);
            _head += size;
            _data_length += size;
            return 0;
        }
        else if (size < _tail)
        {
            _buffer.copy_from(0, buffer, size);
            _rewind = _head;
            _head = size;
            _data_length += size;
            return 0;
        }
    }
    else if (_head < _tail)
    {
        if (_head + size < _tail)
        {
            _buffer.copy_from(_head, buffer, size);
            _head += size;
            _data_length += size;
            return 0;
        }
    }

    return -1;
}

int CircularBuffer::pop(char *buffer, uint32_t size)
{
    assert(size > 0);
    assert(buffer != NULL);

    if (_tail < _head)
    {
        if (_head - _tail >= size)
        {
            _buffer.copy_to(buffer, _tail, size);
            _tail += size;
            _data_length -= size;
            return 0;
        }
    }
    else if (_tail > _head)
    {
        if (_tail == _rewind)
        {
            if (size < _tail)
            {
                _buffer.copy_to(buffer, 0, size);
                _tail = size;
                _data_length -= size;
                return 0;
            }
        }
        else if (_rewind - _tail >= size)
        {
            _buffer.copy_to(buffer, _tail, size);
            _tail += size;
            _data_length -= size;
            return 0;
        }
        else
        {
            assert(false); // exceed _discard point
        }
    }

    return -1;
}

}

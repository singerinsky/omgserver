#ifndef _SFL_CIRCULAR_BUFFER_H_
#define _SFL_CIRCULAR_BUFFER_H_

#include "head.h"
#include "buffer.h"

#include "lock.h"

namespace omg
{

// 循环队列
class CircularBuffer
{
public:
    CircularBuffer(void);
    ~CircularBuffer(void);

    // 初始化
    void init(uint32_t size, bool zero = false);

    // 释放,析构用
    void free(void);

    // 加数据加入,-1为缓冲区满，0成功
    int push(const char *buffer, uint32_t size);

    // 读取数据，-1为缓冲区中没有足够的数据，0成功
    int pop(char *buffer, uint32_t size);

    // 读取指定大小的一块数据，但是不把它提取出来，需要保证缓冲区中有足够的数据
    char *peek(uint32_t size)
    {
        assert(size > 0);

        int diff = _head - _tail;
        if (diff == 0)
        {
            return NULL;
        }

        if (diff > 0)
        {
            if (diff >= (int)size)
            {
                return _buffer.buffer + _tail;
            }
        }
        else if (diff < 0)
        {
            int rewind_diff = _rewind - _tail;
            if (rewind_diff >= (int)size)
            {
                return _buffer.buffer + _tail;
            }
            else if (rewind_diff == 0)
            {
                if (size < _tail)
                {
                    return _buffer.buffer;
                }
            }
            else
            {
                assert(false); // exceed _discard point
            }
        }

        return NULL;
    }

    // 丢弃指定大小的数据块,-1为缓冲区中没有足够的数据，0成功
    inline int discard(uint32_t size)
    {
        assert(size > 0);

        if (_tail < _head)
        {
            if (_head - _tail >= size)
            {
                _tail += size;
                return 0;
            }
        }
        else if (_tail > _head)
        {
            if (_tail == _rewind)
            {
                if (size < _tail)
                {
                    _tail = size;
                    return 0;
                }
            }
            else if (_rewind - _tail >= size)
            {
                _tail += size;
                return 0;
            }
            else
            {
                assert(false); // exceed _discard point
            }
        }

        return -1;
    }

private:
    // 缓存块
    ManualBuffer _buffer;

    // 写入点
    volatile uint32_t _head;

    // 读取点
    volatile uint32_t _tail;

    // 回转点
    volatile uint32_t _rewind;

    //存入的数据长度
    volatile uint32_t _data_length;
};

}

#endif /* _SFL_CIRCULAR_BUFFER_H_ */

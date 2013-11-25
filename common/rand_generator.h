#ifndef _RAND_GENERATOR_H_
#define _RAND_GENERATOR_H_
#include <stdarg.h>
#include "mtrand.h"

class RandGenerator
{
    unsigned int _seed;

    static RandGenerator *_instance;

public:
    RandGenerator(void)
    {
        _seed = time(NULL);
    }

    unsigned int next_int(void)
    {
    	_seed++;
        return rand_r(&_seed);
    }

    double next_double(void)
    {
    	_seed++;
    	unsigned int new_seed =  rand_r(&_seed);
        return (double)rand_r(&new_seed) / RAND_MAX;
    }

    static RandGenerator *get_instance(void)
    {
        return _instance;
    }

    unsigned int get_number_from_array_by_random(int count, ...)
    {
        va_list ap; // 初始化指向可变参数列表的指针
        unsigned int num = 0;
        int index = next_int() % count;
        va_start(ap, count); // 将第一个可变参数的地址付给ap，即ap指向可变参数列表的开始
        for (int i = 0; i < (index + 1); ++i)
        {
        	num = va_arg(ap, int);
        }
        va_end(ap); // ap付值为0，没什么实际用处，主要是为程序健壮性
        return num;
    }

    int get_work_rate_value(int x)
    {
    	return (1. + (double)(x - 50) * 0.005) * 1000.;
    }
};

class MTRandWarpper{
private:
	MTRand_int32*	 _int_rand;
	MTRand*		 	 _double_rand;
	static MTRandWarpper*   _instance;
	MTRandWarpper(){
		unsigned long init[5] = {0x123, 0x234, 0x345, 0x456,0x452}, length = 5;
		_int_rand = new MTRand_int32(init,length);
		_double_rand = new MTRand();
	}

public:
	static MTRandWarpper* GetInstance(){
		if(_instance == NULL){
			_instance = new MTRandWarpper();
		}
		return _instance;
	}

	unsigned long get_rand_int(){
		return (*_int_rand)();
	}

	double get_rand_double(){
		return (*_double_rand)();
	}
};



#define RAND_INT MTRandWarpper::GetInstance()->get_rand_int()
#define RAND_DBL MTRandWarpper::GetInstance()->get_rand_double()
#define RAND_ARRAY(x, args...) RandGenerator::get_instance()->get_number_from_array_by_random(x, ##args)
#define NEW_WORK_RATE_VALUE(x) RandGenerator::get_instance()->get_work_rate_value(x)

#define MY_MAX(x,y)	x>y?x:y

#endif /* _RAND_GENERATOR_H_ */

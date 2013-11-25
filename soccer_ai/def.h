#ifndef _SFL_DEF_H_
#define _SFL_DEF_H_

namespace omg
{

#define DEFAULT_HASH_SIZE 64 * 1024
#define VERBOSE_SOCKET_LEVEL 11
#define VERBOSE_SIGNAL_LEVEL 12

#if __WORDSIZE == 64
    typedef uint64_t socket_id_t;
#else
    typedef uint32_t socket_id_t;
#endif

//just for the debug mode
#define _DEBUG_MODE_

#define LISNUM 10
#define MAXBUF 1024 * 32
#define MAXEPOLLSIZE 10000

}

#endif /* _SFL_DEF_H_ */

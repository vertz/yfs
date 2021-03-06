// lock protocol

#ifndef lock_protocol_h
#define lock_protocol_h

#include "rpc.h"

class lock_protocol {
 public:
  enum xxstatus { OK, RETRY, RPCERR, NOENT, IOERR };
  typedef int status;
  typedef unsigned long long lockid_t;
  enum rpc_numbers {
    acquire = 0x7001,
    release,
    stat
  };
};

enum lockstate_t{
    LOCKFREE = 0,
    LOCKED
};

struct lock_t{
    lockstate_t state;
    pthread_cond_t lock_cond;

    lock_t(): state(LOCKFREE)
    { 
        pthread_cond_init(&lock_cond,NULL);
    }
    
    ~lock_t()
    {
        pthread_cond_destroy(&lock_cond);
    }
};

#endif 

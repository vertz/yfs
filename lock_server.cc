// the lock server implementation

#include "lock_server.h"
#include <sstream>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>

lock_server::lock_server(): nacquire(0)
{
     pthread_mutex_init(&lock_server_mutex,NULL);
}

lock_server::~lock_server()
{
     pthread_mutex_destroy(&lock_server_mutex);
}

lock_protocol::status
lock_server::stat(int clt, lock_protocol::lockid_t lid, int &r)
{
    lock_protocol::status ret = lock_protocol::OK;
    printf("stat request from clt %d\n", clt);
    r = nacquire;
    return ret;
}

lock_protocol::status
lock_server::acquire(int clt, lock_protocol::lockid_t lid, int &r)
{
    lock_protocol::status ret = lock_protocol::OK;
        
    pthread_mutex_lock(&lock_server_mutex);
    
    while(locks_table[lid].state != LOCKFREE) 
        pthread_cond_wait(&locks_table[lid].lock_cond,&lock_server_mutex);

    locks_table[lid].state = LOCKED;           
    pthread_mutex_unlock(&lock_server_mutex);
                
    r = nacquire;
    return ret;
}

lock_protocol::status
lock_server::release(int clt, lock_protocol::lockid_t lid, int &r)
{
    lock_protocol::status ret = lock_protocol::OK;
    pthread_mutex_lock(&lock_server_mutex);
    
    if(locks_table[lid].state != LOCKED)
    {
        ret = lock_protocol::NOENT;
    }
    else
    {
        locks_table[lid].state = LOCKFREE;
        pthread_cond_signal(&locks_table[lid].lock_cond);
    }
        
    pthread_mutex_unlock(&lock_server_mutex);
    
    r = nacquire;
    return ret;
}



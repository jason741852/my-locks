/*
 * Afke Holgersen, etc.
 *
 * sync.h
 */

#ifndef _m_SYNC_H_
#define _m_SYNC_H_

#include "atomic_ops.h"

struct my_mutex_struct {
  volatile unsigned long locked; // 0 if available, 1 if true
  int count; //count how many times a certain thread has accessed the lock
  int threadID;
};


typedef struct my_mutex_struct my_mutex_t;


int my_mutex_init(my_mutex_t *lock);
int my_mutex_unlock(my_mutex_t *lock);
int my_mutex_destroy(my_mutex_t *lock);

int my_mutex_lock(my_mutex_t *lock);
int my_mutex_trylock(my_mutex_t *lock);



/*Spinlock Starts here*/

struct my_spinlock_struct {
  volatile unsigned long locked; // 0 if available, 1 if true
  int count; //count how many times a certain thread has accessed the lock
  int threadID;
};

typedef struct my_spinlock_struct my_spinlock_t;

int my_spinlock_init(my_spinlock_t *lock);
int my_spinlock_destroy(my_spinlock_t *lock);
int my_spinlock_unlock(my_spinlock_t *lock);

int my_spinlock_lockTAS(my_spinlock_t *lock);
int my_spinlock_lockTTAS(my_spinlock_t *lock);
int my_spinlock_trylock(my_spinlock_t *lock);


/*queuelock Starts here*/

struct my_queuelock_struct {
  int count;
  int threadID;
  volatile unsigned long next_ticket;
  volatile unsigned long now_serving; //queue head

};

typedef struct my_queuelock_struct my_queuelock_t;

int my_queuelock_init(my_queuelock_t *lock);
int my_queuelock_destroy(my_queuelock_t *lock);
int my_queuelock_unlock(my_queuelock_t *lock);

int my_queuelock_lock(my_queuelock_t *lock);
int my_queuelock_trylock(my_queuelock_t *lock);


#endif

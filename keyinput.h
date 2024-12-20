#ifndef KEYINPUT_H 
#define KEYINPUT_H

#include <stdio.h>
#include <windows.h>
#include <pthread.h>
#include <errno.h>

#define false 0
#define true 1

typedef char bool;

extern bool isRunning;

extern bool w_is_pressed;
extern bool a_is_pressed;
extern bool s_is_pressed;
extern bool d_is_pressed;
extern bool space_is_pressed;
extern bool c_is_pressed;
extern bool lshift_is_pressed;

extern pthread_mutex_t mtx_keyinput;
extern pthread_cond_t cv_keyinput;

extern int freq_ms;

void *keyInput(void *arg);
void *actions(void *arg);
void threadInit(pthread_t *thread, void *(*func)(void *));

#endif
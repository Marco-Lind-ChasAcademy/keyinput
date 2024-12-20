#include "keyinput.h"

int main() {
    pthread_t t_key, t_act;
    threadInit(&t_key, keyInput);
    threadInit(&t_act, actions);

    pthread_join(t_key, NULL);
    pthread_join(t_act, NULL);

    pthread_mutex_destroy(&mtx_keyinput);
    pthread_cond_destroy(&cv_keyinput);
    
    return 0;
}
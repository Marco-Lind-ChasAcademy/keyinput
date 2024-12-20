// Replace all puts() with game logic
// Use pthreads_create() is you prefer, otherwise threadInit(), which is a wrapper with standard initialization and error handling

#include "keyinput.h"

bool isRunning = true;

bool w_is_pressed = false;
bool a_is_pressed = false;
bool s_is_pressed = false;
bool d_is_pressed = false;
bool space_is_pressed = false;
bool c_is_toggled = false;
bool lshift_is_pressed = false;

pthread_mutex_t mtx_keyinput = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cv_keyinput = PTHREAD_COND_INITIALIZER;

int freq_ms = 50; // Edit this for update frequency

void *keyInput(void *arg) {
    while (isRunning) {
        Sleep(freq_ms);
        pthread_mutex_lock(&mtx_keyinput);
        if (GetAsyncKeyState('W')) {
            w_is_pressed = true;
        } else {
            w_is_pressed = false;
        }
        if (GetAsyncKeyState('A')) {
            a_is_pressed = true;
        } else {
            a_is_pressed = false;
        }
        if (GetAsyncKeyState('S')) {
            s_is_pressed = true;
        } else {
            s_is_pressed = false;
        }
        if (GetAsyncKeyState('D')) {
            d_is_pressed = true;
        } else {
            d_is_pressed = false;
        }
        if (GetAsyncKeyState(' ')) {
            space_is_pressed = true;
            Sleep(100 - freq_ms); // Just for console cleanliness - remove for real game
        } else {
            space_is_pressed = false;
        }
        if (GetAsyncKeyState('C')) {
            if (!c_is_toggled) {
                c_is_toggled = true;
                Sleep(200 - freq_ms);
            } else if (c_is_toggled) {
                c_is_toggled = false;
                Sleep(200 - freq_ms);
            }
        }
        if (GetAsyncKeyState(VK_LSHIFT)) {
            lshift_is_pressed = true;
        } else {
            lshift_is_pressed = false;
        }

        
        if (c_is_toggled && (lshift_is_pressed || space_is_pressed)) {
            c_is_toggled = false;
        } 
        
        pthread_cond_signal(&cv_keyinput);
        pthread_mutex_unlock(&mtx_keyinput);
    }
    return NULL;
}

void *actions(void *arg) {
    while (isRunning) {

        pthread_mutex_lock(&mtx_keyinput);
        pthread_cond_wait(&cv_keyinput, &mtx_keyinput);
        
        // Walking/Running/Sneaking
        if (w_is_pressed && a_is_pressed && s_is_pressed && d_is_pressed && lshift_is_pressed && c_is_toggled) {
            puts("Standing still");
        }
        
        else if (w_is_pressed && a_is_pressed && s_is_pressed && d_is_pressed && lshift_is_pressed) {
            puts("Standing still");
        }
        
        else if (w_is_pressed && a_is_pressed && s_is_pressed && d_is_pressed && c_is_toggled) {
            puts("Crouching");
        }
        
        else if (w_is_pressed && a_is_pressed && d_is_pressed && lshift_is_pressed && c_is_toggled) {
            puts("Walking forwards");
        } else if (s_is_pressed && a_is_pressed && d_is_pressed && lshift_is_pressed && c_is_toggled) {
            puts("Walking backwards");
        } else if (w_is_pressed && a_is_pressed && s_is_pressed && lshift_is_pressed && c_is_toggled) {
            puts("Walking left");
        } else if (w_is_pressed && s_is_pressed && d_is_pressed && lshift_is_pressed && c_is_toggled) {
            puts("Walking right");
        }
        
        else if (w_is_pressed && a_is_pressed && s_is_pressed && d_is_pressed) {
            puts("Standing still");
        }
        
        else if (a_is_pressed && w_is_pressed && c_is_toggled && lshift_is_pressed) {
            puts("Walking left and forwards");
        } else if (a_is_pressed && s_is_pressed && c_is_toggled && lshift_is_pressed) {
            puts("Walking left and backwards");
        } else if (d_is_pressed && w_is_pressed && c_is_toggled && lshift_is_pressed) {
            puts("Walking right and forwards");
        } else if (d_is_pressed && s_is_pressed && c_is_toggled && lshift_is_pressed) {
            puts("Walking right and backwards");
        }
        
        else if (w_is_pressed && a_is_pressed && d_is_pressed && lshift_is_pressed) {
            puts("Running forwards");
        } else if (s_is_pressed && a_is_pressed && d_is_pressed && lshift_is_pressed) {
            puts("Running backwards");
        } else if (a_is_pressed && w_is_pressed && s_is_pressed && lshift_is_pressed) {
            puts("Running left");
        } else if (d_is_pressed && w_is_pressed && s_is_pressed && lshift_is_pressed) {
            puts("Running right");
        }
        
        else if (w_is_pressed && d_is_pressed && a_is_pressed && c_is_toggled) {
            puts("Sneaking forwards");
        } else if (s_is_pressed && d_is_pressed && a_is_pressed && c_is_toggled) {
            puts("Sneaking backwards");
        } else if (w_is_pressed && a_is_pressed && s_is_pressed && c_is_toggled) {
            puts("Sneaking left");
        } else if (w_is_pressed && d_is_pressed && s_is_pressed && c_is_toggled) {
            puts("Sneaking right");
        }
        
        else if (a_is_pressed && w_is_pressed && c_is_toggled) {
            puts("Sneaking left and forwards");
        } else if (a_is_pressed && s_is_pressed && c_is_toggled) {
            puts("Sneaking left and backwards");
        } else if (d_is_pressed && w_is_pressed && c_is_toggled) {
            puts("Sneaking right and forwards");
        } else if (d_is_pressed && s_is_pressed && c_is_toggled) {
            puts("Sneaking right and backwards");
        }
        
        else if (w_is_pressed && lshift_is_pressed && c_is_toggled) {
            puts("Walking forwards");
        } else if (s_is_pressed && lshift_is_pressed && c_is_toggled) {
            puts("Walking backwards");
        } else if (a_is_pressed && lshift_is_pressed && c_is_toggled) {
            puts("Walking left");
        } else if (d_is_pressed && lshift_is_pressed && c_is_toggled) {
            puts("Walking right");
        }
        
        else if (w_is_pressed && s_is_pressed && c_is_toggled) {
            puts("Crouching");
        } else if (a_is_pressed && d_is_pressed && c_is_toggled) {
            puts("Crouching");
        }
        
        else if (a_is_pressed && w_is_pressed && lshift_is_pressed) {
            puts("Running left and forwards");
        } else if (a_is_pressed && s_is_pressed && lshift_is_pressed) {
            puts("Running left and backwards");
        } else if (d_is_pressed && w_is_pressed && lshift_is_pressed) {
            puts("Running right and forwards");
        } else if (d_is_pressed && s_is_pressed && lshift_is_pressed) {
            puts("Running right and backwards");
        }
        
        else if (a_is_pressed && w_is_pressed && d_is_pressed) {
            puts("Walking forwards");
        } else if (a_is_pressed && s_is_pressed && d_is_pressed) {
            puts("Walking backwards");
        } else if (a_is_pressed && w_is_pressed && s_is_pressed) {
            puts("Walking left");
        } else if (w_is_pressed && s_is_pressed && d_is_pressed) {
            puts("Walking right");
        }
        
        else if (a_is_pressed && d_is_pressed) {
            puts("Standing still");
        } else if (w_is_pressed && s_is_pressed) {
            puts("Standing still");
        } else if (lshift_is_pressed && c_is_toggled) {
            puts("Standing still");
        }
        
        else if (a_is_pressed && w_is_pressed) {
            puts("Walking left and forwards");
        } else if (d_is_pressed && w_is_pressed) {
            puts("Walking right and forwards");
        } else if (a_is_pressed && s_is_pressed) {
            puts("Walking left and backwards");
        } else if (d_is_pressed && s_is_pressed) {
            puts("Walking right and backwards");
        }
        
        else if (w_is_pressed && lshift_is_pressed) {
            puts("Running forwards");
        } else if (s_is_pressed && lshift_is_pressed) {
            puts("Running backwards");
        } else if (a_is_pressed && lshift_is_pressed) {
            puts("Running left");
        } else if (d_is_pressed && lshift_is_pressed) {
            puts("Running right");
        }
        
        else if (w_is_pressed && c_is_toggled) {
            puts("Sneaking forwards");
        } else if (s_is_pressed && c_is_toggled) {
            puts("Sneaking backwards");
        } else if (a_is_pressed && c_is_toggled) {
            puts("Sneaking left");
        } else if (d_is_pressed && c_is_toggled) {
            puts("Sneaking right");
        }
        
        else if (w_is_pressed) {
            puts("Walking forwards");
        } else if (s_is_pressed) {
            puts("Walking backwards");
        } else if (a_is_pressed) {
            puts("Walking left");
        } else if (d_is_pressed) {
            puts("Walking right");
        }
        
        else if (c_is_toggled) {
            puts("Crouching");
        }

        else {
            puts("Standing still");
        }
         

        
        // Jumping
        if (space_is_pressed) {
            puts("Jumped");
        }

        // Quit
        if (GetAsyncKeyState('Q')) {
            isRunning = false;
        }

        pthread_mutex_unlock(&mtx_keyinput);
    }
    return NULL;
}

void threadInit(pthread_t *thread, void *(*func)(void *)) {
    if (pthread_create(thread, NULL, func, NULL) != 0) {
        perror("Creating thread failed.");
        exit(EXIT_FAILURE);
    }
}
#ifndef CORE_H
#define CORE_H

typedef struct
{
    void*       hnd;
    int         width;
    int         height;
} st_window;

int st_init();
int st_cleanup();

#endif // CORE_H

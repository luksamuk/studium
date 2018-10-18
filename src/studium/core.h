#ifndef CORE_H
#define CORE_H

typedef struct
{
    void*       hnd;
    int         width;
    int         height;
} st_window;

void st_init();
void st_cleanup();

#endif // CORE_H

#ifndef DISPLAY_H
#define DISPLAY_H

typedef struct
{
    void*       hnd;
    int         width;
    int         height;
    double      last_time;
} st_window;

st_window st_create_window(int width, int height, const char* title);

#endif // DISPLAY_H

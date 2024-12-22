#pragma once

typedef struct
{
    int width;
    int height;
    char **canvas;
    char pen;
} Canvas;

Canvas *init_canvas(int width, int height, char pen);
void reset_canvas(Canvas *c);
void print_canvas(Canvas *c);
void free_canvas(Canvas *c);

void draw_line(Canvas *c, const int x0, const int y0, const int x1, const int y1);
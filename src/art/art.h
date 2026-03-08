/*
 * art.h - Animation abstraction for sl-2026
 *
 * Animations implement init/draw/cleanup callbacks.
 * draw() uses art_goto/art_puts to output without knowing
 * absolute coordinates or column clipping.
 */

#ifndef SL_ART_H
#define SL_ART_H

typedef struct animation {
    const char *name;
    int height;
    void *ctx;
    void (*init)(struct animation *a);
    void (*draw)(struct animation *a, int tick);
    void (*cleanup)(struct animation *a);
} animation;

/* Drawing API — set up by art_set_pos before each frame */
void art_set_pos(int start_y, int x, int maxcols);
void art_goto(int row);
void art_puts(const char *s);

/* Animation registry */
extern animation *animations[];
animation *get_animation(const char *name);

#endif

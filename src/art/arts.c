/*
 * art/arts.c - Animation registry
 */

#include "art.h"
#include <string.h>

extern animation sl_animation;
extern animation clawd_animation;

animation *animations[] = {
    &sl_animation,
    &clawd_animation,
    NULL
};

animation *get_animation(const char *name) {
    if (!name)
        return animations[0];
    for (int i = 0; animations[i]; i++)
        if (strcmp(animations[i]->name, name) == 0)
            return animations[i];
    return animations[0];
}

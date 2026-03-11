/*
 * art/ufo.c - Space Invaders mystery ship (UFO)
 *
 * Classic 16×7 pixel sprite, half-block encoded to 4 text rows.
 */

#include "art.h"
#include "../sl.h"

#define UFO_HEIGHT  4

static const char *ufo_art[UFO_HEIGHT] = {
    "   ▄▄██████▄▄   ",
    " ▄█▀██▀██▀██▀█▄ ",
    "▀▀████▀▀▀▀████▀▀",
    "   ▀▀      ▀▀   ",
};

static void ufo_init(animation *a) { (void)a; }

static void ufo_draw(animation *a, int tick) {
    (void)tick;
    for (int y = 0; y < UFO_HEIGHT; y++)
        art_putline(y, ufo_art[y]);
    putchar('\n');
}

static void ufo_cleanup(animation *a) { (void)a; }

animation ufo_animation = {
    .name    = "ufo",
    .height  = UFO_HEIGHT,
    .width   = 16,
    .init    = ufo_init,
    .draw    = ufo_draw,
    .cleanup = ufo_cleanup,
};

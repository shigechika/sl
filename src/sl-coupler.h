/*
 * sl-coupler.h - Coupler framework for sl-2026
 *
 * HOW TO ADD A NEW CAR
 *
 * 1. Create car-xxx.c with a constructor function:
 *
 *      #include "sl-coupler.h"
 *      static void xxx_init(coupler *cpl, int COLS, int LINES) { ... }
 *      static void xxx_frame(coupler *cpl, int COLS, int LINES, int x) { ... }
 *      static void xxx_cleanup(coupler *cpl, int COLS, int LINES) { ... }
 *      coupler xxx_coupler(void) {
 *          return (coupler){ .init = xxx_init, .frame = xxx_frame,
 *                            .cleanup = xxx_cleanup };
 *      }
 *
 *    - ctx: per-instance data pointer (malloc in init, free in cleanup)
 *    - init: called once before the animation loop
 *    - frame: called each frame after SL is drawn, before fflush
 *      - x: current SL position (decreasing from COLS toward 0)
 *    - cleanup: called once after the animation loop
 *    - Any callback may be NULL if not needed.
 *
 * 2. Declare the constructor in this header (below).
 *
 * 3. Register in sl-couplers.c under #ifdef CAR_XXX:
 *
 *      #ifdef CAR_XXX
 *          if (car_enabled("XXX", CAR_XXX))
 *              couplers[n_couplers++] = xxx_coupler();
 *      #endif
 *
 * 4. Add to SL2026_CARS in Makefile (NAME=1 for default on, =0 for off):
 *
 *      SL2026_CARS := NULL=1 XXX=1
 *
 *    This auto-generates -DCAR_XXX=1 and car-xxx.c from the entry.
 *
 * COMPILE-TIME DEFAULT
 *
 * The value of -DCAR_XXX sets the default: =1 enabled, =0 disabled.
 *
 * ENVIRONMENT
 *
 * SL_CAR_XXX overrides the compile-time default at runtime.
 * Set to "0" to disable, any other value to enable.
 */

#ifndef SL_COUPLER_H
#define SL_COUPLER_H

typedef struct coupler {
    void *ctx;
    void (*init)(struct coupler *cpl, int COLS, int LINES);
    void (*frame)(struct coupler *cpl, int COLS, int LINES, int x);
    void (*cleanup)(struct coupler *cpl, int COLS, int LINES);
} coupler;

#define MAX_COUPLERS 8

extern coupler couplers[MAX_COUPLERS];
extern int n_couplers;

void couple(void);
int car_enabled(const char *name, int dflt);
coupler null_coupler(void);

#endif

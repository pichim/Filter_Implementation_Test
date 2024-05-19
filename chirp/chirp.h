#pragma once

#include <math.h>
#include <stdbool.h>
#include <stdint.h>

#ifndef M_PIf
    #define M_PIf 3.14159265358979323846f /* pi */
#endif

typedef struct chirp_s {
    float f0, Ts, beta, k0, k1;
    uint32_t count, N;
    float exc, fchirp, sinarg;
    bool isFinished;
} chirp_t;

void chirpInit(chirp_t *chirp, const float f0, const float f1, const float t1, const float Ts);
void chirpReset(chirp_t *chirp);
void chirpResetSignals(chirp_t *chirp);
bool chirpUpdate(chirp_t *chirp);
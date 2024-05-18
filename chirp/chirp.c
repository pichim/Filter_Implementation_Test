#include <math.h>

#include "chirp.h"

// initialize the chirp signal generator
// f0: start frequency in Hz
// f1: end frequency in Hz
// t1: signal length in seconds
// Ts: sampling time in seconds
void chirpInit(chirp_t *chirp, const float f0, const float f1, const float t1, const float Ts)
{
    chirp->f0 = f0;
    chirp->Ts = Ts;
    chirp->N = (uint32_t)(t1 / Ts);
    chirp->beta = powf(f1 / f0, 1.0f / t1);
    chirp->k0 = 2.0f * M_PI / logf(chirp->beta);
    chirp->k1 = chirp->k0 * f0;
    chirpReset(chirp);
}

// reset the chirp signal generator fully
void chirpReset(chirp_t *chirp)
{
    chirp->count = 0;
    chirp->isFinished = false;
    chirpResetSignals(chirp);
}

// reset the chirp signal generator signals
void chirpResetSignals(chirp_t *chirp)
{
    chirp->exc = 0.0f;
    chirp->fchirp = 0.0f;
    chirp->sinarg = 0.0f;
}

// update the chirp signal generator
bool chirpUpdate(chirp_t *chirp)
{
    if (chirp->isFinished) {
        
        return false;

    } else if (chirp->count == chirp->N) {

        chirp->isFinished = true;
        chirpResetSignals(chirp);
        return false;

    } else {

        chirp->fchirp = chirp->f0 * powf(chirp->beta, (float)(chirp->count) * chirp->Ts);
        chirp->sinarg = chirp->k0 * chirp->fchirp - chirp->k1;
        chirp->sinarg = fmodf(chirp->sinarg, 2.0f * M_PI);
        chirp->exc = sinf(chirp->sinarg);
        chirp->count++;

        return true;
    }
}
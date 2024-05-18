#pragma once

#include <stdint.h>

#ifndef M_PI
    # define M_PI 3.14159265358979323846
#endif

class Chirp
{
public:
    Chirp() {};
    Chirp(const float f0, const float f1, const float t1, const float Ts);
    virtual ~Chirp() {};

    void init(const float f0, const float f1, const float t1, const float Ts);
    void reset();
    bool update();

    float getFreq() const;
    float getSinarg() const;
    float getExc() const;

private:
    struct ChripParams {
        float f0, Ts, beta, k0, k1;
        uint32_t count, N;
        float exc, fchirp, sinarg;
        bool isFinished;
    } chirp;

    void resetSignals();
};
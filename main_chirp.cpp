#include <iostream>
#include <fstream>
#include <iomanip>
#include <math.h>

#include "chirp_c.h"

#define TS 40.0e-6f

#define CHIRP_T1 5.0f
#define CHIRP_F0 (1.0f / CHIRP_T1)
#define CHIRP_F1 (1.0f / (2.0f * TS))
#define CHIRP_OFFSET 5.0f
#define CHIRP_AMPLITUDE 3.0f
#define CHIRP_T_SETTLE 0.0f

int main(int argc, char *argv[])
{
    chirp_t chirp_c;
    chirpInit(&chirp_c, CHIRP_F0, CHIRP_F1, CHIRP_T1, TS);

    std::ofstream ofs ("output/data.txt");

    uint64_t cntr = 0;

    float chirp_exc_c = 0.0f;
    float chirp_freq_c = 0.0f;
    float chirp_sinarg_c = 0.0f;

    float input_c = CHIRP_OFFSET;
    float input_c_previous = CHIRP_OFFSET;
    float diff_input_c = 0.0f;

    bool chirp_update_finished = false;

    while (true) {

        const float time = cntr++ * TS;

        if (time > CHIRP_T_SETTLE) {
            if (chirpUpdate(&chirp_c)) {
                chirp_exc_c = chirp_c.exc;
                chirp_freq_c = chirp_c.fchirp;
                chirp_sinarg_c = chirp_c.sinarg;

                input_c = CHIRP_AMPLITUDE * chirp_exc_c + CHIRP_OFFSET;

                diff_input_c = (input_c - input_c_previous) / TS;
                input_c_previous = input_c;
            } else {
                chirp_update_finished = true;
            }
        }

        if (chirp_update_finished)
            break;

        ofs  << std::setprecision(9) << std::scientific << time << ", "                                                            //  0
                                                        << chirp_exc_c << ", "                                                     //  1
                                                        << chirp_freq_c << ", "                                                    //  2
                                                        << chirp_sinarg_c << ", "                                                  //  3
                                                        << input_c << ", "                                                         //  4
                                                        << diff_input_c << std::endl;                                              //  5
    }

    ofs.close();

    return 0;
}

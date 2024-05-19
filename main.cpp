#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>

#include "Chirp.h"
#include "IIRFilter.h"

#include "chirp.h"
#include "iirfilter.h"

#define TS 50.0e-6f

#define CHIRP_T1 20.0f
#define CHIRP_F0 (1.0f / CHIRP_T1)
#define CHIRP_F1 (1.0f / (2.0f * TS))

#define NOTCH_F_CUT 1.0e3f
#define NOTCH_D 0.1f

#define LOWPASS2_F_CUT 60.0f
#define LOWPASS2_D (sqrtf(3.0f) / 2.0f)

#define LOWPASS1_F_CUT 60.0f

int main(int argc, char *argv[])
{
    Chirp chirp_cpp;
    chirp_cpp.init(CHIRP_F0, CHIRP_F1, CHIRP_T1, TS);
    IIRFilter notch_cpp;
    notch_cpp.notchFilterInit(NOTCH_F_CUT, NOTCH_D, TS);
    IIRFilter lowpass2_cpp;
    lowpass2_cpp.lowPassFilter2Init(LOWPASS2_F_CUT, LOWPASS2_D, TS);
    IIRFilter lowpass1_cpp;
    lowpass1_cpp.lowPassFilter1Init(LOWPASS1_F_CUT, TS);

    chirp_t chirp_c;
    chirpInit(&chirp_c, CHIRP_F0, CHIRP_F1, CHIRP_T1, TS);
    IIRFilter_t notch_c;
    notchFilterInit(&notch_c, NOTCH_F_CUT, NOTCH_D, TS);
    IIRFilter_t lowpass2_c;
    lowPassFilter2Init(&lowpass2_c, LOWPASS2_F_CUT, LOWPASS2_D, TS);
    IIRFilter_t lowpass1_c;
    lowPassFilter1Init(&lowpass1_c, LOWPASS1_F_CUT, TS);

    std::ofstream ofs ("output/datafile.txt");

    ssize_t cntr = 0;

    while (chirp_cpp.update() && chirpUpdate(&chirp_c)) {

        ofs  << std::setprecision(9) << std::scientific << cntr++ * TS << ", "                                      //  0
                                                        << chirp_cpp.getExc() << ", "                               //  1
                                                        << chirp_cpp.getFreq() << ", "                              //  2
                                                        << chirp_cpp.getSinarg() << ", "                            //  3
                                                        << chirp_c.exc << ", "                                      //  4
                                                        << chirp_c.fchirp << ", "                                   //  5
                                                        << chirp_c.sinarg << ", "                                   //  6
                                                        << notch_cpp.apply(chirp_cpp.getExc()) << ", "     //  7
                                                        << iirFilterApply(&notch_c, chirp_c.exc) << ", "            //  8
                                                        << lowpass2_cpp.apply(chirp_cpp.getExc()) << ", "  //  9
                                                        << iirFilterApply(&lowpass2_c, chirp_c.exc) << ", "         // 10
                                                        << lowpass1_cpp.apply(chirp_cpp.getExc()) << ", "  // 11
                                                        << iirFilterApply(&lowpass1_c, chirp_c.exc) << std::endl;   // 12

        // const float yMin = -0.8f;
        // const float yMax = 0.8f;
        // ofs  << std::setprecision(9) << std::scientific << cntr++ * TS << ", "                                            //  0
        //                                                 << chirp_cpp.getExc() << ", "                                     //  1
        //                                                 << chirp_cpp.getFreq() << ", "                                    //  2
        //                                                 << chirp_cpp.getSinarg() << ", "                                  //  3
        //                                                 << chirp_c.exc << ", "                                            //  4
        //                                                 << chirp_c.fchirp << ", "                                         //  5
        //                                                 << chirp_c.sinarg << ", "                                         //  6
        //                                                 << notch_cpp.applyConstrained(chirp_cpp.getExc(), yMin, yMax) << ", "                    //  7
        //                                                 << notchFilterApplyConstrained(&notch_c, chirp_c.exc, yMin, yMax) << ", "                //  8
        //                                                 << lowpass2_cpp.applyConstrained(chirp_cpp.getExc(), yMin, yMax) << ", "                 //  9
        //                                                 << lowPassFilter2ApplyConstrained(&lowpass2_c, chirp_c.exc, yMin, yMax) << std::endl;    // 10
    }

    ofs.close();

    return 0;
}
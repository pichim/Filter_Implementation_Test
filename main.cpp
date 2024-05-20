#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>

#include "Chirp.h"
#include "IIRFilter.h"

#include "chirp.h"
#include "iirfilter.h"

#define TS 50.0e-6f

#define CHIRP_T1 5.0f
#define CHIRP_F0 (1.0f / CHIRP_T1)
#define CHIRP_F1 (1.0f / (2.0f * TS))

#define NOTCH_F_CUT 1.0e3f
#define NOTCH_D 0.1f

#define LOWPASS2_F_CUT 60.0f
#define LOWPASS2_D (sqrtf(3.0f) / 2.0f)

#define LOWPASS1_F_CUT 60.0f

#define LEADLAG1_F_ZERO 60.0f
#define LEADLAG1_F_POLE 200.0f

#define PHASECOMP1_F_CENTER 80.0f
#define PHASECOMP1_PHASE_LIFT -45.0f

#define LEADLAG2_F_ZERO 20.0f
#define LEADLAG2_D_ZERO 0.08f
#define LEADLAG2_F_POLE 1000.0f
#define LEADLAG2_D_POLE 0.12f


int main(int argc, char *argv[])
{
    Chirp chirp_cpp;
    chirp_cpp.init(CHIRP_F0, CHIRP_F1, CHIRP_T1, TS);
    IIRFilter notch_cpp;
    notch_cpp.notchInit(NOTCH_F_CUT, NOTCH_D, TS);
    IIRFilter lowPass2_cpp;
    lowPass2_cpp.lowPass2Init(LOWPASS2_F_CUT, LOWPASS2_D, TS);
    IIRFilter lowPass1_cpp;
    lowPass1_cpp.lowPass1Init(LOWPASS1_F_CUT, TS);
    IIRFilter leadLag1_cpp;
    leadLag1_cpp.leadLag1Init(LEADLAG1_F_ZERO, LEADLAG1_F_POLE, TS);
    IIRFilter phaseComp_cpp;
    phaseComp_cpp.phaseComp1Init(PHASECOMP1_F_CENTER, PHASECOMP1_PHASE_LIFT, TS);
    IIRFilter leadLag2_cpp;
    leadLag2_cpp.leadLag2Init(LEADLAG2_F_ZERO, LEADLAG2_D_ZERO, LEADLAG2_F_POLE, LEADLAG2_D_POLE, TS);

    chirp_t chirp_c;
    chirpInit(&chirp_c, CHIRP_F0, CHIRP_F1, CHIRP_T1, TS);
    IIRFilter_t notch_c;
    notchInit(&notch_c, NOTCH_F_CUT, NOTCH_D, TS);
    IIRFilter_t lowPass2_c;
    lowPass2Init(&lowPass2_c, LOWPASS2_F_CUT, LOWPASS2_D, TS);
    IIRFilter_t lowPass1_c;
    lowPass1Init(&lowPass1_c, LOWPASS1_F_CUT, TS);
    IIRFilter_t leadLag1_c;
    leadLag1Init(&leadLag1_c, LEADLAG1_F_ZERO, LEADLAG1_F_POLE, TS);
    IIRFilter_t phaseComp_c;
    phaseComp1Init(&phaseComp_c, PHASECOMP1_F_CENTER, PHASECOMP1_PHASE_LIFT, TS);
    IIRFilter_t leadLag2_c;
    leadLag2Init(&leadLag2_c, LEADLAG2_F_ZERO, LEADLAG2_D_ZERO, LEADLAG2_F_POLE, LEADLAG2_D_POLE, TS);

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
                                                        << notch_cpp.apply(chirp_cpp.getExc()) << ", "              //  7
                                                        << iirFilterApply(&notch_c, chirp_c.exc) << ", "            //  8
                                                        << lowPass2_cpp.apply(chirp_cpp.getExc()) << ", "           //  9
                                                        << iirFilterApply(&lowPass2_c, chirp_c.exc) << ", "         // 10
                                                        << lowPass1_cpp.apply(chirp_cpp.getExc()) << ", "           // 11
                                                        << iirFilterApply(&lowPass1_c, chirp_c.exc) << ", "         // 12
                                                        << leadLag1_cpp.apply(chirp_cpp.getExc()) << ", "           // 13
                                                        << iirFilterApply(&leadLag1_c, chirp_c.exc) << ", "         // 14
                                                        << phaseComp_cpp.apply(chirp_cpp.getExc()) << ", "          // 15
                                                        << iirFilterApply(&phaseComp_c, chirp_c.exc) << ", "        // 16
                                                        << leadLag2_cpp.apply(chirp_cpp.getExc()) << ", "           // 17
                                                        << iirFilterApply(&leadLag2_c, chirp_c.exc) << std::endl;   // 18

    }

    ofs.close();

    return 0;
}
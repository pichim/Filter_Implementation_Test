#include <iostream>
#include <fstream>
#include <iomanip>
#include <math.h>

#include "Chirp.h"
#include "IIRFilter.h"
#include "FadingNotchFilter.h"

#include "chirp.h"
#include "iirfilter.h"
#include "fadingnotchfilter.h"

/**
 * TODO:
 * - Initialization of differentiating filters needs to be fixed
 */

#define TS 50.0e-6f

#define CHIRP_T1 5.0f
#define CHIRP_F0 (1.0f / CHIRP_T1)
#define CHIRP_F1 (1.0f / (2.0f * TS))
#define CHIRP_OFFSET 5.0f
#define CHIRP_AMPLITUDE 3.0f
#define CHIRP_T_SETTLE 2.0f

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

#define FADING_NOTCH_F_CUT 0.0f
#define FADING_NOTCH_D 0.1f
#define FADING_NOTCH_F_FADE_MIN 100.0f
#define FADING_NOTCH_F_FADE_MAX 1000.0f

#define DIFF_LOWPASS1_F_CUT 120.0f


int main(int argc, char *argv[])
{
    Chirp chirp_cpp;
    chirp_cpp.init(CHIRP_F0, CHIRP_F1, CHIRP_T1, TS);

    IIRFilter notch_cpp;
    notch_cpp.notchInit(NOTCH_F_CUT, NOTCH_D, TS);
    notch_cpp.reset(CHIRP_OFFSET);

    IIRFilter lowPass2_cpp;
    lowPass2_cpp.lowPass2Init(LOWPASS2_F_CUT, LOWPASS2_D, TS);
    lowPass2_cpp.reset(CHIRP_OFFSET);

    IIRFilter lowPass1_cpp;
    lowPass1_cpp.lowPass1Init(LOWPASS1_F_CUT, TS);
    lowPass1_cpp.reset(CHIRP_OFFSET);

    IIRFilter leadLag1_cpp;
    leadLag1_cpp.leadLag1Init(LEADLAG1_F_ZERO, LEADLAG1_F_POLE, TS);
    leadLag1_cpp.reset(CHIRP_OFFSET);

    IIRFilter phaseComp_cpp;
    phaseComp_cpp.phaseComp1Init(PHASECOMP1_F_CENTER, PHASECOMP1_PHASE_LIFT, TS);
    phaseComp_cpp.reset(CHIRP_OFFSET);
    
    IIRFilter leadLag2_cpp;
    leadLag2_cpp.leadLag2Init(LEADLAG2_F_ZERO, LEADLAG2_D_ZERO, LEADLAG2_F_POLE, LEADLAG2_D_POLE, TS);
    leadLag2_cpp.reset(CHIRP_OFFSET);

    FadingNotchFilter fadingNotch_cpp;
    fadingNotch_cpp.fadingNotchInit(FADING_NOTCH_F_CUT, FADING_NOTCH_D, FADING_NOTCH_F_FADE_MIN, FADING_NOTCH_F_FADE_MAX, TS);
    fadingNotch_cpp.reset(FADING_NOTCH_F_CUT, CHIRP_OFFSET);

    IIRFilter integrator_cpp;
    integrator_cpp.integratorInit(TS);
    integrator_cpp.reset(CHIRP_OFFSET);

    IIRFilter differentiator_cpp;
    differentiator_cpp.differentiatorInit(TS);
    differentiator_cpp.reset(CHIRP_OFFSET); // differentiating a constant input results in zero

    IIRFilter differentiatingLowPass1_cpp;
    differentiatingLowPass1_cpp.differentiatingLowPass1Init(DIFF_LOWPASS1_F_CUT, TS);
    differentiatingLowPass1_cpp.reset(CHIRP_OFFSET); // differentiating a constant input results in zero

    chirp_t chirp_c;
    chirpInit(&chirp_c, CHIRP_F0, CHIRP_F1, CHIRP_T1, TS);

    IIRFilter_t notch_c;
    notchInit(&notch_c, NOTCH_F_CUT, NOTCH_D, TS);
    iirFilterReset(&notch_c, CHIRP_OFFSET);

    IIRFilter_t lowPass2_c;
    lowPass2Init(&lowPass2_c, LOWPASS2_F_CUT, LOWPASS2_D, TS);
    iirFilterReset(&lowPass2_c, CHIRP_OFFSET);

    IIRFilter_t lowPass1_c;
    lowPass1Init(&lowPass1_c, LOWPASS1_F_CUT, TS);
    iirFilterReset(&lowPass1_c, CHIRP_OFFSET);

    IIRFilter_t leadLag1_c;
    leadLag1Init(&leadLag1_c, LEADLAG1_F_ZERO, LEADLAG1_F_POLE, TS);
    iirFilterReset(&leadLag1_c, CHIRP_OFFSET);

    IIRFilter_t phaseComp_c;
    phaseComp1Init(&phaseComp_c, PHASECOMP1_F_CENTER, PHASECOMP1_PHASE_LIFT, TS);
    iirFilterReset(&phaseComp_c, CHIRP_OFFSET);

    IIRFilter_t leadLag2_c;
    leadLag2Init(&leadLag2_c, LEADLAG2_F_ZERO, LEADLAG2_D_ZERO, LEADLAG2_F_POLE, LEADLAG2_D_POLE, TS);
    iirFilterReset(&leadLag2_c, CHIRP_OFFSET);

    FadingNotchFilter_t fadingNotch_c;
    fadingNotchInit(&fadingNotch_c, FADING_NOTCH_F_CUT, FADING_NOTCH_D, FADING_NOTCH_F_FADE_MIN, FADING_NOTCH_F_FADE_MAX, TS);
    fadingNotchFilterReset(&fadingNotch_c, FADING_NOTCH_F_CUT, CHIRP_OFFSET);

    IIRFilter_t integrator_c;
    integratorInit(&integrator_c, TS);
    iirFilterReset(&integrator_c, CHIRP_OFFSET);

    IIRFilter_t differentiator_c;
    differentiatorInit(&differentiator_c, TS);
    iirFilterReset(&differentiator_c, CHIRP_OFFSET); // differentiating a constant input results in zero

    IIRFilter_t differentiatingLowPass1_c;
    differentiatingLowPass1Init(&differentiatingLowPass1_c, DIFF_LOWPASS1_F_CUT, TS);
    iirFilterReset(&differentiatingLowPass1_c, CHIRP_OFFSET); // differentiating a constant input results in zero

    std::ofstream ofs ("output/data.txt");

    uint64_t cntr = 0;

    float chirp_exc_cpp = 0.0f;
    float chirp_freq_cpp = 0.0f;
    float chirp_sinarg_cpp = 0.0f;
    float chirp_exc_c = 0.0f;
    float chirp_freq_c = 0.0f;
    float chirp_sinarg_c = 0.0f;

    float input_cpp = CHIRP_OFFSET;
    float input_c = CHIRP_OFFSET;

    bool chirp_update_finished = false;

    while (true) {

        const float time = cntr++ * TS;

        if (time > CHIRP_T_SETTLE) {
            if (chirp_cpp.update() && chirpUpdate(&chirp_c)) {
                chirp_exc_cpp = chirp_cpp.getExc();
                chirp_freq_cpp = chirp_cpp.getFreq();
                chirp_sinarg_cpp = chirp_cpp.getSinarg();
                chirp_exc_c = chirp_c.exc;
                chirp_freq_c = chirp_c.fchirp;
                chirp_sinarg_c = chirp_c.sinarg;

                input_cpp = CHIRP_AMPLITUDE * chirp_exc_cpp + CHIRP_OFFSET;
                input_c = CHIRP_AMPLITUDE * chirp_exc_c + CHIRP_OFFSET;
            } else {
                chirp_update_finished = true;
            }
        }

        if (chirp_update_finished)
            break;

        ofs  << std::setprecision(9) << std::scientific << time << ", "                                                            //  0
                                                        << chirp_exc_cpp << ", "                                                   //  1
                                                        << chirp_freq_cpp << ", "                                                  //  2
                                                        << chirp_sinarg_cpp << ", "                                                //  3
                                                        << chirp_exc_c << ", "                                                     //  4
                                                        << chirp_freq_c << ", "                                                    //  5
                                                        << chirp_sinarg_c << ", "                                                  //  6
                                                        << notch_cpp.apply(input_cpp) << ", "                                      //  7
                                                        << iirFilterApply(&notch_c, input_c) << ", "                               //  8
                                                        << lowPass2_cpp.apply(input_cpp) << ", "                                   //  9
                                                        << iirFilterApply(&lowPass2_c, input_c) << ", "                            // 10
                                                        << lowPass1_cpp.apply(input_cpp) << ", "                                   // 11
                                                        << iirFilterApply(&lowPass1_c, input_c) << ", "                            // 12
                                                        << leadLag1_cpp.apply(input_cpp) << ", "                                   // 13
                                                        << iirFilterApply(&leadLag1_c, input_c) << ", "                            // 14
                                                        << phaseComp_cpp.apply(input_cpp) << ", "                                  // 15
                                                        << iirFilterApply(&phaseComp_c, input_c) << ", "                           // 16
                                                        << leadLag2_cpp.apply(input_cpp) << ", "                                   // 17
                                                        << iirFilterApply(&leadLag2_c, input_c) << ", "                            // 18
                                                        << input_cpp << ", "                                                       // 19
                                                        << input_c << ", "                                                         // 20
                                                        << fadingNotch_cpp.apply(chirp_freq_cpp, input_cpp) << ", "                // 21
                                                        << fadingNotchFilterApply(&fadingNotch_c, chirp_freq_cpp, input_c) << ", " // 22
                                                        << integrator_cpp.apply(input_cpp) << ", "                                 // 23
                                                        << iirFilterApply(&integrator_c, input_c) << ", "                          // 24
                                                        << differentiator_cpp.apply(input_cpp) << ", "                             // 25
                                                        << iirFilterApply(&differentiator_c, input_c) << ", "                      // 26
                                                        << differentiatingLowPass1_cpp.apply(input_cpp) << ", "                    // 27
                                                        << iirFilterApply(&differentiatingLowPass1_c, input_c) << std::endl;       // 28

    }

    ofs.close();

    return 0;
}
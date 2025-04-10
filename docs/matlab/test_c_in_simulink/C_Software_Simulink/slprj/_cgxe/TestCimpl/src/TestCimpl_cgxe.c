/* Include files */

#include "TestCimpl_cgxe.h"
#include "m_bKQgXCoH8tcEcvIVXTEX9C.h"

unsigned int cgxe_TestCimpl_method_dispatcher(SimStruct* S, int_T method, void
  * data)
{
  if (ssGetChecksum0(S) == 3691120995 &&
      ssGetChecksum1(S) == 2811185940 &&
      ssGetChecksum2(S) == 501019588 &&
      ssGetChecksum3(S) == 2509995162) {
    method_dispatcher_bKQgXCoH8tcEcvIVXTEX9C(S, method, data);
    return 1;
  }

  return 0;
}

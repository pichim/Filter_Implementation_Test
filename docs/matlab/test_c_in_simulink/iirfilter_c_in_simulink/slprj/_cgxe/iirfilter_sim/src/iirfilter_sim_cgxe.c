/* Include files */

#include "iirfilter_sim_cgxe.h"
#include "m_pEClYI3NgNTuTdGHmGitdG.h"

unsigned int cgxe_iirfilter_sim_method_dispatcher(SimStruct* S, int_T method,
  void* data)
{
  if (ssGetChecksum0(S) == 1619662919 &&
      ssGetChecksum1(S) == 4134176624 &&
      ssGetChecksum2(S) == 2143326382 &&
      ssGetChecksum3(S) == 130633954) {
    method_dispatcher_pEClYI3NgNTuTdGHmGitdG(S, method, data);
    return 1;
  }

  return 0;
}

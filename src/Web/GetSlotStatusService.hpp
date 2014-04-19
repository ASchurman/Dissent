#ifndef DISSENT_WEB_GET_SLOT_STATUS_SERVICE_GUARD
#define DISSENT_WEB_GET_SLOT_STATUS_SERVICE_GUARD

#include "SessionService.hpp"

namespace Dissent {
namespace Web {

  class GetSlotStatusService : public SessionService
  {
  public:
    explicit GetSlotStatusService(SessionManager &sm)
      : SessionService(sm)
    { }

    virtual ~GetSlotStatusService() { }

    /**
     * Called to handle the incoming request
     * @param request the incoming request
     * @param response used to respond to the rqeuest
     */
    virtual void HandleRequest(QHttpRequest *request, QHttpResponse *response);
  };

}
}

#endif

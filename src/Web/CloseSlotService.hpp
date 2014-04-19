#ifndef DISSENT_WEB_CLOSE_SLOT_SERVICE_GUARD
#define DISSENT_WEB_CLOSE_SLOT_SERVICE_GUARD

#include "SessionService.hpp"

namespace Dissent {
namespace Web {

  /**
   * WebService for closing the speaker's slot for queue scheduling in
   * CSBulk. The contents of the HTTP POST body aren't read.
   */
  class CloseSlotService : public SessionService
  {
  public:
    explicit CloseSlotService(SessionManager &sm)
      : SessionService(sm)
    { }

    virtual ~CloseSlotService() { }

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

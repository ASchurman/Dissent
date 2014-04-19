#include "GetSlotStatusService.hpp"

namespace Dissent {
namespace Web {

  void GetSlotStatusService::HandleRequest(QHttpRequest *, QHttpResponse *response)
  {
    QSharedPointer<Session> session = GetSession();
    QVariant data;

    if(session) {
      data = session->GetSlotStatus();
    } else {
      data = false;
    }

    SendJsonResponse(response, data);
  }

}
}

#include "GetSlotStatusService.hpp"

namespace Dissent {
namespace Web {

  void GetSlotStatusService::HandleRequest(QHttpRequest *, QHttpResponse *response)
  {
    QSharedPointer<Session> session = GetSession();
    QVariantHash data;

    if(session) {
      data["status"] = session->GetSlotStatus() ? 1 : 0;
    } else {
      data["status"] = 0;
    }

    SendJsonResponse(response, data);
  }

}
}

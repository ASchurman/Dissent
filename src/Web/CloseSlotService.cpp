#include "CloseSlotService.hpp"

namespace Dissent {
namespace Web {

  void CloseSlotService::HandleRequest(QHttpRequest *,
      QHttpResponse *response)
  {
    QSharedPointer<Session> session = GetSession();
    QVariantHash data;

    if(session) {
      session->RequestCloseSlot();
      data["successful"] = 1;
    } else {
      data["successful"] = 0;
    }

    SendJsonResponse(response, data);
  }

}
}

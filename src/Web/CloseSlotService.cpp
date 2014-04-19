#include "CloseSlotService.hpp"

namespace Dissent {
namespace Web {

  void CloseSlotService::HandleRequest(QHttpRequest *,
      QHttpResponse *response)
  {
    QSharedPointer<Session> session = GetSession();
    QVariantHash data;

    if(session) {
      data["successful"] = session->RequestCloseSlot() ? 1 : 0;
    } else {
      data["successful"] = 0;
    }

    SendJsonResponse(response, data);
  }

}
}

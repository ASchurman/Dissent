#include "CloseSlotService.hpp"

namespace Dissent {
namespace Web {

  void CloseSlotService::HandleRequest(QHttpRequest *,
      QHttpResponse *response)
  {
    QSharedPointer<Session> session = GetSession();
    QVariant data;

    if(session) {
      data = session->RequestCloseSlot();
    } else {
      data = false;
    }

    SendJsonResponse(response, data);
  }

}
}

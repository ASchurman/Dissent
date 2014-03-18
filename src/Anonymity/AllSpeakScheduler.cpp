#include "AllSpeakScheduler.hpp"

#include <QDebug>

namespace Dissent {
namespace Anonymity {

  void AllSpeakScheduler::RequestingOpenSlot()
  {
    // All requests are granted instantly in this scheduler
    read = false;
    slot_open = true;
  }

  void AllSpeakScheduler::CloseMySlot()
  {
    slot_open = false;
  }

  void AllSpeakScheduler::RequestedOpenSlot(int idx, int len)
  {
    next_messages[idx] = len;
    next_msg_length += len;
    qDebug() << "Opening slot" << idx;
  }

  void AllSpeakScheduler::SlotClosed(int idx)
  {
    qDebug() << "Slot" << idx << "closing";
  }

}
}

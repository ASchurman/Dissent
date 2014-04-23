#include "AllSpeakScheduler.hpp"

#include <QDebug>

namespace Dissent {
namespace Anonymity {

  void AllSpeakScheduler::RequestingOpenSlot()
  {
    // All requests are granted instantly in this scheduler
    read = false;
    slot_open = true;
    emit SlotChanged(slot_open);
  }

  void AllSpeakScheduler::RequestingCloseSlot()
  {
    slot_open = false;
    emit SlotChanged(slot_open);
  }

  void AllSpeakScheduler::RequestedOpenSlot(int idx, int len)
  {
    next_messages[idx] = len;
    next_msg_length += len;
    qDebug() << "Opening slot" << idx;
  }

  void AllSpeakScheduler::RequestedCloseSlot(int idx)
  {
    qDebug() << "Slot" << idx << "closing";
  }

}
}

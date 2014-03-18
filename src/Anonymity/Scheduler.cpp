#include <QDebug>

#include "Scheduler.hpp"

namespace Dissent {
namespace Anonymity {

  void Scheduler::SetNextMsgLen(int idx, int len)
  {
    if (messages.contains(idx) && messages[idx] != 0) {
      qDebug() << "next_msg_length from " << next_msg_length << " to " << next_msg_length+len;
      next_msg_length += len;
      next_messages[idx] = len;
    } else {
      qDebug() << "Setting message length for a closed slot: " << idx;
    }
  }

  void Scheduler::CompletedRound()
  {
    qDebug() << "COMPLETED ROUND: setting msg_length from " << msg_length << " to " << next_msg_length;
    qDebug() << "Resetting next_msg_length to " << base_msg_length;
    messages = next_messages;
    msg_length = next_msg_length;

    next_messages.clear();
    next_msg_length = base_msg_length;
  }

}
}

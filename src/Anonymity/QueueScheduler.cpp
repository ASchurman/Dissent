#include "QueueScheduler.hpp"

#include <QDebug>

namespace Dissent {
namespace Anonymity {

  void QueueScheduler::RequestedOpenSlot(int idx, int len)
  {
    if (idx != speaker)
    {
      for (int i = 0; i < queue.count(); i++) {
        if (queue[i].first == idx) {
          // idx is already queued
          return;
        }
      }
      queue.enqueue(QPair<int, int>(idx, len));
    } else {
      qDebug() << "Trying to enqueue the current speaker:" << idx;
    }
  }

  void QueueScheduler::RequestedCloseSlot(int idx)
  {
    if (idx != speaker) {
      qDebug() << "Non-speaker requesting to close slot";
      return;
    }

    qDebug() << "Closing slot by request" << speaker;
    CloseSlot();
  }

  void QueueScheduler::CompletedRound()
  {
    // Check to see if current speaker is allowed to continue.
    // If speaker_time_limit is 0, then there is no time limit, so don't check
    // on the current timer value.
    if (speaker_time_limit != 0 && speaker >= 0) {
      if (speaker_timer == 0) {
        if (queue.isEmpty()) {
          qDebug() << "Time's up for " << speaker << " but queue is empty";
        } else {
          qDebug() << "Time's up! Closing slot" << speaker;
          CloseSlot();
        }
      } else {
        speaker_timer--;
        qDebug() << speaker_timer << " rounds left for speaker " << speaker;
      }
    }

    // Check to see if a new speaker should be dequeued.
    if (speaker < 0 && !queue.isEmpty()) {
      QPair<int, int> new_speaker = queue.dequeue();
      speaker = new_speaker.first;
      next_messages[speaker] = new_speaker.second;
      next_msg_length += new_speaker.second;
      qDebug() << "Opening slot" << speaker;
      speaker_timer = speaker_time_limit;

      if (speaker == my_idx) {
        qDebug() << "My slot is being opened";
        slot_open = true;
        read = false;
        emit SlotStatusChanged(slot_open);
      }
    }

    Scheduler::CompletedRound();
  }

  inline void QueueScheduler::CloseSlot()
  {
    next_msg_length -= next_messages[speaker];
    next_messages[speaker] = 0;
    if (speaker == my_idx) {
      slot_open = false;
      read = false;
      emit SlotStatusChanged(slot_open);
    }
    speaker = -1;
  }

}
}

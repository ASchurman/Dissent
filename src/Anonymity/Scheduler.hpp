#ifndef DISSENT_ANONYMITY_SCHEDULER_H_GUARD
#define DISSENT_ANONYMITY_SCHEDULER_H_GUARD

#include <QMap>

namespace Dissent {
namespace Anonymity {

  /**
   * Abstract base class for all scheduling schemes used in CSBulkRound
   */
  class Scheduler
  {
  public:
      Scheduler() : slot_open(false) {}

      virtual ~Scheduler() {}

      /**
       * Called when I am requesting to open my slot by indicating so in
       * my cipher text
       */
      virtual void RequestingOpenSlot() = 0;

      /**
       * Analogous to RequestingOpenSlot. Called when I am closing my slot.
       */
      virtual void CloseMySlot() = 0;

      /**
       * Called when a user requested their slot to be opened
       * @param idx the slot number requested to open
       * @param len the initial length of the opened slot
       */
      virtual void RequestedOpenSlot(int idx, int len) = 0;

      /**
       * Analogous to RequestedOpenSlot. Called when a speaking user requested
       * their slot to be closed
       * @param idx the slot number requested to close
       */
      virtual void SlotClosed(int idx) = 0;

      /**
       * Set the length of a slot for the next round. The slot should already
       * be opened through RequestedOpenSlot and be reflected in a non-zero
       * entry in messages before calling this function. Also adjusts
       * next_msg_length accordingly.
       * @param idx the slot number to set
       * @param len the length of the slot in the next round
       */
      virtual void SetNextMsgLen(int idx, int len);

      /**
       * Called each round by CSBulkRound. Updates messages and msg_length
       * based on next_messages and next_msg_length and any logic specific to
       * the particular Scheduler class.
       * Resets next_messages and next_msg_length to default values.
       */
      virtual void CompletedRound();

      virtual inline void SetBaseMessageLength(int len)
      {
        base_msg_length = len;
        next_msg_length = len;
      }


      /**
       * True if we should read our message queue
       */
      bool read;

      /**
       * True if my slot is open
       */
      bool slot_open;

      /**
       * Holds the length of each slot. Keyed by slot number. 0 if the slot is
       * closed.
       */
      QMap<int, int> messages;

      int msg_length;

      int base_msg_length;

  protected:
      QMap<int, int> next_messages;

      int next_msg_length;
  };

}
}

#endif

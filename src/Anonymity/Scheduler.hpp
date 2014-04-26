#ifndef DISSENT_ANONYMITY_SCHEDULER_H_GUARD
#define DISSENT_ANONYMITY_SCHEDULER_H_GUARD

#include <QMap>

#include "Identity/PrivateIdentity.hpp"

namespace Dissent {
namespace Anonymity {

  /**
   * Abstract base class for all scheduling schemes used in CSBulkRound
   */
  class Scheduler : public QObject
  {
    Q_OBJECT
  public:
      typedef Identity::PrivateIdentity PrivateIdentity;

      enum SchedulerType
      {
        INVALID,
        AllSpeakScheduler,
        QueueScheduler
      };

      static SchedulerType StringToSchedulerType(const QString& s)
      {
        if (s == "allspeak") {
          return AllSpeakScheduler;
        } else if (s == "queue") {
          return QueueScheduler;
        } else {
          return INVALID;
        }
      }

      static QString SchedulerTypeToString(SchedulerType t)
      {
        if (t == AllSpeakScheduler) {
          return "allspeak";
        } else if (t == QueueScheduler) {
          return "queue";
        } else {
          return "INVALID";
        }
      }

      Scheduler(const PrivateIdentity &ident) : slot_open(false), _ident(ident) {}

      virtual ~Scheduler() {}

      /**
       * Called when I am requesting to open my slot by indicating so in
       * my cipher text
       */
      virtual void RequestingOpenSlot() = 0;

      /**
       * Analogous to RequestingOpenSlot. Called when I am closing my slot.
       */
      virtual void RequestingCloseSlot() = 0;

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
      virtual void RequestedCloseSlot(int idx) = 0;

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

      inline void SetBaseMessageLength(int group_count)
      {
        msg_length = (group_count / 8);
        if(group_count % 8) {
          ++msg_length;
        }
        base_msg_length = msg_length;
        next_msg_length = base_msg_length;
      }

      virtual bool CanCloseSlot() { return false; }

      inline bool SlotOpen() { return slot_open; }
      inline int MessageLength() { return msg_length; }
      inline int BaseMessageLength() { return base_msg_length; }

      int my_idx;

      /**
       * True if we should read our message queue
       */
      bool read;

      /**
       * Holds the length of each slot. Keyed by slot number. 0 if the slot is
       * closed.
       */
      QMap<int, int> messages;

  signals:
      // Emitted when the slot is opened or closed
      void SlotStatusChanged(bool status);

  protected:
      inline const PrivateIdentity &GetPrivateIdentity() const { return _ident; }

      /**
       * True if my slot is open
       */
      bool slot_open;

      /**
       * Total length of the message, including all slots
       */
      int msg_length;

      int base_msg_length;

      /**
       * Holds the length of each slot for the upcoming round. 0 if the slot is
       * closed.
       */
      QMap<int, int> next_messages;

      /**
       * Total length of hte message for the upcoming round, including all
       * slots
       */
      int next_msg_length;

  private:
      const PrivateIdentity &_ident;
  };

}
}

#endif

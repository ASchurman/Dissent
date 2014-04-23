#ifndef DISSENT_ANONYMITY_QUEUE_SCHEDULER_H_GUARD
#define DISSENT_ANONYMITY_QUEUE_SCHEDULER_H_GUARD

#include <QQueue>
#include <QPair>

#include "Scheduler.hpp"

namespace Dissent {
namespace Anonymity {

  /**
   * Scheduler in which only a single node has an open slot at a time.
   * Additional nodes that request to open slots are queued.
   * The speaker's slot is closed and a new speaker is taken from the queue
   * after a certain number of rounds or when the speaker requests to close
   * its slot.
   */
  class QueueScheduler : public Scheduler
  {
    Q_OBJECT
  public:
    QueueScheduler(const PrivateIdentity &ident, int time_limit) :
      Scheduler(ident),
      speaker(-1),
      speaker_time_limit(time_limit)
    { }

    virtual ~QueueScheduler() {}

    /**
     * Called when I am requesting to open my slot by indicating so in
     * my cipher text. For this scheduler, it's a no-op. Nothing is done until
     * the request is received by others and I make it to the front
     * of the queue.
     */
    virtual void RequestingOpenSlot() {}

    /**
     * Analogous to RequestingOpenSlot. Called when I am closing my slot.
     * For this scheduler, it's a no-op. Nothing is done until the request
     * is received by others.
     */
    virtual void RequestingCloseSlot() {}

    /**
     * Called when a user requested their slot to be opened
     * @param idx the slot number requested to open
     * @param len the initial length of the opened slot
     */
    virtual void RequestedOpenSlot(int idx, int len);

    /**
     * Analogous to RequestedOpenSlot. Called when a speaking user requested
     * their slot to be closed
     * @param idx the slot number requested to close
     */
    virtual void RequestedCloseSlot(int idx);

    virtual void CompletedRound();

    virtual bool CanCloseSlot()
    {
      return speaker == my_idx || GetPrivateIdentity().GetModerator();
    }

  protected:
    void CloseSlot();

    /**
     * The slot number of the current speaker, or -1 if there is no speaker
     */
    int speaker;

    /**
     * The queue of slot number, slot length pairs waiting to speak
     */
    QQueue< QPair<int, int> > queue;

    /**
     * Number of rounds a slot is permitted to be opened
     */
    int speaker_time_limit;

    /**
     * Number of rounds before the current speaker's slot is closed
     */
    int speaker_timer;
  };

}
}

#endif

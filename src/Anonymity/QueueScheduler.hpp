#ifndef DISSENT_ANONYMITY_QUEUE_SCHEDULER_H_GUARD
#define DISSENT_ANONYMITY_QUEUE_SCHEDULER_H_GUARD

#include <QQueue>
#include <QPair>

#include "Scheduler.hpp"

// TODO-AMS work on manually closing slots

namespace Dissent {
namespace Anonymity {

  class QueueScheduler : public Scheduler
  {
  public:
    QueueScheduler() : speaker(-1) {}

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
    const int speaker_time_limit = 30;

    /**
     * Number of rounds before the current speaker's slot is closed
     */
    int speaker_timer;
  };

}
}

#endif

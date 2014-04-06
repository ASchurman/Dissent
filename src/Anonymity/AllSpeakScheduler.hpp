#ifndef DISSENT_ANONYMITY_ALLSPEAK_SCHEDULER_H_GUARD
#define DISSENT_ANONYMITY_ALLSPEAK_SCHEDULER_H_GUARD

#include "Scheduler.hpp"

namespace Dissent {
namespace Anonymity {

  /**
   * Scheduler in which all nodes can have slots opened as soon as they
   * request it.
   */
  class AllSpeakScheduler : public Scheduler
  {
  public:
      AllSpeakScheduler(const PrivateIdentity &ident) :
        Scheduler(ident)
      { }

      virtual ~AllSpeakScheduler() {}

      /**
       * Called when I am requesting to open my slot by indicating so in
       * my cipher text
       */
      void RequestingOpenSlot();

      /**
       * Analogous to RequestingOpenSlot. Called when I am closing my slot.
       */
      virtual void RequestingCloseSlot();

      /**
       * Called when a user requested their slot to be opened
       * @param idx the slot number requested to open
       * @param len the initial length of the opened slot
       */
      void RequestedOpenSlot(int idx, int len);

      /**
       * Analogous to RequestedOpenSlot. Called when a speaking user requested
       * their slot to be closed
       * @param idx the slot number requested to close
       */
      virtual void RequestedCloseSlot(int idx);
  };

}
}

#endif

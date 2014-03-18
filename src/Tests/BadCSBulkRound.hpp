#ifndef DISSENT_TESTS_BAD_CS_BULK_ROUND_H_GUARD
#define DISSENT_TESTS_BAD_CS_BULK_ROUND_H_GUARD

#include "DissentTest.hpp"
#include "RoundTest.hpp"

namespace Dissent {
namespace Tests {

  class CSBulkRoundBadClient : public CSBulkRound, public Triggerable {
    public:
      explicit CSBulkRoundBadClient(const Group &group,
          const PrivateIdentity &ident,
          const Id &round_id,
          const QSharedPointer<Network> &network,
          GetDataCallback &get_data,
          const QSharedPointer<BuddyMonitor> &bm,
          CreateRound create_shuffle) :
        CSBulkRound(group, ident, round_id, network, get_data, bm, create_shuffle)
      {
      }

      virtual QString ToString() const
      {
        return CSBulkRound::ToString() + " BAD!";
      }

    protected:
      virtual QByteArray GenerateCiphertext()
      {
        QByteArray msg = CSBulkRound::GenerateCiphertext();
        if(msg.size() == GetState()->scheduler->base_msg_length) {
          qDebug() << "No damage done";
          return msg;
        }

        int offset = Random::GetInstance().GetInt(GetState()->scheduler->base_msg_length + 1, msg.size());
        msg[offset] = msg[offset] ^ 0xff;
        qDebug() << "up to no good";
        Triggerable::SetTriggered();
        return msg;
      }
  };
}
}

#endif

#include "connection_address_filter.h"

#include "envoy/buffer/buffer.h"
#include "envoy/network/connection.h"

#include "source/common/common/assert.h"
#include "source/common/network/address_impl.h"
#include "source/common/network/cidr_range.h"

namespace Envoy {
namespace Filter {

Network::FilterStatus ConnectionAddresssFilter::onData(Buffer::Instance&, bool) {
  ENVOY_LOG(trace, "onData");
  return Network::FilterStatus::Continue;
}

Network::FilterStatus ConnectionAddresssFilter::onNewConnection() {
  ENVOY_LOG(trace, "onNewConnection");
  const auto& connection_info = read_callbacks_->connection().connectionInfoProviderSharedPtr();
  const auto& local_address = connection_info->localAddress()->asString();
  const auto& remote_address = connection_info->remoteAddress()->asString();
  ENVOY_CONN_LOG(trace, "New connection established. Local: {}, Remote: {}",
                 read_callbacks_->connection(), local_address, remote_address);
  
  // const auto& remote = connection_info->remoteAddress();

  Network::Address::CidrRange rng = Network::Address::CidrRange::create("127.0.0.1/32"); 
  
  // if (rng.isInRange(*remote)) {
  //   ENVOY_LOG(trace, "is in range");
  //   read_callbacks_->connection().close(Network::ConnectionCloseType::Abort);
  //   return Network::FilterStatus::StopIteration;
  // }

  // [dinofizz] WIP testing port filter
  // Check if the remote port is 8888
  if (connection_info->remoteAddress()->ip()->port() != 8888) {
    ENVOY_LOG(trace, "Closing connection because remote IP is 127.0.0.1 and remote port is not 8888");
    // read_callbacks_->connection().close(Network::ConnectionCloseType::Abort);
    // return Network::FilterStatus::StopIteration;

    read_callbacks_->connection().streamInfo().setConnectionTerminationDetails("access denied");
    read_callbacks_->connection().close(Network::ConnectionCloseType::AbortReset, "forbidden_port_close");
    return Network::FilterStatus::StopIteration;
  } else {
    ENVOY_LOG(trace, "NOT closing connection");
  }

  return Network::FilterStatus::Continue;
}

} // namespace Filter
} // namespace Envoy

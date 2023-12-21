#include <string>

#include "connection_address_filter.h"

#include "envoy/registry/registry.h"
#include "envoy/server/filter_config.h"

namespace Envoy {
namespace Server {
namespace Configuration {


/**
 * Config registration for the echo2 filter. @see NamedNetworkFilterConfigFactory.
 */
class ConnectionAddresssFilterConfigFactory : public NamedUpstreamNetworkFilterConfigFactory {
public:
  Network::FilterFactoryCb createFilterFactoryFromProto(const Protobuf::Message&,
                                                        UpstreamFactoryContext&) override {
    return [](Network::FilterManager& filter_manager) -> void {
      filter_manager.addReadFilter(Network::ReadFilterSharedPtr{new Filter::ConnectionAddresssFilter()});
    };
  }

  ProtobufTypes::MessagePtr createEmptyConfigProto() override {
    return ProtobufTypes::MessagePtr{new Envoy::ProtobufWkt::Struct()};
  }

  std::string name() const override { return "dinofizzotti.connection_address_filter"; }

  // bool isTerminalFilterByProto(const Protobuf::Message&, ServerFactoryContext&) override { return true; }
};
/**
 * Static registration for the echo2 filter. @see RegisterFactory.
 */
static Registry::RegisterFactory<ConnectionAddresssFilterConfigFactory, NamedUpstreamNetworkFilterConfigFactory> registered_;

} // namespace Configuration
} // namespace Server
} // namespace Envoy

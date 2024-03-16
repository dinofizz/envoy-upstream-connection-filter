#pragma once

#include "envoy/network/filter.h"

#include "source/common/common/logger.h"

namespace Envoy {
namespace Filter {

/**
 * Implementation of a basic echo filter.
 */
class ConnectionAddresssFilter : public Network::ReadFilter, Logger::Loggable<Logger::Id::filter> {
public:
  // Network::ReadFilter
  Network::FilterStatus onData(Buffer::Instance&, bool end_stream) override;
  Network::FilterStatus onNewConnection() override;
  void initializeReadFilterCallbacks(Network::ReadFilterCallbacks& callbacks) override {
    read_callbacks_ = &callbacks;
  }

private:
  Network::ReadFilterCallbacks* read_callbacks_{};
};

} // namespace Filter
} // namespace Envoy
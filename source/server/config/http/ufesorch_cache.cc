#include "server/config/http/ufesorch_cache.h"

#include <chrono>
#include <string>

#include "common/http/filter/ufesorch_filter.h"
#include "common/cache/cache_impl.h"
#include "envoy/registry/registry.h"

namespace Envoy {
namespace Server {
namespace Configuration {

HttpFilterFactoryCb UfesOrchFilterConfig::createFilterFactory(const Json::Object& config,
                                                           const std::string&,
                                                           FactoryContext& context) {
  log().info("creating ufes orchestrator filter factory..");
  std::string orchestrator_cluster = config.getString("orchestrator_cluster");
  log().info("orchestrator cluster '{}' configured. ", orchestrator_cluster);
  int64_t timeout = config.getInteger("timeout");
  log().info("orchestrator timeput '{}' configured. ", timeout);

  Http::Cache::UfesOrchFilterConfigSharedPtr filter_config(new Http::Cache::UfesOrchFilterConfig(orchestrator_cluster, timeout, context.clusterManager()));
  Http::Cache::OrchClientPtr orch_client(new Http::Cache::RestOrchClient(context.clusterManager(), orchestrator_cluster));

  return [filter_config, &context, orch_client](Http::FilterChainFactoryCallbacks& callbacks) -> void {
    callbacks.addStreamDecoderFilter(Http::StreamDecoderFilterSharedPtr{new Http::Cache::UfesOrchFilter(filter_config, orch_client)});
  };
}

/**
 * Static registration for the ufes orch filter. @see RegisterFactory.
 */
static Registry::RegisterFactory<UfesOrchFilterConfig, NamedHttpFilterConfigFactory> register_;

} // Configuration
} // Server
} // Envoy

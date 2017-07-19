#include "common/http/filter/cache_filter.h"

#include <string>
#include <chrono>

#include "envoy/cache/cache.h"
#include "common/cache/cache_constants.h"
#include "common/http/header_map_impl.h"
#include "envoy/http/header_map.h"
#include "envoy/http/filter.h"

namespace Envoy {
namespace Http {
namespace Cache {

FilterHeadersStatus CacheFilter::decodeHeaders(Envoy::Http::HeaderMap& headers, bool) {
  client_->cache(*this, headers);
  return FilterHeadersStatus::StopIteration;
}

FilterDataStatus CacheFilter::decodeData(Buffer::Instance&, bool) {
  return FilterDataStatus::Continue;
}

FilterTrailersStatus CacheFilter::decodeTrailers(HeaderMap&) {
  return FilterTrailersStatus::Continue;
}

void CacheFilter::setDecoderFilterCallbacks(StreamDecoderFilterCallbacks& callbacks) {
  callbacks_ = &callbacks;
}


void CacheFilter::complete(OrchestratorResponse& response) {
   callbacks_->continueDecoding();

}
} //namespace envoy
}// namespace http
}// namespace cache


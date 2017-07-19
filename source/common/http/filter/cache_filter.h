#pragma once

#include <string>
#include <chrono>

#include "envoy/http/filter.h"
#include "envoy/upstream/cluster_manager.h"
#include "envoy/cache/cache.h"

#include "common/http/header_map_impl.h"

namespace Envoy {
namespace Http {
namespace Cache {

class CacheFilterConfig  {
public:
	 CacheFilterConfig(const std::string cache_cluster_name, int64_t timeout, Upstream::ClusterManager& cm)
	      : cache_cluster_(cache_cluster_name),
	        timeout_(std::chrono::milliseconds(timeout)),
	        cm_(cm) {}
private:
	const std::string cache_cluster_;
	const std::chrono::milliseconds timeout_;
	Upstream::ClusterManager& cm_;

};

typedef std::shared_ptr<CacheFilterConfig> CacheFilterConfigSharedPtr;

class CacheFilter : Logger::Loggable<Logger::Id::filter>, public StreamDecoderFilter {

public:
	CacheFilter(CacheFilterConfigSharedPtr config, CacheClientPtr client): config_(config), client_(std::move(client)){}
	~CacheFilter() {}

	// Http::StreamFilterBase
	void onDestroy() override;

	// Http::StreamDecoderFilter
	FilterHeadersStatus decodeHeaders(HeaderMap& headers, bool end_stream) override;
	FilterDataStatus decodeData(Buffer::Instance& data, bool end_stream) override;
	FilterTrailersStatus decodeTrailers(HeaderMap& trailers) override;
	void setDecoderFilterCallbacks(StreamDecoderFilterCallbacks& callbacks) override;

private:
	CacheFilterConfigSharedPtr config_;
	CacheClientPtr client_;
	StreamDecoderFilterCallbacks* callbacks_{};
	Upstream::ClusterInfoConstSharedPtr cluster_;

};
  }// namespace Cache
 }// namespace Http
}// namespace Envoy

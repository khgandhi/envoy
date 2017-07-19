#pragma once

#include <string>
#include <unordered_map>


#include "envoy/cache/cache.h"
#include "common/common/logger.h"
#include "envoy/upstream/cluster_manager.h"
#include "envoy/network/connection.h"
#include "envoy/buffer/buffer.h"


namespace Envoy {
namespace Http {
namespace Cache {

class RestCacheClient: public CacheClient, public Http::AsyncClient::Callbacks {

public:
	RestCacheClient(Upstream::ClusterManager& cm, std::string caching_cluster_name):cm_(cm), caching_cluster_name_(caching_cluster_name) {
	    if (cm_.get(caching_cluster_name) == nullptr) {
	    		throw EnvoyException (fmt::format("caching cluster name {} not defined in cluster manager.", caching_cluster_name));
    	}
	}

	virtual ~RestCacheClient() {};

	// CacheClient
	 void populateCacheObject(const std::string& cache_key, const std::string& cache_data) override;
	 std::string getCachedObject(const std::string& cache_key) override;

	 // AsyncClient::Callbacks
	 void onSuccess(Http::MessagePtr&& response) override;
	 void onFailure(Http::AsyncClient::FailureReason reason) override;

private:
	Upstream::ClusterManager& cm_;
	std::string caching_cluster_name_;
};


class RestOrchClient: public OrchClient, public Http::AsyncClient::Callbacks, public Logger::Loggable<Logger::Id::filter> {

public:
	RestOrchClient(Upstream::ClusterManager& cm, std::string orch_cluster_name):cm_(cm), orch_cluster_name_(orch_cluster_name) {
    	if (cm_.get(orch_cluster_name) == nullptr) {
    		throw EnvoyException(fmt::format("orchestrating cluster name {} not defined in cluster manager", orch_cluster_name));
    	}
	}

	virtual ~RestOrchClient() {};

	// OrchClient
	void orchestrate(OrchRequestCallbacks& callbacks, const Http::HeaderMap& headers) override;
	std::string createRequest(const Http::HeaderMap& downstreamHeaderMap) override;


	// AsyncClient::Callbacks
    void onSuccess(Http::MessagePtr&& response) override;
	void onFailure(Http::AsyncClient::FailureReason reason) override;

private:
	Upstream::ClusterManager& cm_;
	std::string orch_cluster_name_;
	OrchRequestCallbacks* callbacks_{};
};

}// namespace cache
} // namespace http
}// namespace envoy

#pragma once

#include <string>
#include <unordered_map>

#include "envoy/http/header_map.h"


namespace Envoy {
namespace Http {
namespace Cache {

/**
 * THe response from the Orchestrator client.
 **/

class OrchestratorResponse {

public:
	OrchestratorResponse(const std::string& cache_key, const uint64_t response_code, const std::string& go_to_origin):
	cache_key_(cache_key), response_code_(response_code), go_to_origin_(go_to_origin) {}

	~OrchestratorResponse() {};

	std::string getCacheKey() {return cache_key_;}

	uint64_t getResponseCode() {return response_code_;}

	std::string getGoToOrigin() {return go_to_origin_;}

private:
	std::string cache_key_;
	uint64_t response_code_;
	std::string go_to_origin_;
};

/**
 * A call back the orchestrator. To be called when the request is completed.
**/
class OrchRequestCallbacks {
public:
  virtual ~OrchRequestCallbacks() {};

  /**
   * Called when the Orchestrator call is completed.
   */
  virtual void complete(OrchestratorResponse& response) PURE;
};

/**
 * A call back for the cache invoker. To be called with the call to the external cache layer is completed.
 */
class CacheRequestCallbacks {
public:
	 virtual ~CacheRequestCallbacks() {}

	/**
	 * Called when the cache call is completed.
	 */
	virtual void complete() PURE;
};


/**
 * A cache client to interact with an external caching service.
 */
class CacheClient {
public:
	virtual ~CacheClient() {}

	/**
	 * This method is responsible for invoking the external cache for persisting the cache object.
	 */
	virtual void populateCacheObject(const std::string& cache_key, const std::string& cache_data) PURE;

	/**
	 * Get the cached object by looking up the external cache system.
	 */
	virtual std::string getCachedObject(const std::string& cache_key) PURE;
};

typedef std::shared_ptr<CacheClient> CacheClientPtr;

class OrchClient {

public:
	virtual ~OrchClient() {}

	/**
	* Invokes the external orchestrator to make a decision on whether to serve a cached page or not. It also returns the cache key if
	  we need to serve from the cache the HTML page.
	**/
	virtual void orchestrate(OrchRequestCallbacks& callbacks, const Http::HeaderMap& headers) PURE;

	/**
	 * create a request for the orch client.
	 */
	virtual std::string createRequest(const Http::HeaderMap& downstreamHeaderMap) PURE;
};

typedef std::shared_ptr<OrchClient> OrchClientPtr;

/**
 * The request to the orchestrator client.
 **/

class OrchestratorRequest {

public:
	OrchestratorRequest(const std::string& target_host, const std::string& target_uri) : 
	target_host_ (target_host), target_uri_(target_uri) {}
	
	~OrchestratorRequest() {};

	void addHttpHeader(const std::string& key, const std::string& value);

	void addQueryParam(const std::string& key, const std::string& value);

	std::string toJsonString();

private:
	std::string target_host_;
	std::string target_uri_;
	std::unordered_map<std::string, std::string> http_headers_;
	std::unordered_map<std::string, std::string> query_parameters_;

};
}// namespace cache
} // namespace http
}// namespace envoy

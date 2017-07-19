#pragma once

#include <string>

#include "envoy/http/header_map.h"
#include "common/common/singleton.h"

namespace Envoy {
namespace Http {
namespace Cache {

class CacheConstantValues {
public:
  const LowerCaseString CacheKeyHeader{"cache-key"};
  const LowerCaseString GoToOrigin{"go-to-origin"};

   struct {
    const std::string OrchestratorUri{"/ufesorchsvc/v1/orchestration"};
  } OrchestratorClientProperties;

   struct {
	  const std::string Purge {"PURGE"};
	  const std::string Push {"PUSH"};
  } CacheHttpMethods;
};

typedef ConstSingleton<CacheConstantValues> CacheConstants;

} // Cache
} // Http
} // Envoy

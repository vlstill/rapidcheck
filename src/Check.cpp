#include "rapidcheck/Check.h"

#include "detail/DefaultTestListener.h"
#include "detail/Testing.h"

namespace rc {
namespace detail {

TestResult
checkProperty(const Property &property,
              const TestMetadata &metadata,
              const TestParams &params,
              TestListener &listener,
              const std::unordered_map<std::string, Reproduce> &reproduceMap) {
  if (reproduceMap.empty()) {
    return testProperty(property, metadata, params, listener);
  }

  const auto it = reproduceMap.find(metadata.id);
  if (metadata.id.empty() || (it == end(reproduceMap))) {
    SuccessResult success;
    success.numSuccess = 0;
    return success;
  } else {
    auto reproduce = it->second;
    if (params.disableShrinking) {
      reproduce.shrinkPath.clear();
    }
    return reproduceProperty(property, reproduce);
  }
}

TestResult checkProperty(const Property &property,
                         const TestMetadata &metadata,
                         const TestParams &params,
                         TestListener &listener) {
  return checkProperty(
      property, metadata, params, listener, configuration().reproduce);
}

TestResult checkProperty(const Property &property,
                         const TestMetadata &metadata,
                         const TestParams &params) {
  return checkProperty(property, metadata, params, globalTestListener());
}

TestResult checkProperty(const Property &property,
                         const Config &config,
                         const TestMetadata &metadata) {
  auto params = configuration().testParams;
  if ( config.max_size >= 0 )
      params.maxSize = config.max_size;
  if ( config.max_success >= 0 )
      params.maxSuccess = config.max_success;
  return checkProperty(property, metadata, params);
}

TestResult checkProperty(const Property &property, const Config &config) {
  return checkProperty(property, config, TestMetadata());
}

} // namespace detail
} // namespace rc

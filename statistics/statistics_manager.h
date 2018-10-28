#include "base/prediction_set.h"
#include "statistics/clusterizator_statistics.h"
#include <memory>

class StatisticsManager {
public:
  StatisticsManager() = default;

  const ClusterizatorStatistics& statistics(const std::string& clusterizator_name) const {
    return statistics_.at(clusterizator_name);
  }

  void set_execution_time(const std::string& clusterizator_name, double execution_time);
  void set_score(const std::string& clusterizator_name, double score);

  void process_prediction_set(const PredictionSet& prediction_set);

private:
  void add_statistics_if_not_exists(const std::string& clusterizator_name);

  std::unordered_map<std::string, ClusterizatorStatistics> statistics_;
};

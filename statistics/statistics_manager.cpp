#include "statistics_manager.h"
#include <algorithm>
#include <memory>

void StatisticsManager::set_execution_time(const std::string& clusterizator_name, double execution_time) {
  add_statistics_if_not_exists(clusterizator_name);
  statistics_.at(clusterizator_name).execution_time = execution_time;
}

void StatisticsManager::set_web_score(const std::string& clusterizator_name, double score) {
  add_statistics_if_not_exists(clusterizator_name);
  statistics_.at(clusterizator_name).web_score = score;
}

void StatisticsManager::process_prediction_set(const PredictionSet& prediction_set) {
  auto clusterizator_name = prediction_set.clusterizator_name();
  add_statistics_if_not_exists(clusterizator_name);

  auto companies_count = prediction_set.class_by_company_name().size();
  std::unordered_map<int, size_t> cluster_sizes;
  for (const auto& [company_name, cluster] : prediction_set.class_by_company_name()) {
    cluster_sizes[cluster]++;
  }

  std::vector<std::pair<size_t, int>> size_and_clusters;
  for (const auto& [cluster, size] : cluster_sizes) {
    size_and_clusters.emplace_back(size, cluster);
  }

  std::sort(size_and_clusters.begin(), size_and_clusters.end());

  statistics_.at(clusterizator_name).median_cluster_size =
      (size_and_clusters[size_and_clusters.size() / 2].first +
        size_and_clusters[(size_and_clusters.size() + 1) / 2].first) / 2.0;

  statistics_.at(clusterizator_name).average_cluster_size =
      static_cast<double>(companies_count) /
      static_cast<double>(size_and_clusters.size());

  double coefficient_gini = 0;
  double sizes_prefix_sum = 0;
  for (size_t i = 0; i < size_and_clusters.size(); ++i) {
    sizes_prefix_sum += size_and_clusters[i].first;
    coefficient_gini +=
        2.0 * (1.0 * companies_count * (i + 1) / size_and_clusters.size() - sizes_prefix_sum);
  }
  statistics_.at(clusterizator_name).coefficient_gini = coefficient_gini;
}

void StatisticsManager::add_statistics_if_not_exists(const std::string& clusterizator_name) {
  if (statistics_.find(clusterizator_name) == statistics_.end()) {
    statistics_.emplace(clusterizator_name, ClusterizatorStatistics(clusterizator_name));
  }
}

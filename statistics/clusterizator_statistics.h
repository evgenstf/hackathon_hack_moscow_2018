#pragma once 

struct ClusterizatorStatistics {
  std::string name;
  double execution_time;
  double web_score;
  size_t clusters_count;
  double median_cluster_size;
  double average_cluster_size;
  double coefficient_gini;

  ClusterizatorStatistics(const std::string& clusterizator_name): name(clusterizator_name) {}
};

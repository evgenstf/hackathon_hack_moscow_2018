#include "clusterizator_manager.h"

ClusterizatorManager::ClusterizatorManager() {
  INFO("load OneClass strategy")
  clusterizators_.push_back(std::make_unique<OneClass>());
  INFO("load Hasher strategy")
  clusterizators_.push_back(std::make_unique<Hasher>());
  INFO("load Levenshtein strategy")
  clusterizators_.push_back(std::make_unique<Levenshtein>());
  INFO("load Levenshtein with company names preprocessing strategy")
  clusterizators_.push_back(std::make_unique<LevenshteinPreprocessed>());
  INFO("load \"Rand() % 2\" strategy")
  clusterizators_.push_back(std::make_unique<Rand2>());
}

void ClusterizatorManager::load_company_names(const std::vector<std::string>& company_names) {
  for (auto& clusterizator : clusterizators_) {
    DEBUG("load company_names to " << clusterizator->name())
    clusterizator->load_company_names(company_names);
  }
}

std::vector<PredictionSet> ClusterizatorManager::prediction_sets() {
  std::vector<PredictionSet> result;
  for (auto& clusterizator : clusterizators_) {
    DEBUG("getting prediction from " << clusterizator->name())
    result.push_back(clusterizator->prediction_set());
    DEBUG("finished")
  }
  return result;
}


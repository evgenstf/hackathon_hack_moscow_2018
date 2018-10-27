#include "algorithm_manager.h"

AlgorithmManager::AlgorithmManager() {
  INFO("load OneClass strategy")
  algorithms_.push_back(std::make_unique<OneClass>());
  INFO("load Hasher strategy")
  algorithms_.push_back(std::make_unique<Hasher>());
  INFO("load Levenshtein strategy")
  algorithms_.push_back(std::make_unique<Levenshtein>());
}

void AlgorithmManager::load_company_names(const std::vector<std::string>& company_names) {
  for (auto& algorithm : algorithms_) {
    DEBUG("load company_names to " << algorithm->name())
    algorithm->load_company_names(company_names);
  }
}

std::vector<PredictionSet> AlgorithmManager::prediction_sets() {
  std::vector<PredictionSet> result;
  for (auto& algorithm : algorithms_) {
    DEBUG("getting prediction from " << algorithm->name())
    result.push_back(algorithm->prediction_set());
  }
  return result;
}


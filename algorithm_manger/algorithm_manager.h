#include "algorithm.h"
#include "algorithms/one_class/one_class.h"
#include <memory>

class AlgorithmManager {
public:

  AlgorithmManager() {
    algorithms_.push_back(std::make_unique<OneClass>());
  }

  void load_company_names(const std::vector<std::string>& company_names) {
    for (auto& algorithm : algorithms_) {
      algorithm->load_company_names(company_names);
    }
  }

  std::vector<PredictionSet> prediction_sets() {
    std::vector<PredictionSet> result;
    for (auto& algorithm : algorithms_) {
      result.push_back(algorithm->prediction_set());
    }
    return result;
  }

private:
  std::vector<std::unique_ptr<Algorithm>> algorithms_;
};

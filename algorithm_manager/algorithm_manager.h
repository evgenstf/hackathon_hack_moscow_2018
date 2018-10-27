#include "algorithm.h"
#include "algorithms/one_class/one_class.h"
#include "algorithms/hasher/hasher.h"
#include "algorithms/levenshtein/levenshtein.h"
#include "base/logger/logger.h"
#include <memory>

class AlgorithmManager {
public:
  AlgorithmManager();
  void load_company_names(const std::vector<std::string>& company_names);
  std::vector<PredictionSet> prediction_sets();

private:
  std::vector<std::unique_ptr<Algorithm>> algorithms_;
};

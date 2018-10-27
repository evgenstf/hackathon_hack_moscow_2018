#include "clusterizator.h"
#include "clusterizators/one_class/one_class.h"
#include "clusterizators/hasher/hasher.h"
#include "clusterizators/levenshtein/levenshtein.h"
#include "clusterizators/levenshtein_preprocessed/levenshtein_preprocessed.h"
#include "clusterizators/rand2/rand2.h"
#include "base/logger/logger.h"
#include <memory>

class ClusterizatorManager {
public:
  ClusterizatorManager();
  void load_company_names(const std::vector<std::string>& company_names);
  std::vector<PredictionSet> prediction_sets();

private:
  std::vector<std::unique_ptr<Clusterizator>> clusterizators_;
};

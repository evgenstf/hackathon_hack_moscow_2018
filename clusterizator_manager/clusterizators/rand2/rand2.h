#include "base/prediction_set.h"
#include "base/dbscan/dbscan.h"
#include "../../clusterizator.h"

#include <random>

class Rand2 : public Clusterizator {
public:
  Rand2() {}

  void load_company_names(const std::vector<std::string>& company_names) override {
    company_names_ = company_names;
  }

  PredictionSet prediction_set() override {
    PredictionSet result(kClusterizatorName);
    std::mt19937 generator(1337u);
    for (const auto& company_name : company_names_) {
      result.add_prediction(company_name, generator() % 2);
    }
    return result;
  }

  const std::string& name() const override { return kClusterizatorName; }

private:
  const std::string kClusterizatorName = "\"Rand() % 2\"";

  std::vector<std::string> company_names_;
};

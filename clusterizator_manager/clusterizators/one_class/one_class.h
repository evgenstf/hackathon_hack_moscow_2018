#include "base/prediction_set.h"
#include "base/dbscan/dbscan.h"
#include "../../clusterizator.h"

class OneClass : public Clusterizator {
public:
  OneClass() {}

  void load_company_names(const std::vector<std::string>& company_names) override {
    company_names_ = company_names;
  }

  PredictionSet prediction_set() override {
    PredictionSet result(kClusterizatorName);
    for (const auto& company_name : company_names_) {
      result.add_prediction(company_name, 1);
    }
    return result;
  }

  const std::string& name() const override { return kClusterizatorName; }

private:
  const std::string kClusterizatorName = "OneClass";

  std::vector<std::string> company_names_;
};

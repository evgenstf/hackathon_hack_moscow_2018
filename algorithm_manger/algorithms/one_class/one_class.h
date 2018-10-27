#include "base/prediction_set.h"
#include "../../algorithm.h"

class OneClass : public Algorithm {
public:
  OneClass() {}

  void load_company_names(const std::vector<std::string>& company_names) override {
    company_names_ = company_names;
  }

  PredictionSet prediction_set() override {
    PredictionSet result(kAlgorithmName);
    for (const auto& company_name : company_names_) {
      result.add_prediction(company_name, 1);
    }
    return result;
  }

  std::string name() const { return kAlgorithmName; }

private:
  const std::string kAlgorithmName = "OneClass";

  std::vector<std::string> company_names_;
};

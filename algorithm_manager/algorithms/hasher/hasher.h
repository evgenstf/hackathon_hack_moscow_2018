#include "base/prediction_set.h"
#include "base/dbscan/dbscan.h"
#include "../../algorithm.h"

#include <cstdlib>

class Hasher : public Algorithm {
private:
  class HasherPoint {
  public:
    HasherPoint(const std::string& company_name)
      : hash_(std::hash<std::string>()(company_name))
    {
    }

    double distance_to(const HasherPoint& other) const {
      return std::abs(static_cast<long long>(hash_ - other.hash_));
    }

  private:
    const size_t hash_;
  };

public:
  Hasher() {}

  void load_company_names(const std::vector<std::string>& company_names) override {
    company_names_ = company_names;
  }

  PredictionSet prediction_set() override {
    PredictionSet result(kAlgorithmName);

    std::vector<HasherPoint> points;
    points.reserve(company_names_.size());
    for (const auto& company_name : company_names_) {
      points.emplace_back(company_name);
    }
    DBSCAN<HasherPoint> dbscan(100000, 3, points);
    const std::vector<unsigned int>& clusters = dbscan.get_clusters();

    for (size_t i = 0; i < company_names_.size(); ++i) {
      result.add_prediction(company_names_[i], clusters[i]);
    }
    return result;
  }

  const std::string& name() const override { return kAlgorithmName; }

private:
  const std::string kAlgorithmName = "Hasher";

  std::vector<std::string> company_names_;
};

#include "base/prediction_set.h"
#include "base/dbscan/dbscan.h"
#include "base/string_preprocessor/string_preprocessor.h"
#include "../../clusterizator.h"

#include <algorithm>
#include <cstdlib>

class LevenshteinPreprocessed : public Clusterizator {
private:
  class LevenshteinPoint {
  public:
    LevenshteinPoint(const std::string& company_name)
      : name_(company_name)
    {
    }

    double distance_to(const LevenshteinPoint& other) const {
      if (name_.empty() || other.name_.empty()) {
        return std::max(name_.size(), other.name_.size());
      }
      std::vector<std::vector<unsigned int>> d(name_.size(), std::vector<unsigned int>(other.name_.size()));
      for (size_t i = 0; i < name_.size(); ++i) {
        d[i][0] = i;
      }
      for (size_t i = 0; i < other.name_.size(); ++i) {
        d[0][i] = i;
      }
      for (size_t i = 1; i < name_.size(); ++i) {
        for (size_t j = 1; j < other.name_.size(); ++j) {
          unsigned int cost = !(name_[i] == other.name_[j]);
          d[i][j] = std::min({d[i - 1][j] + 1, d[i][j - 1] + 1, d[i - 1][j - 1] + cost});
        }
      }
      return d.back().back();
    }

  private:
    const std::string& name_;
  };

public:
  LevenshteinPreprocessed() {}

  void load_company_names(const std::vector<std::string>& company_names) override {
    company_names_ = company_names;
    preprocessing::StringPreprocessor preprocessor;
    preprocessor.set_forbidden_chars(" \t\n\r\"\'.,:|?!");
    preprocessor.set_forbidden_words({
      "inc", "org", "co", "com", "llc", "ltd"
    });
    for (std::string& name : company_names_) {
      name = preprocessor.preprocess(name);
    }
  }

  PredictionSet prediction_set() override {
    PredictionSet result(kClusterizatorName);

    std::vector<LevenshteinPoint> points;
    points.reserve(company_names_.size());
    for (const auto& company_name : company_names_) {
      points.emplace_back(company_name);
    }
    DBSCAN<LevenshteinPoint> dbscan(5, 3, points);
    const std::vector<unsigned int>& clusters = dbscan.get_clusters();

    for (size_t i = 0; i < company_names_.size(); ++i) {
      result.add_prediction(company_names_[i], clusters[i]);
    }
    return result;
  }

  const std::string& name() const override { return kClusterizatorName; }

private:
  const std::string kClusterizatorName = "Levenshtein with company names preprocessing";

  std::vector<std::string> company_names_;
};

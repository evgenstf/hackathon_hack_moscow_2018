#pragma once

#include "../base/prediction_set.h"
#include "../base/csv_parser/csv_parser.h"

#include <unordered_map>
#include <vector>
#include <string>

class Arranger {
public:
    Arranger(const std::string& path);
    double GetScore(const PredictionSet& prediction_set) const;

private:
    const std::vector<double>& GetFeatures(const std::string& name) const {
        if (model_.find(name) == model_.end()) {
            return empty_features_;
        }
        return model_.at(name);
    }

private:
    const std::string kCompanyName = "company_name";
    std::vector<double> empty_features_;
    size_t features_num_ = -1;

    std::unordered_map<std::string, std::vector<double>> model_;
};

#pragma once

#include "../base/prediction_set.h"

#include <unordered_set>
#include <vector>
#include <string>

class Arranger {
public:
    Arrange(const std::string& path);
    double GetScore(const PredictionSet& prediction_set) const;

private:
    std::unordered_set<std::string, std::vector<double>> model_;
};

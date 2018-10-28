#include "arranger.h"
#include "base/logger/logger.h"

#include <algorithm>
#include <cassert>
#include <cmath>

namespace {

    double ScalarProduct(const std::vector<double>& lhs, const std::vector<double>& rhs) {
        double res = 0;
        for (size_t i = 0; i < lhs.size(); ++i) {
            res += lhs[i] * rhs[i];
        }
        return res;
    }

} // namespace

Arranger::Arranger(const std::string& path) {
    DEBUG("parsing csv arranger model: " << path)
    CsvParser csv_parser(path);

    for (const auto& it : csv_parser.items()) {
        const std::string& name = it.at(kCompanyName);

        std::vector<double> features;
        features.reserve(it.size());

        std::vector<std::pair<std::string, std::string>> input(it.begin(), it.end());
        std::sort(input.begin(), input.end());

        for (const auto& [key, value] : input) {
            if (key != kCompanyName) {
                features.push_back(std::stod(value));
            }
        }

        if (features_num_ == -1) {
            features_num_ = features.size();
        }

        assert(features_num_ == features.size());

        model_[name] = std::move(features);
    }
    DEBUG("finished")
}

double Arranger::GetScore(const PredictionSet& prediction_set) const {
    INFO("calculating score for " << prediction_set.clusterizator_name())
    double score = 0;

    std::unordered_map<int, std::vector<std::string>> companies_by_cluster;

    const auto& predictions = prediction_set.class_by_company_name();
    for (const auto& [name, cluster] : predictions) {
        companies_by_cluster[cluster].push_back(name);
    }

    const size_t clusters = companies_by_cluster.size();

    // can be parallel for each cluster
    for (const auto& [cluster, companies] : companies_by_cluster) {
        if (companies.size() < 2) {
            score += clusters;
            continue;
        }

        for (size_t i = 0; i < companies.size(); ++i) {
            for (size_t j = i + 1; j < companies.size(); ++j) {
                const double product = ScalarProduct(GetFeatures(companies[i]), GetFeatures(companies[j]));
                score += 1. / (product + 1);
            }
        }
    }

    return score;
}

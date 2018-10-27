#include "arranger.h"

#include <algorithm>
#include <cassert>

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
}

double Arranger::GetScore(const PredictionSet& prediction_set) const {
    double score = 0;

    std::unordered_map<int, std::vector<std::string>> companies_by_cluster;

    const auto& predictions = prediction_set.class_by_company_name();
    for (const auto& [name, cluster] : predictions) {
        companies_by_cluster[cluster].push_back(name);
    }

    // can be parallel for each cluster
    for (const auto& [cluster, companies] : companies_by_cluster) {
        double cluster_score = 0;

        for (size_t i = 0; i < companies.size(); ++i) {
            for (size_t j = i + 1; j < companies.size(); ++j) {
                cluster_score += ScalarProduct(GetFeatures(companies[i]), GetFeatures(companies[j]));
            }
        }


        score += cluster_score;
    }

    return score;
}

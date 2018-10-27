#pragma once
#include <string>
#include <vector>
#include <unordered_map>

class PredictionSet {
public:
  PredictionSet(std::string algorithm_name):
    algorithm_name_(std::move(algorithm_name)) {}

  const std::string& algorithm_name() const { return algorithm_name_; }

  const std::unordered_map<std::string, int>& class_by_company_name() const {
    return class_by_company_name_;
  }

  void add_prediction(const std::string& company_name, int predicted_class) {
    class_by_company_name_[company_name] = predicted_class;
  }
    
private:
  std::unordered_map<std::string, int> class_by_company_name_;
  const std::string algorithm_name_;
};


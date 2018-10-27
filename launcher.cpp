#include "base/logger/logger.h"
#include "base/command_parser/command_parser.h"
#include "external_libraries/json.hpp"
#include "data_provider/data_provider.h"
#include "algorithm_manager/algorithm_manager.h"
#include "arranger/arranger.h"
#include <iostream>
#include <fstream>
#include <streambuf>

using namespace std;
using Json = nlohmann::json;

namespace {

auto read_config(const std::string& config_file) {
  std::ifstream stream(config_file);
  std::stringstream buffer;
  buffer << stream.rdbuf();
  return Json::parse(buffer.str());
}

void save_prediction(const PredictionSet& prediction_set) {
  std::ofstream file(prediction_set.algorithm_name() + "_prediction_set.csv");
  file << "company_name,predicted_class\n";
  for (const auto& [company_name, predicted_class] : prediction_set.class_by_company_name()) {
    file << '\"' << company_name << "\"," << predicted_class << '\n';
  }
}

}  // namespace

int main(int arguments_count, char* arguments[]) {
  CommandParser command_parser({});
  auto parse_result = command_parser.parse(arguments_count, arguments);

  if (parse_result.empty()) {
    std::clog << "Usage: score_calculator config.json" << std::endl;
    return 0;
  }

  const auto& config_file = parse_result.front().second.front();

  auto config = read_config(config_file);
  DEBUG("config: " << config);

  DataProvider data_provider;
  for (auto source : config["sources"]) {
    data_provider.add_source({source["filename"], source["company_names_row"]});
  }

  auto companies = data_provider.company_names();

  AlgorithmManager algorithm_manager;
  algorithm_manager.load_company_names(companies);

  auto prediction_sets = algorithm_manager.prediction_sets();

  Arranger arranger(config["arranger_model"]);
  
  for (const auto& prediction_set : prediction_sets) {
    auto prediction_score = arranger.GetScore(prediction_set);
    std::cout << prediction_set.algorithm_name() << " score: " << prediction_score << std::endl;
  }

  for (const auto& prediction_set : prediction_sets) {
    save_prediction(prediction_set);
  }

  return 0;
}

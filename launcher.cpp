#include "base/logger/logger.h"
#include "base/command_parser/command_parser.h"
#include "external_libraries/json.hpp"
#include "data_provider/data_provider.h"
#include "clusterizator_manager/clusterizator_manager.h"
#include "arranger/arranger.h"
#include "statistics/statistics_manager.h"
#include <boost/filesystem.hpp>
#include <iostream>
#include <fstream>
#include <streambuf>

using namespace std;
using Json = nlohmann::json;

namespace {

const std::string kOutputDirectory = "output_data";

void create_ouput_directory() {
  const char* path = kOutputDirectory.c_str();
  boost::filesystem::path dir(path);
  if(boost::filesystem::create_directory(dir)) {
    DEBUG("created output directory: " << kOutputDirectory);
  }
}

auto read_config(const std::string& config_file) {
  std::ifstream stream(config_file);
  std::stringstream buffer;
  buffer << stream.rdbuf();
  return Json::parse(buffer.str());
}

void save_prediction(const PredictionSet& prediction_set) {
  create_ouput_directory();
  std::ofstream file(
      kOutputDirectory + '/' + prediction_set.clusterizator_name() + "_prediction_set.csv");
  file << "company_name,predicted_class\n";
  for (const auto& [company_name, predicted_class] : prediction_set.class_by_company_name()) {
    file << '\"' << company_name << "\"," << predicted_class << '\n';
  }
}

void save_statistics(
    const StatisticsManager& statistics_manager, const std::string& clusterizator_name) {
  create_ouput_directory();
  std::ofstream file(
      kOutputDirectory + '/' + clusterizator_name + "_statistics.txt");
  auto statistics = statistics_manager.statistics(clusterizator_name);
  file << "score: " << statistics.score << '\n';
  file << "median_cluster_size: " << statistics.median_cluster_size << '\n';
  file << "average_cluster_size: " << statistics.average_cluster_size << '\n';
  file << "coefficient_gini: " << statistics.coefficient_gini << '\n';
}

auto get_prediction_sets(const Json& config) {
  DataProvider data_provider;
  for (auto source : config["sources"]) {
    data_provider.add_source({source["filename"], source["company_names_row"]});
  }

  auto companies = data_provider.company_names();

  ClusterizatorManager clusterizator_manager;
  clusterizator_manager.load_company_names(companies);

  return clusterizator_manager.prediction_sets();
}

void print_statistics(
    const StatisticsManager& statistics_manager, const std::string& clusterizator_name) {
  std::cout << "-----------------------------------\n";
  auto statistics = statistics_manager.statistics(clusterizator_name);
  std::cout << "clusterizator: " << statistics.name << std::endl;
  std::cout << "   score: " << statistics.score << std::endl;
  std::cout << "   median_cluster_size: " << statistics.median_cluster_size << std::endl;
  std::cout << "   average_cluster_size: " << statistics.average_cluster_size << std::endl;
  std::cout << "   coefficient_gini: " << statistics.coefficient_gini << std::endl;
  std::cout << "-----------------------------------\n";
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

  StatisticsManager statistics_manager;

  auto prediction_sets = get_prediction_sets(config);

  Arranger arranger(config["arranger_model"]);
  
  for (const auto& prediction_set : prediction_sets) {
    statistics_manager.process_prediction_set(prediction_set);
    auto prediction_score = arranger.GetScore(prediction_set);
    statistics_manager.set_score(prediction_set.clusterizator_name(), prediction_score);
    print_statistics(statistics_manager, prediction_set.clusterizator_name());
    save_prediction(prediction_set);
    save_statistics(statistics_manager, prediction_set.clusterizator_name());
  }

  return 0;
}

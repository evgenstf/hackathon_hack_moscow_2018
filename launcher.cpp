#include "base/logger/logger.h"
#include "base/command_parser/command_parser.h"
#include "external_libraries/json.hpp"
#include "data_provider/data_provider.h"
#include <iostream>
#include <fstream>
#include <streambuf>
#include <stdlib>

using namespace std;
using Json = nlohmann::json;

namespace {

auto read_config(const std::string& config_file) {
  std::ifstream stream(config_file);
  std::stringstream buffer;
  buffer << stream.rdbuf();
  return Json::parse(buffer.str());

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
  for (const auto& company : companies) {
    std::clog << company << std::endl;
  }


  return 0;
}

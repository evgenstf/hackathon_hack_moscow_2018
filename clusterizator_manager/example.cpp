// Author: Evgenii Kazakov. Github: @evgenstf
#include "clusterizator_manager.h"
#include <iostream>

int main(int arguments_count, char* arguments[]) {
  SET_LOG_LEVEL(Debug);
  std::cout << "Enter company count: ";
  size_t company_count = 0;
  std::cin >> company_count;
  std::vector<std::string> company_names(company_count);
  for (auto& company_name : company_names) {
    std::cin >> company_name;  
  }

  ClusterizatorManager manager;
  manager.load_company_names(company_names);

  auto prediction_sets = manager.prediction_sets();
  for (const auto& prediction_set : prediction_sets) {
    std::cout << "Clusterizator name: " << prediction_set.clusterizator_name() << std::endl;
    auto class_by_company_name = prediction_set.class_by_company_name();
    for (const auto& company_name_and_predicted_class : class_by_company_name) {
      auto company_name = company_name_and_predicted_class.first;
      auto predicted_class = company_name_and_predicted_class.second;
      std::cout << "   " << company_name << " " << predicted_class << std::endl;
    }
  }
  return 0;
}

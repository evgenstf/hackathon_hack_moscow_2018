#pragma once

#include <string>
#include <utility>
#include <vector>

class DataProvider {
public:
  DataProvider(const std::string& input_table);

  std::vector<std::string> company_names() const;

private:
  std::vector<std::string> company_names_from_csv(const std::string& input_table) const;

  std::vector<std::string> company_names(
    const std::vector<std::unordered_map<std::string, std::string>>& items,
    const std::string& company_field_name
  );

private:
  std::pair<std::string, std::string> input_table_;
};

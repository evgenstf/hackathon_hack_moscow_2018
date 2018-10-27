#pragma once

#include <string>
#include <utility>
#include <vector>
#include <unordered_map>

using DataSource = std::pair<std::string, std::string>;

class DataProvider {
public:
  DataProvider() = default;
  DataProvider(const std::vector<DataSource>& sources);

  std::vector<std::string> company_names() const;

  void add_source(const DataSource& source);

private:
  std::vector<std::string> company_names_from_csv(const DataSource& source) const;

  std::vector<std::string> company_names(
    const std::vector<std::unordered_map<std::string, std::string>>& items,
    const std::string& company_names_row
  ) const;

private:
  std::vector<DataSource> sources_;
};

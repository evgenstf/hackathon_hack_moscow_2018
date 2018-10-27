#include "data_provider.h"
#include "base/logger/logger.h"
#include "base/csv_parser/csv_parser.h"
#include <iostream>

namespace {
  std::string Strip(const std::string& s, const std::string& chars = "\" ") {
    const auto first = s.find_first_not_of(chars);
    const auto last = s.find_last_not_of(chars);
    if (first == std::string::npos)
      return "";
    return s.substr(s.find_first_not_of(chars), last - first);
  }
};

DataProvider::DataProvider(const std::vector<DataSource>& sources) {
  for (const auto& source : sources) {
    add_source(source);
  }
}

void DataProvider::add_source(const DataSource& source) {
  DEBUG("add source: filename: " << source.first << " company_names_row: " << source.second)
  sources_.push_back(source);
}

std::vector<std::string> DataProvider::company_names() const {
  std::vector<std::string> result;
  for (const auto& source : sources_) {
    DEBUG("try extract company_names from file: " << source.first)
    auto companies = company_names_from_csv(source);
    result.insert(result.end(), companies.begin(), companies.end());
  }
  return result;
}

std::vector<std::string> DataProvider::company_names_from_csv(
    const DataSource& source) const {
  CsvParser csv_parser(source.first);
  return company_names(csv_parser.items(), source.second);
}

std::vector<std::string> DataProvider::company_names(
  const std::vector<std::unordered_map<std::string, std::string>>& items,
  const std::string& company_names_row
) const {
  std::vector<std::string> company_names;
  company_names.reserve(items.size());
  for (const auto& item : items) {
    company_names.push_back(Strip(item.at(company_names_row)));
  }
  return company_names;
}

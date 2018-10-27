#include "data_provider.h"

#include "csv_parser/csv_parser.h"
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

DataProvider::DataProvider(const std::pair<std::string, std::string>& input_table)
  : input_table_(input_table)
{
}

std::vector<std::string> DataProvider::company_names() const {
  return company_names_from_csv(input_table_);
}

std::vector<std::string> DataProvider::company_names_from_csv(const std::pair<std::string, std::string>& input_table) const {
  latte::CsvParser csv_parser(input_table_.first);
  return company_names(csv_parser.items(), input_table_.second);
}

std::vector<std::string> DataProvider::company_names(
  const std::vector<std::unordered_map<std::string, std::string>>& items,
  const std::string& company_field_name
) const {
  std::vector<std::string> company_names;
  company_names.reserve(items.size());
  for (const auto& item : items) {
    company_names.push_back(Strip(item.at(company_field_name)));
  }
  return company_names;
}

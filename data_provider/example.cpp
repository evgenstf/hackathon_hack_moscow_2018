#include "data_provider.h"

#include <iostream>

int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::clog << "Usage: ./data_provider csv_file company_field_name\n";
    return 0;
  }
  DataProvider data_provider({std::string(argv[1]), std::string(argv[2])});
  for (const auto& company_name : data_provider.company_names()) {
    std::clog << company_name << "\n";
  }
}

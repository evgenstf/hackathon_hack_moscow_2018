#include "data_provider.h"

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::clog << "Usage: ./data_provider [csv_file]\n";
    return 0;
  }
  DataProvider data_provider(std::string(argv[1]));
  for (const auto& company_name : data_provider.company_names()) {
    std::clog << company_name << "\n";
  }
}

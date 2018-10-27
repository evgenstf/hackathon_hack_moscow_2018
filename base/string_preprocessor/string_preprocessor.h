#pragma once

#include <cctype>
#include <string>
#include <vector>

namespace preprocessing {

class StringPreprocessor {
public:
  StringPreprocessor();

  void set_forbidden_chars(const std::string& chars);

  void set_forbidden_words(const std::vector<std::string>& words);

  std::string preprocess(std::string original) const;

private:
  std::string chars_;
  std::vector<std::string> words_;
};

}

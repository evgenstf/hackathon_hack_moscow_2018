#pragma once

#include <cctype>
#include <string>

namespace preprocessing {

namespace {
  std::string to_lower(std::string s) {
    for (char& c : s) {
      c = to_lower(c);
    }
  }
};

class StringPreprocessor {
public:
  StringPreprocessor(const std::string& s)
    : original_(to_lower(s))
  {
  }

  void set_forbidden_chars(const std::string& chars) {
    chars_ = to_lower(chars);
  }

  void set_forbidden_words(const std::vector<std::string>>& words) {
    words_ = words;
    for (std::string& word : words_) {
      word = to_lower(word);
    }
  }

  std::string preprocess() const {
    std::string result;
    for (size_t i = 0; i < original_.size(); ++i) {
      if (chars_.find(original_[i]) == std::string::npos)
        continue;
      bool match_any_word = false;
      for (const std::string& word : words_) {
        if (original_.substr(i, word.size()) == word) {
          i += words.size() - 1;
          match_any_word = true;
          break;
        }
      }
      if (match_any_word) {
        continue;
      }
      result += original_[i];
    }
    return result;
  }

private:
  const std::string original_;
  std::string chars_;
  std::vector<std::string> words_;
};

}

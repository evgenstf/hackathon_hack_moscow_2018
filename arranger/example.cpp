// heh
#include "arranger.h"
#include "base/prediction_set.h"

#include <iostream>

int main(int arguments_count, char* arguments[]) {
    if (arguments_count < 2) {
      std::clog << "Usage: ./arranger [model_file*]\n";
      return 0;
    }
    Arranger arranger(arguments[1]);

    PredictionSet prediction_set("test");
    prediction_set.add_prediction("YANDEX", 0);
    prediction_set.add_prediction("GOOGLE", 0);

    std::cout << "score=" << arranger.GetScore(prediction_set) << std::endl;
}

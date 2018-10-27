// heh
#include "arranger.h"
#include "base/prediction_set.h"

#include <iostream>

int main() {
    Arranger arranger("tmp");

    PredictionSet prediction_set("test");
    prediction_set.add_prediction("YANDEX", 0);
    prediction_set.add_prediction("GOOGLE", 0);

    std::cout << "score=" << arranger.GetScore(prediction_set) << std::endl;
}

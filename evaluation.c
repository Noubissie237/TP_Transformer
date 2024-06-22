#include "evaluation.h"
#include <stdio.h>

double evaluate(Predictions preds, Data* data) {
    int correct = 0;
    for (int i = 0; i < data->num_reviews; i++) {
        if (preds.predictions[i] == data->labels[i]) {
            correct++;
        }
    }
    return (double)correct / data->num_reviews;
}

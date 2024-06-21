#ifndef PREPROCESSING_H
#define PREPROCESSING_H

#include "hdf5_reader.h"

typedef struct {
    // Définir la structure des données prétraitées
} PreprocessedData;

PreprocessedData preprocess(Dataset dataset);
void free_preprocessed_data(PreprocessedData pdata);

#endif // PREPROCESSING_H

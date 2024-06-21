#include <stdio.h>
#include "hdf5_reader.h"
#include "preprocessing.h"
#include "transformer.h"
#include "training.h"
#include "evaluation.h"

int main() {
    // Chargement des données
    Dataset dataset = load_hdf5("imdb_movies.hdf5");

    // Prétraitement des données
    PreprocessedData pdata = preprocess(dataset);

    // Initialisation du modèle Transformer
    Transformer transformer = init_transformer();

    // Entraînement du modèle
    train(transformer, pdata);

    // Évaluation du modèle
    evaluate(transformer, pdata);

    // Libération de la mémoire
    free_dataset(dataset);
    free_preprocessed_data(pdata);
    free_transformer(transformer);

    return 0;
}

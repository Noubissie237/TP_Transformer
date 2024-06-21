#include <stdio.h>
#include "transformer.h"

int main() {
    // Paramètres du transformer
    int num_encoder_layers = 6;  // Nombre de couches d'encodeur
    int num_decoder_layers = 6;  // Nombre de couches de décodeur
    int vocab_size = 10000;      // Taille du vocabulaire
    int d_model = 512;           // Dimension du modèle
    int d_ff = 2048;             // Dimension du feed-forward

    // Création d'un transformateur complet
    Transformer* transformer = create_transformer(num_encoder_layers, num_decoder_layers, vocab_size, d_model, d_ff);

    // Initialisation des poids et matrices (exemples)
    for (int i = 0; i < vocab_size; ++i) {
        for (int j = 0; j < d_model; ++j) {
            transformer->embedding_matrix->data[i * d_model + j] = (float)rand() / RAND_MAX;
        }
    }

    for (int i = 0; i < num_encoder_layers; ++i) {
        for (int j = 0; j < d_model; ++j) {
            for (int k = 0; k < d_model; ++k) {
                transformer->encoder_layers[i].attention_layer->query_weights->data[j * d_model + k] = (float)rand() / RAND_MAX;
                transformer->encoder_layers[i].attention_layer->key_weights->data[j * d_model + k] = (float)rand() / RAND_MAX;
                transformer->encoder_layers[i].attention_layer->value_weights->data[j * d_model + k] = (float)rand() / RAND_MAX;
                transformer->encoder_layers[i].attention_layer->output_weights->data[j * d_model + k] = (float)rand() / RAND_MAX;
            }
        }
    }

    for (int i = 0; i < num_decoder_layers; ++i) {
        for (int j = 0; j < d_model; ++j) {
            for (int k = 0; k < d_model; ++k) {
                transformer->decoder_layers[i].self_attention_layer->query_weights->data[j * d_model + k] = (float)rand() / RAND_MAX;
                transformer->decoder_layers[i].self_attention_layer->key_weights->data[j * d_model + k] = (float)rand() / RAND_MAX;
                transformer->decoder_layers[i].self_attention_layer->value_weights->data[j * d_model + k] = (float)rand() / RAND_MAX;
                transformer->decoder_layers[i].self_attention_layer->output_weights->data[j * d_model + k] = (float)rand() / RAND_MAX;
                
                transformer->decoder_layers[i].encoder_attention_layer->query_weights->data[j * d_model + k] = (float)rand() / RAND_MAX;
                transformer->decoder_layers[i].encoder_attention_layer->key_weights->data[j * d_model + k] = (float)rand() / RAND_MAX;
                transformer->decoder_layers[i].encoder_attention_layer->value_weights->data[j * d_model + k] = (float)rand() / RAND_MAX;
                transformer->decoder_layers[i].encoder_attention_layer->output_weights->data[j * d_model + k] = (float)rand() / RAND_MAX;
            }
            for (int k = 0; k < d_ff; ++k) {
                transformer->decoder_layers[i].feed_forward_layer->weights1->data[j * d_ff + k] = (float)rand() / RAND_MAX;
                transformer->decoder_layers[i].feed_forward_layer->weights2->data[k * d_model + j] = (float)rand() / RAND_MAX;
            }
        }
    }

    // Affichage de la matrice d'embedding (exemple)
    printf("Embedding Matrix:\n");
    print_matrix(transformer->embedding_matrix);

    // Libération de la mémoire du transformateur complet
    free_transformer(transformer);

    return 0;
}

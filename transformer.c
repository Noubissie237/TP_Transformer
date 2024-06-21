
#include "transformer.h"

/* --------------------------------- FONCTION PERMETTANT DE MANIPULER LA MATRICE --------------------------------- */

// Fonction pour créer une matrice
Matrix* create_matrix(int rows, int cols) {
    Matrix* matrix = (Matrix*)malloc(sizeof(Matrix));
    if (matrix == NULL) {
        fprintf(stderr, "Erreur d'allocation de mémoire pour la matrice\n");
        exit(EXIT_FAILURE);
    }
    matrix->rows = rows;
    matrix->cols = cols;
    matrix->data = (float*)malloc(rows * cols * sizeof(float));
    if (matrix->data == NULL) {
        fprintf(stderr, "Erreur d'allocation de mémoire pour les données de la matrice\n");
        free(matrix);
        exit(EXIT_FAILURE);
    }
    return matrix;
}

// Fonction pour libérer la mémoire d'une matrice
void free_matrix(Matrix* matrix) {
    if (matrix != NULL) {
        if (matrix->data != NULL) {
            free(matrix->data);
        }
        free(matrix);
    }
}

// Fonction pour afficher une matrice
void print_matrix(Matrix* matrix) {
    if (matrix == NULL) {
        fprintf(stderr, "Matrice nulle\n");
        return;
    }
    for (int i = 0; i < matrix->rows; ++i) {
        for (int j = 0; j < matrix->cols; ++j) {
            printf("%f ", matrix->data[i * matrix->cols + j]);
        }
        printf("\n");
    }
}


/* --------------------------------- FONCTION PERMETTANT DE MANIPULER LA MATRICE --------------------------------- */

// Fonction pour créer une couche d'attention
AttentionLayer* create_attention_layer(int d_model) {
    AttentionLayer* layer = (AttentionLayer*)malloc(sizeof(AttentionLayer));
    if (layer == NULL) {
        fprintf(stderr, "Erreur d'allocation de mémoire pour la couche d'attention\n");
        exit(EXIT_FAILURE);
    }
    
    layer->query_weights = create_matrix(d_model, d_model);
    layer->key_weights = create_matrix(d_model, d_model);
    layer->value_weights = create_matrix(d_model, d_model);
    layer->output_weights = create_matrix(d_model, d_model);
    
    return layer;
}

// Fonction pour libérer la mémoire d'une couche d'attention
void free_attention_layer(AttentionLayer* layer) {
    if (layer != NULL) {
        if (layer->query_weights != NULL) free_matrix(layer->query_weights);
        if (layer->key_weights != NULL) free_matrix(layer->key_weights);
        if (layer->value_weights != NULL) free_matrix(layer->value_weights);
        if (layer->output_weights != NULL) free_matrix(layer->output_weights);
        free(layer);
    }
}

// Fonction pour créer une couche de feed-forward
FeedForwardLayer* create_feed_forward_layer(int d_model, int d_ff) {
    FeedForwardLayer* layer = (FeedForwardLayer*)malloc(sizeof(FeedForwardLayer));
    if (layer == NULL) {
        fprintf(stderr, "Erreur d'allocation de mémoire pour la couche de feed-forward\n");
        exit(EXIT_FAILURE);
    }

    layer->weights1 = create_matrix(d_model, d_ff);
    layer->bias1 = create_matrix(1, d_ff);
    layer->weights2 = create_matrix(d_ff, d_model);
    layer->bias2 = create_matrix(1, d_model);

    return layer;
}

// Fonction pour libérer la mémoire d'une couche de feed-forward
void free_feed_forward_layer(FeedForwardLayer* layer) {
    if (layer != NULL) {
        if (layer->weights1 != NULL) free_matrix(layer->weights1);
        if (layer->bias1 != NULL) free_matrix(layer->bias1);
        if (layer->weights2 != NULL) free_matrix(layer->weights2);
        if (layer->bias2 != NULL) free_matrix(layer->bias2);
        free(layer);
    }
}

// Fonction pour créer une couche d'encodeur
EncoderLayer* create_encoder_layer(int d_model, int d_ff) {
    EncoderLayer* layer = (EncoderLayer*)malloc(sizeof(EncoderLayer));
    if (layer == NULL) {
        fprintf(stderr, "Erreur d'allocation de mémoire pour la couche d'encodeur\n");
        exit(EXIT_FAILURE);
    }

    layer->attention_layer = create_attention_layer(d_model);
    layer->feed_forward_layer = create_feed_forward_layer(d_model, d_ff);
    layer->norm1 = create_matrix(1, d_model);
    layer->norm2 = create_matrix(1, d_model);

    return layer;
}

// Fonction pour libérer la mémoire d'une couche d'encodeur
void free_encoder_layer(EncoderLayer* layer) {
    if (layer != NULL) {
        if (layer->attention_layer != NULL) free_attention_layer(layer->attention_layer);
        if (layer->feed_forward_layer != NULL) free_feed_forward_layer(layer->feed_forward_layer);
        if (layer->norm1 != NULL) free_matrix(layer->norm1);
        if (layer->norm2 != NULL) free_matrix(layer->norm2);
        free(layer);
    }
}

// Fonction pour créer une couche de décodeur
DecoderLayer* create_decoder_layer(int d_model, int d_ff) {
    DecoderLayer* layer = (DecoderLayer*)malloc(sizeof(DecoderLayer));
    if (layer == NULL) {
        fprintf(stderr, "Erreur d'allocation de mémoire pour la couche de décodeur\n");
        exit(EXIT_FAILURE);
    }

    layer->self_attention_layer = create_attention_layer(d_model);
    layer->encoder_attention_layer = create_attention_layer(d_model);
    layer->feed_forward_layer = create_feed_forward_layer(d_model, d_ff);
    layer->norm1 = create_matrix(1, d_model);
    layer->norm2 = create_matrix(1, d_model);
    layer->norm3 = create_matrix(1, d_model);

    return layer;
}

// Fonction pour libérer la mémoire d'une couche de décodeur
void free_decoder_layer(DecoderLayer* layer) {
    if (layer != NULL) {
        if (layer->self_attention_layer != NULL) free_attention_layer(layer->self_attention_layer);
        if (layer->encoder_attention_layer != NULL) free_attention_layer(layer->encoder_attention_layer);
        if (layer->feed_forward_layer != NULL) free_feed_forward_layer(layer->feed_forward_layer);
        if (layer->norm1 != NULL) free_matrix(layer->norm1);
        if (layer->norm2 != NULL) free_matrix(layer->norm2);
        if (layer->norm3 != NULL) free_matrix(layer->norm3);
        free(layer);
    }
}

// Fonction pour créer un transformateur complet
Transformer* create_transformer(int num_encoder_layers, int num_decoder_layers, int vocab_size, int d_model, int d_ff) {
    Transformer* transformer = (Transformer*)malloc(sizeof(Transformer));
    if (transformer == NULL) {
        fprintf(stderr, "Erreur d'allocation de mémoire pour le transformateur\n");
        exit(EXIT_FAILURE);
    }

    transformer->num_encoder_layers = num_encoder_layers;
    transformer->num_decoder_layers = num_decoder_layers;
    transformer->vocab_size = vocab_size;
    transformer->d_model = d_model;

    // Création des couches d'encodeur
    transformer->encoder_layers = (EncoderLayer*)malloc(num_encoder_layers * sizeof(EncoderLayer));
    if (transformer->encoder_layers == NULL) {
        fprintf(stderr, "Erreur d'allocation de mémoire pour les couches d'encodeur\n");
        free(transformer);
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < num_encoder_layers; ++i) {
        transformer->encoder_layers[i] = *create_encoder_layer(d_model, d_ff);
    }

    // Création des couches de décodeur
    transformer->decoder_layers = (DecoderLayer*)malloc(num_decoder_layers * sizeof(DecoderLayer));
    if (transformer->decoder_layers == NULL) {
        fprintf(stderr, "Erreur d'allocation de mémoire pour les couches de décodeur\n");
        free(transformer->encoder_layers);
        free(transformer);
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < num_decoder_layers; ++i) {
        transformer->decoder_layers[i] = *create_decoder_layer(d_model, d_ff);
    }

    // Création de la matrice d'embedding
    transformer->embedding_matrix = create_matrix(vocab_size, d_model);

    return transformer;
}

// Fonction pour libérer la mémoire d'un transformateur complet
void free_transformer(Transformer* transformer) {
    if (transformer != NULL) {
        if (transformer->encoder_layers != NULL) {
            for (int i = 0; i < transformer->num_encoder_layers; ++i) {
                free_encoder_layer(&transformer->encoder_layers[i]);
            }
            free(transformer->encoder_layers);
        }

        if (transformer->decoder_layers != NULL) {
            for (int i = 0; i < transformer->num_decoder_layers; ++i) {
                free_decoder_layer(&transformer->decoder_layers[i]);
            }
            free(transformer->decoder_layers);
        }

        if (transformer->embedding_matrix != NULL) {
            free_matrix(transformer->embedding_matrix);
        }

        free(transformer);
    }
}
#ifndef TRANSFORMER_H
#define TRANSFORMER_H

#include <stdio.h>
#include <stdlib.h>

// Structure pour représenter une matrice
typedef struct {
    float* data;
    int rows;
    int cols;
} Matrix;

// Structure pour représenter une couche d'attention
typedef struct {
    Matrix* query_weights;
    Matrix* key_weights;
    Matrix* value_weights;
    Matrix* output_weights;
} AttentionLayer;

// Structure pour représenter une couche de feed-forward
typedef struct {
    Matrix* weights1;
    Matrix* bias1;
    Matrix* weights2;
    Matrix* bias2;
} FeedForwardLayer;

// Structure pour représenter un encodeur
typedef struct {
    AttentionLayer* attention_layer;
    FeedForwardLayer* feed_forward_layer;
    Matrix* norm1;
    Matrix* norm2;
} EncoderLayer;

// Structure pour représenter un décodeur
typedef struct {
    AttentionLayer* self_attention_layer;
    AttentionLayer* encoder_attention_layer;
    FeedForwardLayer* feed_forward_layer;
    Matrix* norm1;
    Matrix* norm2;
    Matrix* norm3;
} DecoderLayer;

// Structure pour représenter un transformateur complet
typedef struct {
    EncoderLayer* encoder_layers;
    DecoderLayer* decoder_layers;
    Matrix* embedding_matrix;
    int num_encoder_layers;
    int num_decoder_layers;
    int vocab_size;
    int d_model;
} Transformer;

// Fonctions pour manipuler les matrices
Matrix* create_matrix(int rows, int cols);
void free_matrix(Matrix* matrix);
void print_matrix(Matrix* matrix);

// Fonctions pour initialiser et libérer les couches d'attention
AttentionLayer* create_attention_layer(int d_model);
void free_attention_layer(AttentionLayer* layer);

// Fonctions pour initialiser et libérer les couches de feed-forward
FeedForwardLayer* create_feed_forward_layer(int d_model, int d_ff);
void free_feed_forward_layer(FeedForwardLayer* layer);

// Fonctions pour initialiser et libérer les encodeurs et décodeurs
EncoderLayer* create_encoder_layer(int d_model, int d_ff);
void free_encoder_layer(EncoderLayer* layer);
DecoderLayer* create_decoder_layer(int d_model, int d_ff);
void free_decoder_layer(DecoderLayer* layer);

// Fonctions pour initialiser et libérer un transformateur complet
Transformer* create_transformer(int num_encoder_layers, int num_decoder_layers, int vocab_size, int d_model, int d_ff);
void free_transformer(Transformer* transformer);

#endif // TRANSFORMER_H

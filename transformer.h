#ifndef TRANSFORMER_H
#define TRANSFORMER_H
#include "data_processing.h"
#define MAX_PARAMETERS 1000

typedef struct {
    int num_layers;
    int d_model;
    int num_heads;
    int dff;
    int input_vocab_size;
    int target_vocab_size;
    float dropout_rate;

    int num_parameters;
    float encoder_params[MAX_PARAMETERS];
    float decoder_params[MAX_PARAMETERS];
} TransformerModel;

typedef struct {
    float learning_rate;
} Optimizer;

typedef struct {
    int num_predictions;
    int predictions[MAX_REVIEWS];
} Predictions;

void init_transformer(TransformerModel* model);
void save_model(TransformerModel* model, const char* filename);
void load_model(TransformerModel* model, const char* filename);

Optimizer create_adam_optimizer(float learning_rate);
void shuffle_data(Data* data);
void get_batch(Data* data, int batch_size, int batch_num, char input_sequences[MAX_REVIEWS][MAX_REVIEW_LENGTH], int labels[MAX_REVIEWS]);

void forward(TransformerModel* model, char input_sequences[MAX_REVIEWS][MAX_REVIEW_LENGTH], int batch_size, float* outputs);
float compute_loss(float* outputs, int* labels, int batch_size);
void backward(TransformerModel* model, float* logits, int* labels, int batch_size, int vocab_size);
float compute_cross_entropy_loss(float* logits, int* labels, int batch_size, int vocab_size);
void update_parameters(TransformerModel* model, Optimizer* optimizer);
void train_transformer(TransformerModel* model, Data* data);
Predictions predict(TransformerModel* model, Data* data);

#endif // TRANSFORMER_H

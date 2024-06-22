#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "transformer.h"
float encoder_gradients[700]; // Gradients de l'encodeur (tableau)
float decoder_gradients[700]; // Gradients du décodeur (tableau)

void init_transformer(TransformerModel* model) {
    model->num_layers = 6;
    model->d_model = 4;
    model->num_heads = 10;
    model->dff = 10;
    model->input_vocab_size = 8;
    model->target_vocab_size = 8;
    model->dropout_rate = 0.001f;

    model->num_parameters = model->num_layers * (4 * model->d_model * model->d_model + 2 * model->d_model) + 2 * model->d_model * model->target_vocab_size;

    for (int i = 0; i < model->num_parameters; i++) {
        model->encoder_params[i] = (float)rand() / RAND_MAX;
        model->decoder_params[i] = (float)rand() / RAND_MAX;
    }
}

void save_model(TransformerModel* model, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        fprintf(stderr, "Erreur d'ouverture du fichier de sauvegarde.\n");
        return;
    }

    fprintf(file, "%d %d %d %d %d %d %f\n", model->num_layers, model->d_model, model->num_heads, model->dff, model->input_vocab_size, model->target_vocab_size, model->dropout_rate);

    for (int i = 0; i < model->num_parameters; i++) {
        fprintf(file, "%f ", model->encoder_params[i]);
    }
    fprintf(file, "\n");

    for (int i = 0; i < model->num_parameters; i++) {
        fprintf(file, "%f ", model->decoder_params[i]);
    }
    fprintf(file, "\n");

    fclose(file);
}

void load_model(TransformerModel* model, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Erreur d'ouverture du fichier de chargement.\n");
        return;
    }

    fscanf(file, "%d %d %d %d %d %d %f\n", &model->num_layers, &model->d_model, &model->num_heads, &model->dff, &model->input_vocab_size, &model->target_vocab_size, &model->dropout_rate);

    for (int i = 0; i < model->num_parameters; i++) {
        fscanf(file, "%f", &model->encoder_params[i]);
    }

    for (int i = 0; i < model->num_parameters; i++) {
        fscanf(file, "%f", &model->decoder_params[i]);
    }

    fclose(file);
}

Optimizer create_adam_optimizer(float learning_rate) {
    Optimizer optimizer;
    optimizer.learning_rate = learning_rate;
    return optimizer;
}

void shuffle_data(Data* data) {
    srand(time(NULL));
    for (int i = data->num_reviews - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        char temp_review[MAX_REVIEW_LENGTH];
        strcpy(temp_review, data->reviews[i]);
        strcpy(data->reviews[i], data->reviews[j]);
        strcpy(data->reviews[j], temp_review);

        int temp_label = data->labels[i];
        data->labels[i] = data->labels[j];
        data->labels[j] = temp_label;
    }
}

void get_batch(Data* data, int batch_size, int batch_num, char input_sequences[MAX_REVIEWS][MAX_REVIEW_LENGTH], int labels[MAX_REVIEWS]) {
    int start_index = batch_num * batch_size;
    int end_index = start_index + batch_size;
    if (end_index > data->num_reviews) {
        end_index = data->num_reviews;
    }
    for (int i = start_index; i < end_index; i++) {
        strcpy(input_sequences[i - start_index], data->reviews[i]);
        labels[i - start_index] = data->labels[i];
    }
}

void forward(TransformerModel* model, char input_sequences[MAX_REVIEWS][MAX_REVIEW_LENGTH], int batch_size, float* outputs) {
    for (int i = 0; i < batch_size; i++) {
        outputs[i] = 0.5; // Faux résultat
    }
}

float compute_loss(float* outputs, int* labels, int batch_size) {
    float loss = 0.0;
    for (int i = 0; i < batch_size; i++) {
        loss += (outputs[i] - labels[i]) * (outputs[i] - labels[i]);
    }
    return loss / batch_size;
}

void backward(TransformerModel* model, float* logits, int* labels, int batch_size, int vocab_size) {
    for (int i = 0; i < model->num_parameters; i++) {
        encoder_gradients[i] = 0.01f;
        decoder_gradients[i] = 0.01f;
    }
}

float compute_cross_entropy_loss(float* logits, int* labels, int batch_size, int vocab_size) {
    float loss = 0.0;
    for (int i = 0; i < batch_size; i++) {
        loss -= log(logits[i * vocab_size + labels[i]]);
    }
    return loss / batch_size;
}

void update_parameters(TransformerModel* model, Optimizer* optimizer) {
    float learning_rate = optimizer->learning_rate;
    for (int i = 0; i < model->num_parameters; i++) {
        model->encoder_params[i] -= learning_rate * encoder_gradients[i];
        model->decoder_params[i] -= learning_rate * decoder_gradients[i];
    }
}

void train_transformer(TransformerModel* model, Data* data) {
    int batch_size = 32;
    int num_batches = (data->num_reviews + batch_size - 1) / batch_size;

    Optimizer optimizer = create_adam_optimizer(0.001);

    for (int epoch = 0; epoch < 10; epoch++) {
        shuffle_data(data);
        for (int batch_num = 0; batch_num < num_batches; batch_num++) {
            char input_sequences[MAX_REVIEWS][MAX_REVIEW_LENGTH];
            int labels[MAX_REVIEWS];
            get_batch(data, batch_size, batch_num, input_sequences, labels);

            float logits[MAX_REVIEWS];
            forward(model, input_sequences, batch_size, logits);

            float loss = compute_cross_entropy_loss(logits, labels, batch_size, model->target_vocab_size);
            backward(model, logits, labels, batch_size, model->target_vocab_size);

            update_parameters(model, &optimizer);
        }
    }
}

Predictions predict(TransformerModel* model, Data* data) {
    Predictions predictions;
    predictions.num_predictions = data->num_reviews;

    float logits[MAX_REVIEWS];
    forward(model, data->reviews, data->num_reviews, logits);

    for (int i = 0; i < data->num_reviews; i++) {
        predictions.predictions[i] = logits[i] > 0.5 ? 1 : 0;
    }

    return predictions;
}

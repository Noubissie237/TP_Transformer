#include "data_processing.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Fonction pour lire un fichier CSV
Data read_csv(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }
    
    Data data;
    data.num_reviews = 0;
    
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file) && data.num_reviews < MAX_REVIEWS) {
        char* token = strtok(line, ",");
        if (token) {
            strncpy(data.reviews[data.num_reviews], token, MAX_REVIEW_LENGTH - 1);
            data.reviews[data.num_reviews][MAX_REVIEW_LENGTH - 1] = '\0'; // Assurez-vous que la chaîne est terminée
            token = strtok(NULL, ",");
            if (token) {
                data.labels[data.num_reviews] = map_sentiments(token);
                data.num_reviews++;
            }
        }
    }

    fclose(file);
    return data;
}

int map_sentiments(char* sentiment) {
    if (strcmp(sentiment, "positive") == 0) {
        return 1;
    }
    return 0;
}

void to_lowercase(char* text) {
    for (int i = 0; text[i]; i++) {
        text[i] = tolower(text[i]);
    }
}

void remove_html(char* text) {
    char buffer[MAX_REVIEW_LENGTH];
    char* p = buffer;
    int inside_tag = 0;

    while (*text) {
        if (*text == '<') {
            inside_tag = 1;
        } else if (*text == '>') {
            inside_tag = 0;
        } else if (!inside_tag) {
            *p++ = *text;
        }
        text++;
    }
    *p = '\0';
    strcpy(text - (p - buffer), buffer);
}

void remove_url(char* text) {
    char buffer[MAX_REVIEW_LENGTH];
    char* p = buffer;

    while (*text) {
        if (strncmp(text, "http://", 7) == 0 || strncmp(text, "https://", 8) == 0 || strncmp(text, "www.", 4) == 0) {
            while (*text && *text != ' ') text++;
        } else {
            *p++ = *text++;
        }
    }
    *p = '\0';
    strcpy(text - (p - buffer), buffer);
}

void remove_punctuations(char* text) {
    char buffer[MAX_REVIEW_LENGTH];
    char* p = buffer;

    while (*text) {
        if (!ispunct(*text)) {
            *p++ = *text;
        } else {
            *p++ = ' ';
        }
        text++;
    }
    *p = '\0';
    strcpy(text - (p - buffer), buffer);
}

void remove_emojis(char* text) {
    char buffer[MAX_REVIEW_LENGTH];
    char* p = buffer;

    while (*text) {
        if ((*text & 0xF0) == 0xF0) {
            text++;
            while ((*text & 0x80) == 0x80) text++;
        } else {
            *p++ = *text++;
        }
    }
    *p = '\0';
    strcpy(text - (p - buffer), buffer);
}

void remove_stop_words(char* text) {
    char* stop_words[] = {"a", "an", "and", "the", "is", "in", "it", "of", "to", "for", "on", "with", NULL};
    char buffer[MAX_REVIEW_LENGTH];
    char* p = buffer;
    char* word = strtok(text, " ");

    while (word != NULL) {
        int is_stop_word = 0;
        for (int i = 0; stop_words[i] != NULL; i++) {
            if (strcmp(word, stop_words[i]) == 0) {
                is_stop_word = 1;
                break;
            }
        }
        if (!is_stop_word) {
            strcpy(p, word);
            p += strlen(word);
            *p++ = ' ';
        }
        word = strtok(NULL, " ");
    }
    *p = '\0';
    strcpy(text - (p - buffer), buffer);
}

void stem_words(char* text) {
    char buffer[MAX_REVIEW_LENGTH];
    char* p = buffer;
    char* word = strtok(text, " ");

    while (word != NULL) {
        strncpy(p, word, 5);
        p += strlen(word) > 5 ? 5 : strlen(word);
        *p++ = ' ';
        word = strtok(NULL, " ");
    }
    *p = '\0';
    strcpy(text - (p - buffer), buffer);
}

void pre_process(Data* data) {
    for (int i = 0; i < data->num_reviews; i++) {
        to_lowercase(data->reviews[i]);
        remove_html(data->reviews[i]);
        remove_url(data->reviews[i]);
        remove_punctuations(data->reviews[i]);
        remove_emojis(data->reviews[i]);
        remove_stop_words(data->reviews[i]);
        stem_words(data->reviews[i]);
    }
}

void prepare_data(Data* data, int max_len) {
    for (int i = 0; i < data->num_reviews; i++) {
        char* review = data->reviews[i];
        if (strlen(review) > max_len) {
            review[max_len] = '\0';
        }
    }
}

// Fonction pour vider le buffer d'entrée
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
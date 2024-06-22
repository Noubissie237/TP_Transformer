#ifndef DATA_PROCESSING_H
#define DATA_PROCESSING_H

#define MAX_LINE_LENGTH 400
#define MAX_REVIEWS 180
#define MAX_REVIEW_LENGTH 200

typedef struct {
    char reviews[MAX_REVIEWS][MAX_REVIEW_LENGTH];
    int labels[MAX_REVIEWS];
    int num_reviews;
} Data;

Data read_csv(const char* filename);
int map_sentiments(char* sentiment);
void to_lowercase(char* text);
void remove_html(char* text);
void remove_url(char* text);
void remove_punctuations(char* text);
void remove_emojis(char* text);
void remove_stop_words(char* text);
void stem_words(char* text);
void pre_process(Data* data);
void prepare_data(Data* data, int max_len);
void clear_input_buffer();

#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "transformer.h"
#include "data_processing.h"
#include "evaluation.h"

int main() {
    printf("Lecture des données...");
    Data data = read_csv("dataset.csv");
    if (data.num_reviews == 0) {
        fprintf(stderr, "Erreur lors de la lecture du fichier CSV.\n");
        return 1;
    }
    printf("OK\n");

    printf("Prétraitement des données...");
    pre_process(&data);
    prepare_data(&data, MAX_REVIEW_LENGTH);
    printf("OK\n");

    printf("Initialisation du modèle Transformer...");
    TransformerModel model;
    init_transformer(&model);
    printf("OK\n");

    printf("Entraînement du modèle Transformer...");
    train_transformer(&model, &data);
    printf("OK\n");

    printf("Sauvegarde du modèle...");
    save_model(&model, "model.txt");
    printf("OK\n");

    printf("Chargement du modèle...");
    TransformerModel loaded_model;
    load_model(&loaded_model, "model.txt");
    printf("OK\n");
    int choix;

    do
    {
        printf("\n\nChoisir une option \n");
        printf("\t0. Quitter\n");
        printf("\t1. Simuler le transformer\n");
        printf("Choix : ");
        scanf("%d", &choix);

        clear_input_buffer();
        
        switch(choix)
        {
            case 0 : 
                printf("\nSortie du programme...\n");
                break;
            
            case 1 :

                printf("\n ------------------ SIMULATION ------------------ \n\n");
                // Phrases à tester
                char reviews[1][MAX_REVIEW_LENGTH];

                printf("Entrez un commentaire (En anglais) : ");
                
                // Utilisation de fgets pour récupérer le commentaire avec les espaces
                if (fgets(*reviews, sizeof(reviews[0]), stdin)) {
                    // Suppression du saut de ligne à la fin de la chaîne
                    size_t len = strlen(*reviews);
                    if (len > 0 && (*reviews)[len-1] == '\n') {
                        (*reviews)[len-1] = '\0';
                    }
                } else {
                    printf("Erreur de lecture.\n");
                }

                // Prétraitement des phrases et prédiction
                Predictions preds[2]; // Tableau pour stocker les prédictions des deux phrases

                for (int i = 0; i < 1; ++i) {
                    char processed_review[MAX_REVIEW_LENGTH];
                    strcpy(processed_review, reviews[i]);
                    to_lowercase(processed_review);
                    remove_html(processed_review);
                    pre_process(&data); // Assurez-vous d'adapter le prétraitement selon vos besoins

                    // Création d'une structure Data pour la prédiction
                    Data test_data;
                    test_data.num_reviews = 1;
                    strcpy(test_data.reviews[0], processed_review);

                    // Prédiction
                    preds[i] = predict(&loaded_model, &test_data);

                    // Affichage des résultats
                    printf("\nPhrase : %s\n", reviews[i]);
                    printf("\nImpression : %s\n", preds[i].predictions[0] == 1 ? "Positive" : "Negative");
                    printf("\n");
                }

                // Calcul de l'exactitude après avoir obtenu toutes les prédictions
                printf("Évaluation\n");
                double accuracy = 0.0;
                for (int i = 0; i < 2; ++i) {
                    accuracy += evaluate(preds[i], &data);
                }
                accuracy /= 2.0; // Moyenne de l'exactitude pour les deux prédictions
                printf("Précision : %.2f%%\n", accuracy * 100);
                break;

            default:
                printf("Veuillez entrer soit 0 soit 1 en fonction de ce que vous souhaitez faire\n");
                break;
        }
        
    } while (choix != 0);


    printf("Libération de la mémoire\n");
    // Assurez-vous de libérer toute la mémoire allouée dynamiquement

    return 0;
}

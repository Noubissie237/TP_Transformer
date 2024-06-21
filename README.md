## Apres Elaboration du fichier d'entete


1. Matrice : Une structure de base pour représenter une matrice.
2. AttentionLayer : Représente une couche d'attention avec des matrices de poids pour les requêtes, clés, valeurs et la sortie.
3. FeedForwardLayer : Représente une couche de réseau feed-forward avec deux couches de poids et biais.
4. EncoderLayer : Contient une couche d'attention et une couche feed-forward, ainsi que des matrices de normalisation.
5. DecoderLayer : Similaire à EncoderLayer, mais avec une couche d'attention supplémentaire pour les encodeurs.
6. Transformer : La structure principale qui regroupe les encodeurs, les décodeurs et la matrice d'embedding.
Prochaines Étapes
7. Implémenter les Fonctions : Implémentez les fonctions déclarées dans transformer.h dans un fichier source transformer.c.
8. Gestion de la Mémoire : Assurez-vous de bien gérer l'allocation et la libération de la mémoire pour éviter les fuites.
9. Algorithmes d'Apprentissage : Ajoutez les algorithmes nécessaires pour l'entraînement et l'inférence du transformateur.

Ce squelette vous donne un bon point de départ pour structurer votre transformateur en C. Vous pouvez ensuite ajouter plus de détails et fonctionnalités au fur et à mesure.


## Apres l'ajout des fonctions permettant de manipuler les matrice

### Explication

Matrice : Une structure de base pour représenter une matrice.
AttentionLayer : Représente une couche d'attention avec des matrices de poids pour les requêtes, clés, valeurs et la sortie.
FeedForwardLayer : Représente une couche de réseau feed-forward avec deux couches de poids et biais.
EncoderLayer : Contient une couche d'attention et une couche feed-forward, ainsi que des matrices de normalisation.
DecoderLayer : Similaire à EncoderLayer, mais avec une couche d'attention supplémentaire pour les encodeurs.
Transformer : La structure principale qui regroupe les encodeurs, les décodeurs et la matrice d'embedding.
Prochaines Étapes
Implémenter les Fonctions : Implémentez les fonctions déclarées dans transformer.h dans un fichier source transformer.c.
Gestion de la Mémoire : Assurez-vous de bien gérer l'allocation et la libération de la mémoire pour éviter les fuites.
Algorithmes d'Apprentissage : Ajoutez les algorithmes nécessaires pour l'entraînement et l'inférence du transformateur.
Ce squelette vous donne un bon point de départ pour structurer votre transformateur en C. Vous pouvez ensuite ajouter plus de détails et fonctionnalités au fur et à mesure.


#####
Explication des Fonctions
create_attention_layer :

Cette fonction alloue de la mémoire pour une structure AttentionLayer.
Elle initialise les matrices de poids query_weights, key_weights, value_weights et output_weights en appelant la fonction create_matrix avec les dimensions appropriées (dans ce cas, d_model x d_model).
Si l'allocation de mémoire échoue, elle affiche un message d'erreur et termine le programme.
free_attention_layer :

Cette fonction libère la mémoire allouée pour une structure AttentionLayer.
Elle vérifie si les matrices de poids ne sont pas nulles avant de les libérer en appelant free_matrix.
Enfin, elle libère la mémoire allouée pour la structure AttentionLayer.
Compilation et Utilisation
Pour utiliser ces fonctions, vous devez inclure le fichier d'en-tête transformer.h dans votre fichier source et lier correctement les fichiers lors de la compilation.

#####

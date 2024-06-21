# TP_Transformer

###installation de hdf5.h
#### HDF5 :
 Installez la bibliothèque HDF5. Si vous utilisez une distribution Linux basée sur Debian (comme Ubuntu), vous pouvez l'installer en utilisant apt-get :

sh

sudo apt-get update
sudo apt-get install libhdf5-dev

#### CBLAS :
Installez la bibliothèque CBLAS pour les opérations de calcul matriciel :

sh

sudo apt-get install libblas-dev
sudo apt-get install liblapack-dev


#### Étape 1: Créer ou ouvrir le fichier c_cpp_properties.json

    Ouvrez Visual Studio Code.
    Naviguez vers votre espace de travail ou projet.
    Créez un dossier nommé .vscode à la racine de votre projet si ce n'est pas déjà fait.
    Dans le dossier .vscode, créez un fichier nommé c_cpp_properties.json. Si le fichier existe déjà, ouvrez-le.

#### Étape 2: Modifier c_cpp_properties.json

    Ouvrez le fichier c_cpp_properties.json.
    Ajoutez la configuration suivante pour inclure les chemins nécessaires :

json

{
    "configurations": [
        {
            "name": "Linux",
            "includePath": [
                "${workspaceFolder}/**",
                "/usr/include/hdf5/serial",
                "/usr/include/x86_64-linux-gnu"
            ],
            "defines": [],
            "compilerPath": "/usr/bin/gcc",
            "cStandard": "c11",
            "cppStandard": "c++17",
            "intelliSenseMode": "linux-gcc-x64"
        }
    ],
    "version": 4
}

#### Étape 3: Sauvegarder et redémarrer Visual Studio Code

    Sauvegardez le fichier c_cpp_properties.json.
    Redémarrez Visual Studio Code pour que les changements prennent effet.

    #### Étape 1: Vérifiez l'emplacement du fichier hdf5.h

    Recherchez le fichier hdf5.h pour vérifier son emplacement exact.
        Utilisez la commande find pour localiser le fichier :

        bash

        find /usr/include -name hdf5.h

        Vous devriez obtenir quelque chose comme /usr/include/hdf5/serial/hdf5.h ou un chemin similaire.

#### Étape 2: Mettez à jour la commande gcc

    Ajoutez le chemin correct au includePath dans la commande gcc :
        Supposons que le fichier se trouve dans /usr/include/hdf5/serial, vous devrez mettre à jour votre commande gcc comme suit :

        bash

gcc -I/usr/include/hdf5/serial hdf5_reader.c -o p -lhdf5
Puisque le fichier hdf5.h se trouve dans /usr/include/hdf5/serial/, vous devez inclure ce chemin dans votre commande gcc. Voici la commande mise à jour :

bash

gcc -I/usr/include/hdf5/serial hdf5_reader.c -o p -lhdf5


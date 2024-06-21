import PyPDF2

def supprimer_pages_pdf(fichier_entree, fichier_sortie, pages_a_supprimer):
    # Ouvrir le fichier PDF en mode lecture
    pdf_lecteur = PyPDF2.PdfFileReader(fichier_entree)
    pdf_ecrivain = PyPDF2.PdfFileWriter()

    print(f"Nombre total de pages dans le fichier : {pdf_lecteur.numPages}")
    print(f"Pages à supprimer : {pages_a_supprimer}")

    # Boucle pour ajouter les pages restantes
    for page in range(pdf_lecteur.numPages):
        if page not in pages_a_supprimer:
            page_obj = pdf_lecteur.getPage(page)
            pdf_ecrivain.addPage(page_obj)
            print(f"Ajout de la page {page + 1}")  # Affiche le numéro de la page ajoutée (1-indexé)
        else:
            print(f"Suppression de la page {page + 1}")  # Affiche le numéro de la page supprimée (1-indexé)

    # Enregistrer le nouveau PDF
    with open(fichier_sortie, 'wb') as fichier_sortie_pdf:
        pdf_ecrivain.write(fichier_sortie_pdf)
    print(f"Le nouveau fichier PDF a été enregistré sous {fichier_sortie}")

# Exemple d'utilisation
fichier_entree = 'Transformers.pdf'
fichier_sortie = 'Transformers.pdf'

# Liste des pages à supprimer (0-indexé)
pages_a_supprimer = [13, 20, 22, 24]  # Numéros de pages à supprimer (0-indexé)

supprimer_pages_pdf(fichier_entree, fichier_sortie, pages_a_supprimer)

import PyPDF2

def supprimer_pages_pdf(fichier_entree, fichier_sortie, pages_a_supprimer):
    # Ouvrir le fichier PDF en mode lecture
    pdf_lecteur = PyPDF2.PdfFileReader(fichier_entree)
    pdf_ecrivain = PyPDF2.PdfFileWriter()

    # Boucle pour ajouter les pages restantes
    for page in range(pdf_lecteur.numPages):
        if page not in pages_a_supprimer:
            page_obj = pdf_lecteur.getPage(page)
            pdf_ecrivain.addPage(page_obj)

    # Enregistrer le nouveau PDF
    with open(fichier_sortie, 'wb') as fichier_sortie_pdf:
        pdf_ecrivain.write(fichier_sortie_pdf)

# Exemple d'utilisation
fichier_entree = 'Transformers.pdf'
fichier_sortie = 'Transformers1.pdf'

# Générer la liste des pages à supprimer (0-indexé)
pages_a_supprimer = list(range(27, 35))  # 431 non inclus

supprimer_pages_pdf(fichier_entree, fichier_sortie, pages_a_supprimer)

'''
    This is a project management tool for ESP32 & Fingerprint Sensor
'''

# Author: DBIBIH  OUSSAMA
# Date: 2021-07-01
# Version: 1.0
# Description: This is a project management tool for ESP32 & Fingerprint Sensor
# project.
# It allows to evaluate the project indicators for each day of the week and
# display the results in a graphical form.
# The indicators are divided into 5 categories: Costs, Quality, Time, Human
# Resources and Management.
# The user can enter values between 1 and 5 for the first 4 categories and 'OK'
# or 'KO' for the Management category.

import tkinter as tk
from tkinter import ttk, messagebox
import matplotlib.pyplot as plt


def afficher_graphique():
    """Affiche un graphique basé sur les valeurs
    saisies pour chaque
    jour de la semaine."""
    try:
        # Récupération des valeurs saisies pour chaque jour de la semaine
        valeurs_par_jour = {}
        for jour_semaine, entries in entries_par_jour.items():
            valeurs_par_jour[jour_semaine] = {
                "Coûts": [int(entry.get()) for entry in entries["Coûts"]],
                "Qualité": [int(entry.get()) for entry in entries["Qualité"]],
                "Temps": [int(entry.get()) for entry in entries["Temps"]],
                "Humains": [int(entry.get()) for entry in entries["Humains"]],
                "Gestion": [
                    entry.get().strip().upper() for entry in entries["Gestion"]
                ],
            }

        # Vérification des valeurs des indicateurs
        for jour_semaine, valeurs in valeurs_par_jour.items():
            if not all(1 <= v <= 5 for v in valeurs["Coûts"] + valeurs["Qualité"] +
                       valeurs["Temps"] + valeurs["Humains"]):
                messagebox.showerror(
                    "Erreur",
                    f"Veuillez entrer des valeurs en 1 et 5 ({jour_semaine})."
                )
                return
            if not all(v in ["OK", "KO"] for v in valeurs["Gestion"]):
                messagebox.showerror(
                    "Erreur",
                    f"Veuillez entrer 'OK' ou 'KO' ({jour_semaine})."
                )
                return

        # Création des graphiques pour chaque jour
        for jour_semaine, valeurs in valeurs_par_jour.items():
            plt.figure(figsize=(10, 6))
            for i, (categorie, data) in enumerate(valeurs.items()):
                if categorie != "Gestion":
                    plt.subplot(2, 2, i + 1)
                    plt.barh(
                        [categorie] * len(data), data,
                        color=["red" if v == 1 else "yellow" if v <= 3 else "green" for v in data],
                        edgecolor="black"
                    )
                    plt.xlabel("Niveau (1 = Mauvais, 5 = Bon)")
                    plt.title(f"{jour} - {categorie}")
            plt.tight_layout()
            plt.show()

    except ValueError:
        messagebox.showerror("Erreur", "Veuillez entrer: valeurs numériques")


# Création de l'interface Tkinter
root = tk.Tk()
root.title("Évaluation des Indicateurs - Projet ESP32 & Capteur d'Empreintes")

# Ajout d'onglets pour les jours de la semaine
notebook = ttk.Notebook(root)
notebook.pack(expand=True, fill='both')

jours_semaine = [
    "Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi", "Dimanche"
]
sections = {
    "Coûts": ["Budget actuel", "Budget prévisionnel", "Budget de vente"],
    "Qualité": [
        "Sensibilité capteur", "Temps de réaction", "Niveau détection",
        "Sécurité", "Résistance"
    ],
    "Temps": [
        "Comparaison dates", "Jours restants", "Jours travaillés",
        "Présences dequipes"
    ],
    "Humains": [
        "Charge de travail", "Satisfaction des employés", "Formation reçue",
        "Communication interne"
    ],
    "Gestion": ["Management de projet (OK/KO)", "Délai de livraison (OK/KO)"]
}

entries_par_jour = {}

for jour in jours_semaine:
    frame = ttk.Frame(notebook)
    notebook.add(frame, text=jour)
    entries_par_jour[jour] = {}
    row = 0
    for section, labels in sections.items():
        ttk.Label(
            frame, text=f"--- {section} ---", font=("Arial", 10, "bold")
        ).grid(row=row, column=0, columnspan=2, pady=5)
        row += 1
        section_entries = []
        for label in labels:
            ttk.Label(frame, text=label).grid(row=row, column=0, padx=10, pady=5, sticky='w')
            entry = ttk.Entry(frame)
            entry.grid(row=row, column=1, padx=10, pady=5)
            section_entries.append(entry)
            row += 1
        entries_par_jour[jour][section] = section_entries

# Bouton pour afficher le graphique
ttk.Button(root, text="Graphique", command=afficher_graphique).pack(pady=10)

root.mainloop()

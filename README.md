# Conception et Développement d'une Application Console de Gestion d'Agence de Voyage (Cotonou)

## 1. Énoncé du Problème
Une agence de voyage située à Cotonou souhaite informatiser le secteur de ses vols et des réparations (modifications) de billets d'avion. L'application console doit permettre de gérer les opérations suivantes :
* Gestion des passagers
* Gestion des réservations
* Gestion des vols
* Gestion des paiements et annulations

---

## 2. Identification des Classes, Attributs et Méthodes

### 2.1. Classe `Passager`
* **Attributs :**
  * `idPassager` (`string`) : Identifiant unique du passager
  * `nom` (`string`) : Nom de famille du passager
  * `prenom` (`string`) : Prénom du passager
  * `passeport` (`string`) : Numéro de passeport
  * `telephone` (`string`) : Numéro de téléphone
* **Méthodes :**
  * `getId()` : Retourne l'identifiant du passager
  * `getNomComplet()` : Retourne le nom complet
  * `afficher()` : Affiche les informations du passager

### 2.2. Classe `Vol`
* **Attributs :**
  * `numeroVol` (`string`) : Code unique du vol (ex. AF802)
  * `villeDepart` (`string`) : Ville de départ (ex. Cotonou)
  * `villeArrivee` (`string`) : Ville de destination
  * `dateHeure` (`string`) : Date et heure du départ
  * `prixBase` (`double`) : Tarif du billet en FCFA
  * `placesDisponibles` (`int`) : Nombre de sièges restants
* **Méthodes :**
  * `reserverPlace()` : Décrémente le nombre de places disponibles
  * `libererPlace()` : Incrémente le nombre de places disponibles
  * `afficher()` : Affiche les détails du vol

### 2.3. Classe `Paiement`
* **Attributs :**
  * `idPaiement` (`string`) : Identifiant unique de la transaction
  * `montant` (`double`) : Montant payé en FCFA
  * `modePaiement` (`string`) : Moyen de paiement (Cash, Mobile Money, Carte)
  * `estPaye` (`bool`) : Statut du paiement (`true` = Payé, `false` = Remboursé/Annulé)
* **Méthodes :**
  * `annulerPaiement()` : Passe le statut à remboursé/annulé
  * `afficher()` : Affiche les détails du paiement

### 2.4. Classe `Reservation`
* **Attributs :**
  * `idReservation` (`string`) : Identifiant unique de la réservation
  * `passager` (`Passager*`) : Référence vers le passager concerné
  * `vol` (`Vol*`) : Référence vers le vol réservé
  * `statut` (`string`) : État de la réservation (`Confirmee`, `Annulee`)
  * `paiement` (`Paiement`) : Paiement associé à la réservation
* **Méthodes :**
  * `reparerBillet(Vol* nouveauVol)` : Modifie le vol associé au billet et met à jour les places
  * `annulerReservation()` : Annule la réservation, libère la place sur le vol et rembourse le paiement
  * `afficher()` : Affiche le récapitulatif complet de la réservation

---

## 3. Associations et Multiplicités

1. **Passager — Reservation (`1` à `0..*`) :**
   * Un passager peut effectuer zéro ou plusieurs réservations.
   * Une réservation est associée à un et un seul passager.
2. **Vol — Reservation (`1` à `0..*`) :**
   * Un vol peut comporter zéro ou plusieurs réservations.
   * Une réservation concerne un et un seul vol à la fois.
3. **Reservation — Paiement (`1` à `1`) :**
   * Chaque réservation confirmée est liée à un paiement unique.
   * Chaque paiement correspond à une seule réservation.

---

## 4. Diagramme de Classe UML

```text
+-----------------------+       1        * +-------------------------+       *        1 +-----------------------+
|       Passager        |------------------|       Reservation       |------------------|          Vol          |
+-----------------------+                  +-------------------------+                  +-----------------------+
| - idPassager : string |                  | - idReservation : string|                  | - numeroVol : string  |
| - nom : string        |                  | - statut : string       |                  | - villeDepart : string|
| - prenom : string     |                  +-------------------------+                  | - villeArrivee: string|
| - passeport : string  |                  | + reparerBillet()       |                  | - dateHeure : string  |
| - telephone : string  |                  | + annulerReservation()  |                  | - prixBase : double   |
+-----------------------+                  | + afficher()            |                  | - placesDisponibles   |
| + getId()             |                  +-------------------------+                  +-----------------------+
| + getNomComplet()     |                               | 1                             | + reserverPlace()     |
| + afficher()          |                               |                               | + libererPlace()      |
+-----------------------+                               | 1                             | + afficher()          |
                                           +-------------------------+                  +-----------------------+
                                           |        Paiement         |
                                           +-------------------------+
                                           | - idPaiement : string   |
                                           | - montant : double      |
                                           | - modePaiement : string |
                                           | - estPaye : bool        |
                                           +-------------------------+
                                           | + annulerPaiement()     |
                                           | + afficher()            |
                                           +-------------------------+
```

---

## 5. Compilation et Exécution

Pour compiler et exécuter le programme C++ fourni dans `main.cpp` :

```bash
g++ -std=c++17 main.cpp -o agence_voyage
./agence_voyage
```

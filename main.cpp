#include <iostream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

// 1. Classe Passager
class Passager {
private:
    string idPassager;
    string nom;
    string prenom;
    string passeport;
    string telephone;

public:
    Passager() {}
    Passager(string id, string n, string p, string pass, string tel)
        : idPassager(id), nom(n), prenom(p), passeport(pass), telephone(tel) {}

    string getId() const { return idPassager; }
    string getNomComplet() const { return prenom + " " + nom; }

    void afficher() const {
        cout << "ID: " << idPassager << " | Nom: " << prenom << " " << nom
             << " | Passeport: " << passeport << " | Tel: " << telephone << endl;
    }
};

// 2. Classe Vol
class Vol {
private:
    string numeroVol;
    string villeDepart;
    string villeArrivee;
    string dateHeure;
    double prixBase;
    int placesDisponibles;

public:
    Vol() : prixBase(0.0), placesDisponibles(0) {}
    Vol(string num, string dep, string arr, string date, double prix, int places)
        : numeroVol(num), villeDepart(dep), villeArrivee(arr), dateHeure(date),
          prixBase(prix), placesDisponibles(places) {}

    string getNumeroVol() const { return numeroVol; }
    double getPrixBase() const { return prixBase; }
    int getPlacesDisponibles() const { return placesDisponibles; }

    bool reserverPlace() {
        if (placesDisponibles > 0) {
            placesDisponibles--;
            return true;
        }
        return false;
    }

    void libererPlace() {
        placesDisponibles++;
    }

    void afficher() const {
        cout << "Vol " << numeroVol << " | " << villeDepart << " -> " << villeArrivee
             << " | Date: " << dateHeure << " | Prix: " << prixBase << " FCFA"
             << " | Places dispo: " << placesDisponibles << endl;
    }
};

// 3. Classe Paiement
class Paiement {
private:
    string idPaiement;
    double montant;
    string modePaiement;
    bool estPaye;

public:
    Paiement() : montant(0.0), estPaye(false) {}
    Paiement(string id, double m, string mode)
        : idPaiement(id), montant(m), modePaiement(mode), estPaye(true) {}

    bool getEstPaye() const { return estPaye; }
    void annulerPaiement() { estPaye = false; }

    void afficher() const {
        cout << "Paiement [" << idPaiement << "] - Montant: " << montant
             << " FCFA - Mode: " << modePaiement
             << " - Statut: " << (estPaye ? "Paye" : "Rembourse/Annule") << endl;
    }
};

// 4. Classe Reservation
class Reservation {
private:
    string idReservation;
    Passager* passager;
    Vol* vol;
    string statut; // "Confirmee", "Annulee"
    Paiement paiement;

public:
    Reservation(string id, Passager* p, Vol* v, Paiement pay)
        : idReservation(id), passager(p), vol(v), statut("Confirmee"), paiement(pay) {}

    string getIdReservation() const { return idReservation; }
    string getStatut() const { return statut; }
    Vol* getVol() const { return vol; }

    // Réparation / Modification de billet (changement de vol)
    void reparerBillet(Vol* nouveauVol) {
        if (statut == "Annulee") {
            cout << "Impossible de reparer un billet deja annule." << endl;
            return;
        }
        if (nouveauVol != nullptr && nouveauVol->reserverPlace()) {
            if (vol != nullptr) {
                vol->libererPlace();
            }
            vol = nouveauVol;
            cout << "Billet " << idReservation << " repare / modifie avec succes pour le vol "
                 << vol->getNumeroVol() << "." << endl;
        } else {
            cout << "Echec de la reparation : aucune place disponible sur le nouveau vol." << endl;
        }
    }

    void annulerReservation() {
        if (statut == "Confirmee") {
            statut = "Annulee";
            if (vol != nullptr) {
                vol->libererPlace();
            }
            paiement.annulerPaiement();
            cout << "Reservation " << idReservation << " annulee et paiement rembourse." << endl;
        } else {
            cout << "Cette reservation est deja annulee." << endl;
        }
    }

    void afficher() const {
        cout << "Reservation ID: " << idReservation << " | Statut: " << statut << endl;
        if (passager) passager->afficher();
        if (vol) vol->afficher();
        paiement.afficher();
        cout << "-----------------------------------------" << endl;
    }
};

// Fonction principale console
int main() {
    vector<Passager> passagers;
    vector<Vol> vols;
    vector<Reservation> reservations;

    // Données initiales de démonstration (Cotonou)
    vols.push_back(Vol("AF802", "Cotonou (COO)", "Paris (CDG)", "2026-12-20 23:30", 450000, 50));
    vols.push_back(Vol("KP104", "Cotonou (COO)", "Abidjan (ABJ)", "2026-12-15 08:00", 120000, 30));
    vols.push_back(Vol("ET918", "Cotonou (COO)", "Addis-Abeba (ADD)", "2026-12-18 14:15", 380000, 25));

    passagers.push_back(Passager("P01", "KOTCHOFA", "Koffi", "B1234567", "+229 0197000001"));
    passagers.push_back(Passager("P02", "DOSSOU", "Afi", "B7654321", "+229 0196000002"));

    int choix = 0;
    do {
        cout << "\n=== AGENCE DE VOYAGE - COTONOU ===" << endl;
        cout << "1. Ajouter un passager" << endl;
        cout << "2. Lister les passagers" << endl;
        cout << "3. Ajouter un vol" << endl;
        cout << "4. Lister les vols" << endl;
        cout << "5. Creer une reservation (et paiement)" << endl;
        cout << "6. Lister les reservations" << endl;
        cout << "7. Reparer / Modifier un billet" << endl;
        cout << "8. Annuler une reservation" << endl;
        cout << "0. Quitter" << endl;
        cout << "Votre choix : ";

        if (!(cin >> choix)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entree invalide. Veuillez saisir un nombre." << endl;
            continue;
        }

        if (choix == 1) {
            string id, nom, prenom, passeport, tel;
            cout << "ID Passager : "; cin >> id;
            cout << "Nom : "; cin >> nom;
            cout << "Prenom : "; cin >> prenom;
            cout << "Numero Passeport : "; cin >> passeport;
            cout << "Telephone : "; cin >> tel;
            passagers.push_back(Passager(id, nom, prenom, passeport, tel));
            cout << "Passager ajoute avec succes !" << endl;

        } else if (choix == 2) {
            cout << "\n--- LISTE DES PASSAGERS ---" << endl;
            for (const auto& p : passagers) {
                p.afficher();
            }

        } else if (choix == 3) {
            string num, dep, arr, date;
            double prix;
            int places;
            cout << "Numero de Vol : "; cin >> num;
            cin.ignore();
            cout << "Ville de depart : "; getline(cin, dep);
            cout << "Ville d'arrivee : "; getline(cin, arr);
            cout << "Date et heure (YYYY-MM-DD HH:MM) : "; getline(cin, date);
            cout << "Prix du billet (FCFA) : "; cin >> prix;
            cout << "Nombre de places : "; cin >> places;
            vols.push_back(Vol(num, dep, arr, date, prix, places));
            cout << "Vol ajoute avec succes !" << endl;

        } else if (choix == 4) {
            cout << "\n--- LISTE DES VOLS ---" << endl;
            for (const auto& v : vols) {
                v.afficher();
            }

        } else if (choix == 5) {
            string idRes, idPass, numVol, mode;
            cout << "ID Reservation (ex: RES01) : "; cin >> idRes;
            cout << "ID Passager : "; cin >> idPass;
            cout << "Numero de Vol : "; cin >> numVol;
            cout << "Mode de paiement (Cash/MoMo/Carte) : "; cin >> mode;

            Passager* pFound = nullptr;
            Vol* vFound = nullptr;

            for (auto& p : passagers) {
                if (p.getId() == idPass) {
                    pFound = &p;
                    break;
                }
            }
            for (auto& v : vols) {
                if (v.getNumeroVol() == numVol) {
                    vFound = &v;
                    break;
                }
            }

            if (pFound && vFound && vFound->reserverPlace()) {
                Paiement pay("PAY-" + idRes, vFound->getPrixBase(), mode);
                reservations.push_back(Reservation(idRes, pFound, vFound, pay));
                cout << "Reservation creee et payee avec succes !" << endl;
            } else {
                cout << "Erreur : Passager introuvable, vol introuvable ou plus de places disponibles !" << endl;
            }

        } else if (choix == 6) {
            cout << "\n--- LISTE DES RESERVATIONS ---" << endl;
            if (reservations.empty()) {
                cout << "Aucune reservation enregistree." << endl;
            }
            for (const auto& r : reservations) {
                r.afficher();
            }

        } else if (choix == 7) {
            string idRes, nouveauVolNum;
            cout << "ID de la reservation a reparer/modifier : "; cin >> idRes;
            cout << "Nouveau numero de vol : "; cin >> nouveauVolNum;

            Reservation* rFound = nullptr;
            Vol* vFound = nullptr;
            for (auto& r : reservations) {
                if (r.getIdReservation() == idRes) {
                    rFound = &r;
                    break;
                }
            }
            for (auto& v : vols) {
                if (v.getNumeroVol() == nouveauVolNum) {
                    vFound = &v;
                    break;
                }
            }

            if (rFound && vFound) {
                rFound->reparerBillet(vFound);
            } else {
                cout << "Reservation ou nouveau vol introuvable." << endl;
            }

        } else if (choix == 8) {
            string idRes;
            cout << "ID de la reservation a annuler : "; cin >> idRes;
            bool trouve = false;
            for (auto& r : reservations) {
                if (r.getIdReservation() == idRes) {
                    r.annulerReservation();
                    trouve = true;
                    break;
                }
            }
            if (!trouve) {
                cout << "Reservation non trouvee." << endl;
            }
        }

    } while (choix != 0);

    cout << "Fermeture de l'application." << endl;
    return 0;
}

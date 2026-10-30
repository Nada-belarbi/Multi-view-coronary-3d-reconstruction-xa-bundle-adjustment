#ifndef ANNOTATIONS_H
#define ANNOTATIONS_H

#include <string>
#include <vector>

// Représente un point 2D annoté sur une image angiographique.
struct Annotation
{
    // Identifiant de la vue : ML1, ML2, ...
    std::string cameraId;

    // Identifiant du landmark : P1, P2, P3...
    std::string pointId;

    // Coordonnées du point dans l'image
    // unité : pixels
    double u = 0.0;
    double v = 0.0;

    // Numéro de la frame sur laquelle le point a été annoté.
    // Utile pour travailler avec les données synchronisées.
    int frameNumber = -1;

    // Identifiant temporel éventuel : T11, T12...
    std::string timeId;
};


// Classe simple contenant un ensemble d'annotations
class Annotations
{
private:

    std::vector<Annotation> annotations;

public:

    // Ajouter une annotation
    void ajouter(const Annotation& annotation);

    // Retourner toutes les annotations
    const std::vector<Annotation>& getToutes() const;

    // Retourner toutes les observations d'un même landmark
    std::vector<Annotation>
    getParPoint(const std::string& pointId) const;

    // Retourner toutes les annotations d'une vue donnée
    std::vector<Annotation>
    getParCamera(const std::string& cameraId) const;

    // Afficher les annotations dans la console
    void afficher() const;
};

#endif
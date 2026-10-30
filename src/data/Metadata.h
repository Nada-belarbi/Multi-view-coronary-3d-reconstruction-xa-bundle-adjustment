#ifndef METADATA_H
#define METADATA_H

#include <string>

// Structure contenant les métadonnées importantes
// d'une acquisition angiographique XA.
//
// Ces informations proviennent du fichier param.json
// associé à chaque vue MI_1, MI_2, ..., MI_5.
struct Metadata
{
    // Nom / identifiant de la vue : MI_1, MI_2, ...
    std::string code;

    // Dimensions de l'image en pixels
    int rows = 0;
    int columns = 0;

    // Taille physique d'un pixel sur le détecteur
    // unité : mm / pixel
    double pixelSpacingX = 0.0;
    double pixelSpacingY = 0.0;

    // Distance entre la source de rayons X et le détecteur
    // unité : mm
    double distanceSourceToDetector = 0.0;

    // Distance entre la source de rayons X et le patient / objet
    // unité : mm
    double distanceSourceToPatient = 0.0;

    // Angle primaire du C-arm
    // lié à la rotation LAO / RAO
    // unité : degrés
    double primaryAngle = 0.0;

    // Angle secondaire du C-arm
    // lié à l'inclinaison CRA / CAU
    // unité : degrés
    double secondaryAngle = 0.0;

    // Nombre d'images par seconde
    double cineRate = 0.0;

    // Temps entre deux frames
    // unité : millisecondes
    double frameTime = 0.0;

    // Nombre total de frames dans la séquence
    int numberOfFrames = 0;

    // Facteur de grossissement géométrique fourni
    // par les métadonnées
    double magnificationFactor = 0.0;

    // Informations générales sur l'appareil
    std::string manufacturer;
    std::string model;
    std::string protocolName;

    // Affiche les principales métadonnées dans la console
    void afficher() const;
};

#endif
#ifndef LOADER_H
#define LOADER_H

#include "Metadata.h"
#include "Annotations.h"

#include <string>
#include <vector>

#include <opencv2/opencv.hpp>

class Loader
{
public:

    // Lit un fichier param.json et retourne les métadonnées
    Metadata chargerMetadata(
        const std::string& cheminJson
    ) const;

    // Charge toutes les images présentes dans un dossier
    //
    // Les images sont triées par nom de fichier afin de
    // conserver l'ordre temporel des frames.
    std::vector<cv::Mat> chargerFrames(
        const std::string& cheminDossier
    ) const;

    // Charge les annotations depuis un fichier CSV.
    //
    // Format attendu :
    // peut changer(j'ai pas encore tester ...)
    // cameraId,pointId,frameNumber,timeId,u,v
    //
    // Exemple :
    // ML1,P1,24,T11,210.5,172.3
    //
    Annotations chargerAnnotationsCSV(
        const std::string& cheminCSV
    ) const;
};

#endif
#include "Metadata.h"

#include <iostream>

void Metadata::afficher() const
{
    std::cout << "\n===== METADONNEES DE LA VUE =====\n";

    std::cout << "Code : " << code << "\n";

    std::cout << "Taille image : "
              << columns << " x "
              << rows << " pixels\n";

    std::cout << "Pixel spacing X : "
              << pixelSpacingX
              << " mm/pixel\n";

    std::cout << "Pixel spacing Y : "
              << pixelSpacingY
              << " mm/pixel\n";

    std::cout << "Distance source-detecteur : "
              << distanceSourceToDetector
              << " mm\n";

    std::cout << "Distance source-patient : "
              << distanceSourceToPatient
              << " mm\n";

    std::cout << "Angle primaire : "
              << primaryAngle
              << " degres\n";

    std::cout << "Angle secondaire : "
              << secondaryAngle
              << " degres\n";

    std::cout << "Cine rate : "
              << cineRate
              << " images/s\n";

    std::cout << "Frame time : "
              << frameTime
              << " ms\n";

    std::cout << "Nombre de frames : "
              << numberOfFrames
              << "\n";

    std::cout << "Facteur de grossissement : "
              << magnificationFactor
              << "\n";

    std::cout << "Fabricant : "
              << manufacturer
              << "\n";

    std::cout << "Modele : "
              << model
              << "\n";

    std::cout << "Protocole : "
              << protocolName
              << "\n";

    std::cout << "=================================\n";
}
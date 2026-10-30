#include "Loader.h"

#include <nlohmann/json.hpp>

#include <fstream>
#include <iostream>
#include <filesystem>
#include <algorithm>
#include <sstream>
#include <limits>
#include <stdexcept>
#include <type_traits>

namespace fs = std::filesystem;

using json = nlohmann::json;

namespace
{
template <typename T>
T lireNombre(const json& objet, const char* cle, T valeurParDefaut)
{
    const auto valeur = objet.find(cle);
    if (valeur == objet.end() || valeur->is_null())
        return valeurParDefaut;

    try
    {
        if (valeur->is_number())
            return valeur->get<T>();

        if (valeur->is_string())
        {
            const std::string texte = valeur->get<std::string>();
            std::size_t position = 0;

            if constexpr (std::is_integral_v<T>)
            {
                const long long nombre = std::stoll(texte, &position);
                if (texte.find_first_not_of(" \t\r\n", position)
                    != std::string::npos
                    || nombre < std::numeric_limits<T>::lowest()
                    || nombre > std::numeric_limits<T>::max())
                {
                    throw std::invalid_argument("valeur entière invalide");
                }
                return static_cast<T>(nombre);
            }
            else
            {
                const double nombre = std::stod(texte, &position);
                if (texte.find_first_not_of(" \t\r\n", position)
                    != std::string::npos)
                {
                    throw std::invalid_argument("valeur numérique invalide");
                }
                return static_cast<T>(nombre);
            }
        }

        std::cerr << "Métadonnée numérique invalide pour la clé \""
                  << cle << "\"\n";
    }
    catch (const std::exception& e)
    {
        std::cerr << "Métadonnée numérique invalide pour la clé \""
                  << cle << "\" : " << e.what() << "\n";
    }

    return valeurParDefaut;
}
}

// ------------------------------------------------------------
// Lecture des métadonnées JSON
// ------------------------------------------------------------

Metadata Loader::chargerMetadata(
    const std::string& cheminJson
) const
{
    Metadata metadata;

    std::ifstream fichier(cheminJson);

    if (!fichier.is_open())
    {
        std::cerr
            << "Erreur : impossible d'ouvrir le fichier JSON : "
            << cheminJson
            << "\n";

        return metadata;
    }

    json j;

    try
    {
        fichier >> j;
    }
    catch (const json::parse_error& e)
    {
        std::cerr
            << "Erreur de lecture JSON : "
            << e.what()
            << "\n";

        return metadata;
    }


    metadata.code =
        j.value("code", "");

    metadata.rows =
        lireNombre(j, "Rows", 0);

    metadata.columns =
        lireNombre(j, "Columns", 0);

    metadata.pixelSpacingX =
        lireNombre(j, "ImagerPixelSpacingX", 0.0);

    metadata.pixelSpacingY =
        lireNombre(j, "ImagerPixelSpacingY", 0.0);

    metadata.distanceSourceToDetector =
        lireNombre(j, "DistanceSourceToDetector", 0.0);

    metadata.distanceSourceToPatient =
        lireNombre(j, "DistanceSourceToPatient", 0.0);

    metadata.primaryAngle =
        lireNombre(j, "PositionerPrimaryAngle", 0.0);

    metadata.secondaryAngle =
        lireNombre(j, "PositionerSecondaryAngle", 0.0);

    metadata.cineRate =
        lireNombre(j, "CineRate", 0.0);

    metadata.frameTime =
        lireNombre(j, "FrameTime", 0.0);

    metadata.numberOfFrames =
        lireNombre(j, "NumberOfFrames", 0);

    metadata.magnificationFactor =
        lireNombre(j, "MagnificationFactor", 0.0);

    metadata.manufacturer =
        j.value("Manufacturer", "");

    metadata.model =
        j.value("ManufacturerModelName", "");

    metadata.protocolName =
        j.value("ProtocolName", "");


    return metadata;
}


// ------------------------------------------------------------
// Chargement des frames
// ------------------------------------------------------------

std::vector<cv::Mat>
Loader::chargerFrames(
    const std::string& cheminDossier
) const
{
    std::vector<cv::Mat> frames;

    std::vector<fs::path> fichiers;


    if (!fs::exists(cheminDossier))
    {
        std::cerr
            << "Erreur : dossier introuvable : "
            << cheminDossier
            << "\n";

        return frames;
    }


    // --------------------------------------------------------
    // Récupération des fichiers image
    // --------------------------------------------------------

    for (const auto& entree :
         fs::directory_iterator(cheminDossier))
    {
        if (!entree.is_regular_file())
            continue;

        std::string extension =
            entree.path().extension().string();

        if (
            extension == ".png" ||
            extension == ".jpg" ||
            extension == ".jpeg" ||
            extension == ".bmp"
        )
        {
            fichiers.push_back(entree.path());
        }
    }


    // --------------------------------------------------------
    // Tri par nom de fichier
    //
    // Important pour conserver l'ordre :
    //
    // img_0001
    // img_0002
    // img_0003
    // ...
    // --------------------------------------------------------

    std::sort(
        fichiers.begin(),
        fichiers.end()
    );


    // --------------------------------------------------------
    // Chargement des images avec OpenCV
    // --------------------------------------------------------

    for (const fs::path& chemin : fichiers)
    {
        cv::Mat image =
            cv::imread(
                chemin.string(),
                cv::IMREAD_GRAYSCALE
            );


        if (image.empty())
        {
            std::cerr
                << "Attention : impossible de lire "
                << chemin
                << "\n";

            continue;
        }


        frames.push_back(image);
    }


    std::cout
        << frames.size()
        << " frames chargees depuis "
        << cheminDossier
        << "\n";


    return frames;
}


// ------------------------------------------------------------
// Lecture des annotations CSV
// ------------------------------------------------------------

Annotations Loader::chargerAnnotationsCSV(
    const std::string& cheminCSV
) const
{
    Annotations resultat;

    std::ifstream fichier(cheminCSV);

    if (!fichier.is_open())
    {
        std::cerr
            << "Erreur : impossible d'ouvrir "
            << cheminCSV
            << "\n";

        return resultat;
    }


    std::string ligne;


    // Ignorer la première ligne contenant les noms de colonnes
    std::getline(fichier, ligne);


    while (std::getline(fichier, ligne))
    {
        if (ligne.empty())
            continue;


        std::stringstream ss(ligne);

        Annotation annotation;

        std::string frameString;
        std::string uString;
        std::string vString;


        // Format :
        //
        // cameraId,pointId,frameNumber,timeId,u,v


        std::getline(
            ss,
            annotation.cameraId,
            ','
        );

        std::getline(
            ss,
            annotation.pointId,
            ','
        );

        std::getline(
            ss,
            frameString,
            ','
        );

        std::getline(
            ss,
            annotation.timeId,
            ','
        );

        std::getline(
            ss,
            uString,
            ','
        );

        std::getline(
            ss,
            vString,
            ','
        );


        try
        {
            annotation.frameNumber =
                std::stoi(frameString);

            annotation.u =
                std::stod(uString);

            annotation.v =
                std::stod(vString);
        }
        catch (...)
        {
            std::cerr
                << "Annotation invalide : "
                << ligne
                << "\n";

            continue;
        }


        resultat.ajouter(annotation);
    }


    return resultat;
}
// ============================================================
// Fonctions utilitaires pour lire les nombres dans le JSON.
//
// Certaines métadonnées peuvent être stockées comme nombres :
//     "Rows": 512
//
// ou comme chaînes de caractères :
//     "Rows": "512"
//
// Ces fonctions gèrent les deux cas.
// ============================================================

double lireDouble(
    const nlohmann::json& j,
    const std::string& cle,
    double valeurParDefaut = 0.0
)
{
    // La clé n'existe pas
    if (!j.contains(cle) || j[cle].is_null())
    {
        return valeurParDefaut;
    }

    const auto& valeur = j[cle];

    // Cas 1 : le JSON contient directement un nombre
    if (valeur.is_number())
    {
        return valeur.get<double>();
    }

    // Cas 2 : le JSON contient un nombre sous forme de texte
    if (valeur.is_string())
    {
        try
        {
            return std::stod(valeur.get<std::string>());
        }
        catch (...)
        {
            std::cerr
                << "Attention : impossible de convertir "
                << cle
                << " = "
                << valeur
                << " en double.\n";

            return valeurParDefaut;
        }
    }

    std::cerr
        << "Attention : type inattendu pour "
        << cle
        << "\n";

    return valeurParDefaut;
}


int lireInt(
    const nlohmann::json& j,
    const std::string& cle,
    int valeurParDefaut = 0
)
{
    if (!j.contains(cle) || j[cle].is_null())
    {
        return valeurParDefaut;
    }

    const auto& valeur = j[cle];

    if (valeur.is_number_integer())
    {
        return valeur.get<int>();
    }

    // Certains entiers peuvent être enregistrés comme 512.0
    if (valeur.is_number())
    {
        return static_cast<int>(valeur.get<double>());
    }

    if (valeur.is_string())
    {
        try
        {
            return std::stoi(valeur.get<std::string>());
        }
        catch (...)
        {
            std::cerr
                << "Attention : impossible de convertir "
                << cle
                << " = "
                << valeur
                << " en int.\n";

            return valeurParDefaut;
        }
    }

    return valeurParDefaut;
}
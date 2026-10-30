#include "Camera.h"
#include "Transforms.h"

#include <iostream>
#include <stdexcept>


// ============================================================
// CONSTRUCTEUR
// ============================================================

Camera::Camera(
    const Metadata& metadata,
    const Eigen::Vector3d& isocentre
)
    :
    metadata(metadata),
    isocentre(isocentre),
    cx(0.0),
    cy(0.0)
{
    mettreAJour();
}


// ============================================================
// PARAMETRES INTRINSEQUES
// ============================================================

void Camera::calculerIntrinseques()
{
    // Vérification pour éviter les divisions par zéro.

    if (metadata.pixelSpacingX <= 0.0 ||
        metadata.pixelSpacingY <= 0.0)
    {
        throw std::runtime_error(
            "Pixel spacing invalide."
        );
    }


    if (metadata.distanceSourceToDetector <= 0.0)
    {
        throw std::runtime_error(
            "Distance source-detecteur invalide."
        );
    }


    // --------------------------------------------------------
    // Distance focale en pixels.
    //
    // DSD = Distance Source -> Detecteur
    //
    // fx = DSD / taillePixelX
    // fy = DSD / taillePixelY
    // --------------------------------------------------------

    double fx =
        metadata.distanceSourceToDetector
        /
        metadata.pixelSpacingX;


    double fy =
        metadata.distanceSourceToDetector
        /
        metadata.pixelSpacingY;


    // --------------------------------------------------------
    // Première approximation :
    //
    // le centre principal est situé au centre du détecteur.
    //
    // Plus tard, cx et cy pourront être optimisés dans le BA.
    // --------------------------------------------------------

    cx =
        static_cast<double>(metadata.columns) / 2.0;

    cy =
        static_cast<double>(metadata.rows) / 2.0;


    // Matrice intrinsèque

    K <<
        fx,  0.0, cx,
        0.0, fy,  cy,
        0.0, 0.0, 1.0;
}


// ============================================================
// ROTATION
// ============================================================

void Camera::calculerRotation()
{
    // --------------------------------------------------------
    // D'après le prof :
    //
    // R_imageVersMonde
    //
    // est la matrice de passage :
    //
    // IMAGE -> MONDE
    // --------------------------------------------------------

    R_imageVersMonde =
        Transforms::construireRotationImageVersMonde(
            metadata.primaryAngle,
            metadata.secondaryAngle
        );


    // --------------------------------------------------------
    // Pour projeter un point monde vers l'image,
    // on a besoin de l'inverse.
    //
    // Pour une rotation :
    //
    // R^-1 = R^T
    // --------------------------------------------------------

    R_mondeVersImage =
        R_imageVersMonde.transpose();
}


// ============================================================
// TRANSLATION
// ============================================================

void Camera::calculerTranslation()
{
    if (metadata.distanceSourceToPatient <= 0.0)
    {
        throw std::runtime_error(
            "Distance source-patient invalide."
        );
    }


    // --------------------------------------------------------
    // On suppose pour cette première modélisation que :
    //
    // DistanceSourceToPatient
    //
    // représente approximativement la distance :
    //
    // Source -> Isocentre
    //
    // On note cette distance SOD.
    // --------------------------------------------------------

    const double SOD =
        metadata.distanceSourceToPatient;


    // --------------------------------------------------------
    // Dans le repère image/caméra :
    //
    // la source est à l'origine.
    //
    // L'isocentre se trouve le long de l'axe optique +Z :
    //
    // I_camera = (0, 0, SOD)
    //
    // Donc, relativement à l'isocentre,
    // la source est :
    //
    // Source_relative = (0, 0, -SOD)
    // --------------------------------------------------------

    Eigen::Vector3d sourceRelativeIsocentre(
        0.0,
        0.0,
        -SOD
    );


    // --------------------------------------------------------
    // R_imageVersMonde transforme un vecteur du repère image
    // vers le repère monde.
    //
    // On obtient donc la position de la source dans le monde :
    //
    // C = I + R_imageVersMonde * (0,0,-SOD)
    // --------------------------------------------------------

    centreSource =
        isocentre
        +
        R_imageVersMonde
        *
        sourceRelativeIsocentre;


    // --------------------------------------------------------
    // Transformation monde -> caméra :
    //
    // Pc = R_mondeVersImage * (Pw - C)
    //
    // Développement :
    //
    // Pc =
    // R_mondeVersImage * Pw
    // -
    // R_mondeVersImage * C
    //
    // Donc :
    //
    // t = -R_mondeVersImage * C
    // --------------------------------------------------------

    t =
        -R_mondeVersImage
        *
        centreSource;
}


// ============================================================
// RECALCUL COMPLET
// ============================================================

void Camera::mettreAJour()
{
    calculerIntrinseques();

    calculerRotation();

    calculerTranslation();
}


// ============================================================
// MATRICE DE PROJECTION
// ============================================================

Eigen::Matrix<double, 3, 4>
Camera::getProjectionMatrix() const
{
    // --------------------------------------------------------
    // Matrice extrinsèque :
    //
    // [ R | t ]
    //
    // dimensions : 3 x 4
    // --------------------------------------------------------

    Eigen::Matrix<double, 3, 4> extrinseque;


    extrinseque.block<3, 3>(0, 0) =
        R_mondeVersImage;


    extrinseque.col(3) =
        t;


    // --------------------------------------------------------
    // Matrice de projection :
    //
    // M = K [R | t]
    // --------------------------------------------------------

    return K * extrinseque;
}


// ============================================================
// GETTERS
// ============================================================

const Eigen::Matrix3d&
Camera::getK() const
{
    return K;
}


const Eigen::Matrix3d&
Camera::getRImageVersMonde() const
{
    return R_imageVersMonde;
}


const Eigen::Matrix3d&
Camera::getRMondeVersImage() const
{
    return R_mondeVersImage;
}


const Eigen::Vector3d&
Camera::getT() const
{
    return t;
}


const Eigen::Vector3d&
Camera::getIsocentre() const
{
    return isocentre;
}


const Eigen::Vector3d&
Camera::getCentreSource() const
{
    return centreSource;
}


const Metadata&
Camera::getMetadata() const
{
    return metadata;
}


// ============================================================
// AFFICHAGE
// ============================================================

void Camera::afficher() const
{
    std::cout
        << "\n========================================\n";

    std::cout
        << "        MODELISATION DE LA CAMERA\n";

    std::cout
        << "========================================\n";


    std::cout
        << "\nAngle primaire RAO/LAO : "
        << metadata.primaryAngle
        << " deg\n";


    std::cout
        << "Angle secondaire CRAN/CAUD : "
        << metadata.secondaryAngle
        << " deg\n";


    std::cout
        << "\nMatrice intrinsèque K :\n"
        << K
        << "\n";


    std::cout
        << "\nR image -> monde :\n"
        << R_imageVersMonde
        << "\n";


    std::cout
        << "\nR monde -> image = R^T :\n"
        << R_mondeVersImage
        << "\n";


    std::cout
        << "\nIsocentre monde :\n"
        << isocentre.transpose()
        << "\n";


    std::cout
        << "\nCentre de la source X monde :\n"
        << centreSource.transpose()
        << "\n";


    std::cout
        << "\nTranslation t :\n"
        << t.transpose()
        << "\n";


    std::cout
        << "\nMatrice de projection M = K[R|t] :\n"
        << getProjectionMatrix()
        << "\n";


    std::cout
        << "========================================\n";
}
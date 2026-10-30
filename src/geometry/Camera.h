#ifndef CAMERA_H
#define CAMERA_H

#include <Eigen/Dense>

#include "../data/Metadata.h"


class Camera
{
private:

    // ========================================================
    // Métadonnées provenant du param.json
    // ========================================================

    Metadata metadata;


    // ========================================================
    // Paramètres intrinsèques
    // ========================================================

    // Matrice intrinsèque :
    //
    // [ fx   0  cx ]
    // [  0  fy  cy ]
    // [  0   0   1 ]
    //
    Eigen::Matrix3d K;


    // ========================================================
    // Rotations
    // ========================================================

    // Matrice donnée par la convention du professeur.
    //
    // Repère image -> repère monde
    Eigen::Matrix3d R_imageVersMonde;


    // Inverse de la précédente.
    //
    // Comme R est une matrice de rotation :
    //
    // R^-1 = R^T
    //
    // Repère monde -> repère image
    Eigen::Matrix3d R_mondeVersImage;


    // ========================================================
    // Translation
    // ========================================================

    // Translation utilisée dans :
    //
    // Pc = R * Pw + t
    //
    Eigen::Vector3d t;


    // ========================================================
    // Géométrie physique
    // ========================================================

    // Isocentre dans le repère monde.
    //
    // Pour commencer :
    // I = (0,0,0)
    //
    Eigen::Vector3d isocentre;


    // Position de la source de rayons X
    // dans le repère monde.
    Eigen::Vector3d centreSource;


    // ========================================================
    // Centre principal
    // ========================================================

    double cx;
    double cy;


public:

    // Constructeur
    Camera(
        const Metadata& metadata,
        const Eigen::Vector3d& isocentre =
            Eigen::Vector3d::Zero()
    );


    // ========================================================
    // Construction géométrique
    // ========================================================

    void calculerIntrinseques();

    void calculerRotation();

    void calculerTranslation();

    void mettreAJour();


    // ========================================================
    // Matrice finale de projection
    //
    // M = K [R | t]
    // ========================================================

    Eigen::Matrix<double, 3, 4>
    getProjectionMatrix() const;


    // ========================================================
    // Getters
    // ========================================================

    const Eigen::Matrix3d&
    getK() const;


    const Eigen::Matrix3d&
    getRImageVersMonde() const;


    const Eigen::Matrix3d&
    getRMondeVersImage() const;


    const Eigen::Vector3d&
    getT() const;


    const Eigen::Vector3d&
    getIsocentre() const;


    const Eigen::Vector3d&
    getCentreSource() const;


    const Metadata&
    getMetadata() const;


    // Affichage console
    void afficher() const;
};

#endif
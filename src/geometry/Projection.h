#ifndef PROJECTION_H
#define PROJECTION_H

#include <Eigen/Dense>

#include "Camera.h"


namespace Projection
{
    // --------------------------------------------------------
    // Projection d'un point 3D monde vers un point image.
    //
    // Entrée :
    //
    // P = (X,Y,Z)
    //
    // Sortie :
    //
    // p = (u,v)
    // --------------------------------------------------------

    Eigen::Vector2d projeterPoint(
        const Eigen::Vector3d& point3D,
        const Camera& camera
    );


    // Variante utilisant directement une matrice M.
    Eigen::Vector2d projeterPoint(
        const Eigen::Vector3d& point3D,
        const Eigen::Matrix<double, 3, 4>& M
    );
}

#endif
#include "Projection.h"

#include <cmath>
#include <stdexcept>


namespace Projection
{

Eigen::Vector2d projeterPoint(
    const Eigen::Vector3d& point3D,
    const Camera& camera
)
{
    return projeterPoint(
        point3D,
        camera.getProjectionMatrix()
    );
}


Eigen::Vector2d projeterPoint(
    const Eigen::Vector3d& point3D,
    const Eigen::Matrix<double, 3, 4>& M
)
{
    // --------------------------------------------------------
    // Coordonnées homogènes du point 3D :
    //
    // (X,Y,Z)
    //
    // devient :
    //
    // (X,Y,Z,1)
    // --------------------------------------------------------

    Eigen::Vector4d P;

    P <<
        point3D.x(),
        point3D.y(),
        point3D.z(),
        1.0;


    // --------------------------------------------------------
    // Projection homogène :
    //
    // p_h = M P
    //
    // p_h = (u', v', w')
    // --------------------------------------------------------

    Eigen::Vector3d pHomogene =
        M * P;


    // Éviter division par zéro

    if (std::abs(pHomogene.z()) < 1e-12)
    {
        throw std::runtime_error(
            "Projection impossible : profondeur nulle."
        );
    }


    // --------------------------------------------------------
    // Passage des coordonnées homogènes aux pixels :
    //
    // u = u' / w'
    //
    // v = v' / w'
    // --------------------------------------------------------

    double u =
        pHomogene.x()
        /
        pHomogene.z();


    double v =
        pHomogene.y()
        /
        pHomogene.z();


    return Eigen::Vector2d(u, v);
}

}
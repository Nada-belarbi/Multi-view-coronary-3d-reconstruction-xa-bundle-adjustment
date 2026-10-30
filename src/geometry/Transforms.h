#ifndef TRANSFORMS_H
#define TRANSFORMS_H

#include <Eigen/Dense>

namespace Transforms
{
    // Conversion degrés -> radians
    double degToRad(double angleDeg);

    // --------------------------------------------------------
    // Construit la matrice de rotation donnée par le prof.
    //
    // angleRAOLAO   : angle primaire du JSON
    // angleCranCaud : angle secondaire du JSON
    //
    // Retour :
    // matrice de passage REPERE IMAGE -> REPERE MONDE
    // --------------------------------------------------------
    Eigen::Matrix3d construireRotationImageVersMonde(
        double angleRAOLAO,
        double angleCranCaud
    );
}

#endif
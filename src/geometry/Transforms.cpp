#include "Transforms.h"

#include <Eigen/Geometry>

namespace Transforms
{

double degToRad(double angleDeg)
{
    constexpr double PI = 3.14159265358979323846;

    return angleDeg * PI / 180.0;
}


Eigen::Matrix3d construireRotationImageVersMonde(
    double angleRAOLAO,
    double angleCranCaud
)
{
    // --------------------------------------------------------
    // Convention EXACTE fournie par le professeur :
    //
    // q1 :
    // rotation de -RAO/LAO autour de l'axe Y
    //
    // q2 :
    // rotation de -CRAN/CAUD autour de l'axe X
    //
    // R = (q2 * q1).matrix()
    //
    // R permet de passer :
    //
    // REPERE IMAGE -> REPERE MONDE
    // --------------------------------------------------------

    const double angle1 =
        -degToRad(angleRAOLAO);

    const double angle2 =
        -degToRad(angleCranCaud);


    Eigen::Quaterniond q1(
        Eigen::AngleAxisd(
            angle1,
            Eigen::Vector3d::UnitY()
        )
    );


    Eigen::Quaterniond q2(
        Eigen::AngleAxisd(
            angle2,
            Eigen::Vector3d::UnitX()
        )
    );


    Eigen::Matrix3d R =
        (q2 * q1).matrix();


    return R;
}

}
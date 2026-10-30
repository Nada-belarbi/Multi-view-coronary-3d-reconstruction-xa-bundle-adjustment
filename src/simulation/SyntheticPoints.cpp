#include "SyntheticPoints.h"

#include <fstream>
#include <iostream>
#include <stdexcept>


void SyntheticPoints::genererBifurcation()
{
    // Nettoyer les éventuels anciens points.
    points.clear();


    // ========================================================
    // BRANCHE PRINCIPALE
    // ========================================================

    points.push_back({
        "P0",
        Eigen::Vector3d(-40.0, 0.0, 0.0),
        "main"
    });

    points.push_back({
        "P1",
        Eigen::Vector3d(-30.0, 2.0, 1.0),
        "main"
    });

    points.push_back({
        "P2",
        Eigen::Vector3d(-20.0, 4.0, 2.0),
        "main"
    });

    points.push_back({
        "P3",
        Eigen::Vector3d(-10.0, 3.0, 4.0),
        "main"
    });


    // ========================================================
    // POINT DE BIFURCATION
    // ========================================================

    points.push_back({
        "B",
        Eigen::Vector3d(0.0, 0.0, 5.0),
        "bifurcation"
    });


    // ========================================================
    // BRANCHE 1
    // ========================================================

    points.push_back({
        "L1",
        Eigen::Vector3d(10.0, 8.0, 8.0),
        "left"
    });

    points.push_back({
        "L2",
        Eigen::Vector3d(20.0, 15.0, 12.0),
        "left"
    });

    points.push_back({
        "L3",
        Eigen::Vector3d(30.0, 20.0, 15.0),
        "left"
    });


    // ========================================================
    // BRANCHE 2
    // ========================================================

    points.push_back({
        "R1",
        Eigen::Vector3d(8.0, -8.0, 7.0),
        "right"
    });

    points.push_back({
        "R2",
        Eigen::Vector3d(18.0, -15.0, 10.0),
        "right"
    });

    points.push_back({
        "R3",
        Eigen::Vector3d(28.0, -20.0, 14.0),
        "right"
    });
}


const std::vector<SyntheticPoint>&
SyntheticPoints::getPoints() const
{
    return points;
}


void SyntheticPoints::afficher() const
{
    std::cout
        << "\n========================================\n"
        << "       POINTS SYNTHETIQUES 3D\n"
        << "========================================\n";


    for (const auto& point : points)
    {
        std::cout
            << point.id
            << " | "
            << point.branch
            << " | "
            << point.position.transpose()
            << "\n";
    }


    std::cout
        << "========================================\n";
}


void SyntheticPoints::exporterCSV(
    const std::string& chemin
) const
{
    std::ofstream fichier(chemin);

    if (!fichier.is_open())
    {
        throw std::runtime_error(
            "Impossible d'ouvrir le fichier CSV : "
            + chemin
        );
    }


    // Entête
    fichier
        << "id,x,y,z,branch\n";


    for (const auto& point : points)
    {
        fichier
            << point.id
            << ","
            << point.position.x()
            << ","
            << point.position.y()
            << ","
            << point.position.z()
            << ","
            << point.branch
            << "\n";
    }


    fichier.close();


    std::cout
        << "\nCSV genere : "
        << chemin
        << "\n";
}
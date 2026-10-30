#ifndef SYNTHETIC_POINTS_H
#define SYNTHETIC_POINTS_H

#include <Eigen/Dense>
#include <string>
#include <vector>


// Un point synthétique appartient à une branche.
struct SyntheticPoint
{
    std::string id;

    Eigen::Vector3d position;

    std::string branch;
};


class SyntheticPoints
{
private:

    std::vector<SyntheticPoint> points;


public:

    // Génère une bifurcation 3D simple.
    void genererBifurcation();


    // Retourne tous les points.
    const std::vector<SyntheticPoint>&
    getPoints() const;


    // Affiche les points dans le terminal.
    void afficher() const;


    // Exporte les points dans un CSV.
    void exporterCSV(
        const std::string& chemin
    ) const;
};

#endif
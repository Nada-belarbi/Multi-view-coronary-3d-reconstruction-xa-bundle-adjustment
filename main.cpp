#include <iostream>

#include "simulation/SyntheticPoints.h"


int main()
{
    std::cout
        << "\n=== TEST SYNTHETIC POINTS ===\n";


    SyntheticPoints simulation;


    // Générer la bifurcation.
    simulation.genererBifurcation();


    // Afficher les points.
    simulation.afficher();


    // Export CSV.
    simulation.exporterCSV(
        "../results/synthetic_points.csv"
    );


    return 0;
}
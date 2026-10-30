#include "Annotations.h"

#include <iostream>

void Annotations::ajouter(const Annotation& annotation)
{
    annotations.push_back(annotation);
}


const std::vector<Annotation>&
Annotations::getToutes() const
{
    return annotations;
}


std::vector<Annotation>
Annotations::getParPoint(const std::string& pointId) const
{
    std::vector<Annotation> resultat;

    for (const Annotation& annotation : annotations)
    {
        if (annotation.pointId == pointId)
        {
            resultat.push_back(annotation);
        }
    }

    return resultat;
}


std::vector<Annotation>
Annotations::getParCamera(const std::string& cameraId) const
{
    std::vector<Annotation> resultat;

    for (const Annotation& annotation : annotations)
    {
        if (annotation.cameraId == cameraId)
        {
            resultat.push_back(annotation);
        }
    }

    return resultat;
}


void Annotations::afficher() const
{
    std::cout << "\n===== ANNOTATIONS =====\n";

    for (const Annotation& annotation : annotations)
    {
        std::cout
            << "Camera : " << annotation.cameraId
            << " | Point : " << annotation.pointId
            << " | Frame : " << annotation.frameNumber
            << " | T : " << annotation.timeId
            << " | (u,v) = ("
            << annotation.u << ", "
            << annotation.v << ")"
            << "\n";
    }

    std::cout << "=======================\n";
}
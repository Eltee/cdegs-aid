/******************************************************************************
* Projet:     CDEGS-Aid
*  /Project
*
* Nom/Name:    building.h
*
* Description: CDEGS-Aid est un logiciel d'aide pour la génération de fichiers
*              de simulation compatibles avec SESCad et CDEGS-HiFreq pour des
*              simulations de champ électrics, d'affichage et d'analyse de
*              résultat de simulations CDEGS-HiFreq.
*
* Auteur:      Renaud Bigras, Hydro-Québec Transénergie
*  /Author
*
* Créé:        12-05-2014
*  /Created
*
* Copyright:   (c) Renaud Bigras 2014
*
*   This file is part of CDEGS-Aid.
*
*   CDEGS-Aid is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   CDEGS-Aid is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with CDEGS-Aid. If not, see <http://www.gnu.org/licenses/>.
*******************************************************************************/

#ifndef BUILDING_H
#define BUILDING_H

#include <string>
#include <math.h>
#include "component.h"
#include "conductor.h"
#include "leadtype.h"
#include "conductortype.h"
#include "coating.h"
#include "energization.h"
#include "cabletype.h"
#include "util/apputils.h"

class Conductor;
class Energization;
class Component;

/*!
 \brief Classe composante qui représente un bâtiment.

 Cette classe représente, dans le modèle, un bâtiment ajouté à la configuration.

 Celui-ci sera ensuite converti en les conducteurs apropriés pour la simulation.

 \class Building building.h "classes/building.h"
*/
class Building : public Component
{
    public:
        Building();
        Building(int const faces, double const height, double const distance, double const step, const double width);
        Building(Building const* build);
        ~Building();
        bool operator==(Building const* build);
        bool operator!=(Building const* build);
        bool validateBuilding();
        std::vector<std::shared_ptr<Conductor>> generateConductors();
    //Getters start---------------------------------------------------
        int getFaces() const;
        int getHeight() const;
        int getDistance() const;
        int getLength() const;
        double getStep() const;
        int getWidth() const;
        double getRadius() const;
        std::shared_ptr<LeadType> getLeadType() const;
        std::shared_ptr<ConductorType> getConductorType() const;
        std::shared_ptr<Coating> getCoating() const;
        std::shared_ptr<Energization> getEnergization() const;
        std::shared_ptr<CableType> getCableType() const;
    //Getters end-----------------------------------------------------
    //Setters start---------------------------------------------------
        Building& setFaces(int const faces);
        Building& setHeight(int const height);
        Building& setDistance(int const distance);
        Building& setLength(int const length);
        Building& setStep(double const step);
        Building& setWidth(int const width);
        Building& setRadius(double const radius);
        Building& setLeadType(std::shared_ptr<LeadType> leadType);
        Building& setConductorType(std::shared_ptr<ConductorType> conductorType);
        Building& setCoating(std::shared_ptr<Coating> coating);
        Building& setEnergization(std::shared_ptr<Energization> energization);
        Building& setCableType(std::shared_ptr<CableType> cableType);
    //Setters end-----------------------------------------------------
    private:
        int m_faces, m_height, m_distance, m_length, m_width;
        double m_step, m_radius;
        std::shared_ptr<LeadType> m_leadType;
        std::shared_ptr<ConductorType> m_conductorType;
        std::shared_ptr<Coating> m_coating;
        std::shared_ptr<Energization> m_energization;
        std::shared_ptr<CableType> m_cableType;
};

#endif // BUILDING_H

/******************************************************************************
* Projet:     CDEGS-Aid
*  /Project
*
* Nom/Name:    conductor.h
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

#ifndef CONDUCTOR_H
#define CONDUCTOR_H

#include <string>
#include <stdio.h>
#include "structs.h"
#include "leadtype.h"
#include "conductortype.h"
#include "coating.h"
#include "energization.h"
#include "cabletype.h"
#include "component.h"
#include "configuration.h"
#include "util/apputils.h"

class LeadType;
class ConductorType;
class Coating;
class Energization;
class CableType;
class Component;
class Configuration;

/*!
 \brief Classe composante qui représente un conducteur.

 Cette classe représente un objet conducteur. Possiblement l'objet le plus important de la simulation.

 \class Conductor conductor.h "classes/conductor.h"
*/
class Conductor : public Component
{
    public:
        Conductor();
        Conductor(Configuration const& config, int const& leadType, int const& conductorType, int const& coating, int const& energization, int const& cableType, const double& radius=0.0);
        Conductor(std::shared_ptr<LeadType> leadType, std::shared_ptr<ConductorType> conductorType, std::shared_ptr<Coating> coating, std::shared_ptr<Energization> energization, std::shared_ptr<CableType> cableType, const double& radius=0.0);
        Conductor(Conductor const* cond);
        bool operator==(Conductor const* cond);
        bool operator!=(Conductor const* cond);
        ~Conductor();
    //Getters start--------------------------------------------------------
        std::shared_ptr<LeadType> getLeadType() const;
        std::shared_ptr<ConductorType> getConductorType() const;
        std::shared_ptr<Coating> getCoating() const;
        std::shared_ptr<Energization> getEnergization() const;
        std::shared_ptr<CableType> getCableType() const;
        coords const& getStartCoords() const;
        coords const& getEndCoords() const;
        double const& getRadius() const;
        int const& getSubDivision() const;
    //Getters end----------------------------------------------------------
    //Setters start--------------------------------------------------------
        Conductor& setLeadType(std::shared_ptr<LeadType> leadType);
        Conductor& setConductorType(std::shared_ptr<ConductorType> conductorType);
        Conductor& setCoating(std::shared_ptr<Coating> coating);
        Conductor& setEnergization(std::shared_ptr<Energization> energization);
        Conductor& setStartCoords(coords const& start);
        Conductor& setEndCoords(coords const& end);
        Conductor& setCoords(coords const& start, coords const& end);
        Conductor& setRadius(double const& radius);
        Conductor& setSubDivision(int const& subD);
        Conductor& setCableType(std::shared_ptr<CableType> cableType);
    //Setters end----------------------------------------------------------
    private:
        std::shared_ptr<LeadType> m_leadType;
        std::shared_ptr<ConductorType> m_conductorType;
        std::shared_ptr<Coating> m_coating;
        std::shared_ptr<Energization> m_energization;
        coords m_startCoords, m_endCoords;
        double m_radius;
        int m_subDivision = 1;
        std::shared_ptr<CableType> m_cableType;
};

#endif // CONDUCTOR_H

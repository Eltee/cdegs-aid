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

struct coords{
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
};

struct subDivision{
    std::string method = "default";
    int number = 0;
};

class Conductor : public Component
{
    public:
        Conductor();
        Conductor(Configuration const& config, std::string const& leadType, std::string const& conductorType, std::string const& coating, std::string const& energization, std::string const& cableType, const double& radius=0.0);
        Conductor(LeadType* leadType, ConductorType* conductorType, Coating* coating, Energization* energization, CableType* cableType, const double& radius=0.0);
        ~Conductor();
    //Getters start--------------------------------------------------------
        LeadType* getLeadType() const;
        ConductorType* getConductorType() const;
        Coating* getCoating() const;
        Energization* getEnergization() const;
        CableType* getCableType() const;
        coords const& getStartCoords() const;
        coords const& getEndCoords() const;
        double const& getRadius() const;
        subDivision const& getSubDivision() const;
    //Getters end----------------------------------------------------------
    //Setters start--------------------------------------------------------
        Conductor& setLeadType(LeadType* leadType);
        Conductor& setConductorType(ConductorType* conductorType);
        Conductor& setCoating(Coating* coating);
        Conductor& setEnergization(Energization* energization);
        Conductor& setStartCoords(coords const& start);
        Conductor& setEndCoords(coords const& end);
        Conductor& setCoords(coords const& start, coords const& end);
        Conductor& setRadius(double const& radius);
        Conductor& setSubDivision(subDivision const& subD);
        Conductor& setCableType(CableType* cableType);
    //Setters end----------------------------------------------------------
    private:
        LeadType* m_leadType = NULL;
        ConductorType* m_conductorType = NULL;
        Coating* m_coating = NULL;
        Energization* m_energization = NULL;
        coords m_startCoords, m_endCoords;
        double m_radius;
        subDivision m_subDivision;
        CableType* m_cableType = NULL;
};

#endif // CONDUCTOR_H

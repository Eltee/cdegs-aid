/******************************************************************************
* Projet:     CDEGS-Aid
*  /Project
*
* Nom/Name:    configuration.h
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

#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <string>
#include <vector>
#include "energization.h"
#include "conductortype.h"
#include "conductor.h"
#include "building.h"
#include "leadtype.h"
#include "coating.h"

class Configuration
{
    public:
        Configuration();
        ~Configuration();
    private:
        std::string m_id;
        std::string m_identifier;
        std::string m_units;
        std::string m_frequency;
        std::vector <LeadType*> m_leadTypes;
        std::vector <Coating*> m_coatings;
        std::vector<Energization*> m_energizations;
        std::vector<double> m_tolerances;
        std::vector<ConductorType*> m_conductorTypes;
        std::vector<Conductor*> m_conductors;
        std::vector<Conductor*> m_buildingConductors;
        std::vector<Building*> m_buildings;
        struct computations{
            bool GPR;
            bool POTENTIAL_SCALAR;
            bool ELECTRIC;
            bool MAGNETIC;
            bool VECTOR_POTENTIAL;
            bool GRADIENT_SCALAR;
        } m_computations;
        struct profile{
            struct coords{
                double start;
                double end;
                double step;
            } xCoords, yCoords;
            double NLine;
            double MCol;
        };
        std::vector<profile> m_profiles;
};

#endif // CONFIGURATION_H

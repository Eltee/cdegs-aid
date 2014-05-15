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
#include "leadtype.h"
#include "conductortype.h"
#include "coating.h"
#include "energization.h"
#include "cabletype.h"

class Conductor
{
    public:
        Conductor();
        ~Conductor();
    private:
        std::string m_id;
        LeadType* m_leadType;
        ConductorType* m_conductorType;
        Coating* m_coating;
        Energization* m_energization;
        struct coords{
            double x;
            double y;
            double z;
        } m_startCoords, m_endCoords;
        double m_radius;
        struct subDivision{
            std::string method;
            int number;
        } m_subDivision;
        CableType* m_cableType;
};

#endif // CONDUCTOR_H

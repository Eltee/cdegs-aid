/******************************************************************************
* Projet:     CDEGS-Aid
*  /Project
*
* Nom/Name:    conductortype.h
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

#ifndef CONDUCTORTYPE_H
#define CONDUCTORTYPE_H

#include <string>
#include "util/apputils.h"

class ConductorType
{
    public:
        ConductorType();
        ConductorType(std::string const& type, std::string const& name, int const& number, double const& resistivity, double const& permeability);
        ~ConductorType();
    //Getters start------------------------------------------------
        std::string const& getId() const;
        std::string const& getType() const;
        std::string const& getName() const;
        int const& getNumber() const;
        double const& getResistivity() const;
        double const& getPermeability() const;
    //Getters end--------------------------------------------------
    //Setters start------------------------------------------------
        ConductorType& setType(std::string const& type);
        ConductorType& setName(std::string const& name);
        ConductorType& setNumber(int const& number);
        ConductorType& setResistivity(double const& resistivity);
        ConductorType& setPermeability(double const& permeability);
    //Setters end--------------------------------------------------
    private:
        std::string m_id, m_type, m_name;
        int m_number;
        double m_resistivity, m_permeability;
};

#endif // CONDUCTORTYPE_H

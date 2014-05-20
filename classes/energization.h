/******************************************************************************
* Projet:     CDEGS-Aid
*  /Project
*
* Nom/Name:    energization.h
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

#ifndef ENERGIZATION_H
#define ENERGIZATION_H

#include <string>
#include "util/apputils.h"

class Energization
{
    public:
        Energization();
        Energization(std::string const& identification, std::string const& type, int const& angle, double const& magnitude);
        ~Energization();
    //Getters start----------------------------------------------------
        std::string const& getId() const;
        std::string const& getIdentification() const;
        std::string const& getType() const;
        int const& getAngle() const;
        double const& getMagnitude() const;
    //Getters end------------------------------------------------------
    //Setters start----------------------------------------------------
        Energization& setIdentification(std::string const& identification);
        Energization& setType(std::string const& type);
        Energization& setAngle(int const& angle);
        Energization& setMagnitude(double const& magnitude);
    //Setters end------------------------------------------------------
    private:
        std::string m_id, m_identification, m_type;
        int m_angle;
        double m_magnitude;
};

#endif // ENERGIZATION_H

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
#include "component.h"
#include "util/apputils.h"

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
        Building(int const& faces, double const& height, double const& distanceMin, double const& distanceMax, double const& step);
        ~Building();
    //Getters start---------------------------------------------------
        int const& getFaces() const;
        double const& getHeight() const;
        double const& getDistanceMin() const;
        double const& getDistanceMax() const;
        double const& getStep() const;
    //Getters end-----------------------------------------------------
    //Setters start---------------------------------------------------
        Building& setFaces(int const& faces);
        Building& setHeight(double const& height);
        Building& setDistanceMin(double const& distanceMin);
        Building& setDistanceMax(double const& distanceMax);
        Building& setStep(double const& step);
    //Setters end-----------------------------------------------------
    private:
        int m_faces;
        double m_height, m_distanceMin, m_distanceMax, m_step;
};

#endif // BUILDING_H

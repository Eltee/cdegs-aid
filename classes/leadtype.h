/******************************************************************************
* Projet:     CDEGS-Aid
*  /Project
*
* Nom/Name:    leadtype.h
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

#ifndef LEADTYPE_H
#define LEADTYPE_H

#include <string>
#include "component.h"

class Component;

/*!
 \brief Classe composante qui représente un type de connection câble

 Cette classe représente le LeadType dans le modèle de la configuration.

 Par défaut, il y a deux LeadTypes: Unconnected et Default Impedence.

 On peut ajouter des LeadTypes personalisés qui seront sauvegardés dans la configuration.

 \class LeadType leadtype.h "classes/leadtype.h"
*/
class LeadType : public Component
{
    public:
        LeadType();
        LeadType(std::string const& name);
        LeadType(LeadType const* lType);
        ~LeadType();
        bool operator==(LeadType const* lType);
        bool operator!=(LeadType const* lType);
};

#endif // LEADTYPE_H

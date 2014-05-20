/******************************************************************************
* Projet:     CDEGS-Aid
*  /Project
*
* Nom/Name:    leadtype.cpp
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

#include "leadtype.h"

LeadType::LeadType(){
    m_id = AppUtils::getInstance().uniqueIdGenerator("LeadTypeId");
    m_name = "default";
    m_number = 1;
}

LeadType::LeadType(std::string const& name, int const& number){
    m_id = AppUtils::getInstance().uniqueIdGenerator("LeadTypeId");
    m_name = name;
    m_number = number;
}

LeadType::~LeadType(){}

std::string const& LeadType::getId() const{
    return m_id;
}

std::string const& LeadType::getName() const{
    return m_name;
}

int const& LeadType::getNumber() const{
    return m_number;
}

LeadType& LeadType::setName(std::string const& name){
    m_name = name;
    return *this;
}

LeadType& LeadType::setNumber(int const& number){
    m_number = number;
    return *this;
}

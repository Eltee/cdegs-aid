/******************************************************************************
* Projet:     CDEGS-Aid
*  /Project
*
* Nom/Name:    conductortype.cpp
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

#include "conductortype.h"

ConductorType::ConductorType(){
    m_id = AppUtils::getInstance().uniqueIdGenerator("ConductorTypeId");
    m_type = "default";
    m_name = "default";
    m_number = 1;
    m_resistivity = 1.64;
    m_permeability = 1.0;
}

ConductorType::ConductorType(std::string const& type, std::string const& name, int const& number, double const& resistivity, double const& permeability){
    m_id = AppUtils::getInstance().uniqueIdGenerator("ConductorTypeId");
    m_type = type;
    m_name = name;
    m_number = number;
    m_resistivity = resistivity;
    m_permeability = permeability;
}

ConductorType::~ConductorType(){}

std::string const& ConductorType::getId() const{
    return m_id;
}

std::string const& ConductorType::getType() const{
    return m_type;
}

std::string const& ConductorType::getName() const{
    return m_name;
}

int const& ConductorType::getNumber() const{
    return m_number;
}

double const& ConductorType::getResistivity() const{
    return m_resistivity;
}

double const& ConductorType::getPermeability() const{
    return m_permeability;
}

ConductorType& ConductorType::setType(std::string const& type){
    m_type = type;
    return *this;
}

ConductorType& ConductorType::setName(std::string const& name){
    m_name = name;
    return *this;
}

ConductorType& ConductorType::setNumber(int const& number){
    m_number = number;
    return *this;
}

ConductorType& ConductorType::setResistivity(double const& resistivity){
    m_resistivity = resistivity;
    return *this;
}

ConductorType& ConductorType::setPermeability(double const& permeability){
    m_permeability = permeability;
    return *this;
}


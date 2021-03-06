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

/*!
 \brief

 \fn ConductorType::ConductorType
*/
ConductorType::ConductorType() : Component("", false, true){
    m_type = "default";
    m_resistivity = 1.64;
    m_permeability = 1.0;
}

/*!
 \brief

 \fn ConductorType::ConductorType
 \param type
 \param name
 \param resistivity
 \param permeability
*/
ConductorType::ConductorType(const std::string type, const std::string name, const double resistivity, const double permeability) : Component(name, false, true){
    m_type = type;
    m_resistivity = resistivity;
    m_permeability = permeability;
}

ConductorType::ConductorType(ConductorType const* cType){
    m_id = cType->getId();
    m_name = cType->getName();
    m_saveable = cType->isSaveable();
    m_locked = cType->isLocked();
    m_type = cType->getType();
    m_resistivity = cType->getResistivity();
    m_permeability = cType->getPermeability();
}

/*!
 \brief

 \fn ConductorType::~ConductorType
*/
ConductorType::~ConductorType(){}

bool ConductorType::operator==(ConductorType const* cType){
    bool result = true;
    if(m_id != cType->getId()) result = false;
    if(m_name != cType->getName()) result = false;
    if(m_saveable != cType->isSaveable()) result = false;
    if(m_locked != cType->isLocked()) result = false;
    if(m_type != cType->getType()) result = false;
    if(m_resistivity != cType->getResistivity()) result = false;
    if(m_permeability != cType->getPermeability()) result = false;
    return result;
}

bool ConductorType::operator!=(ConductorType const* cType){
    bool result = true;
    if(*this == cType) result = false;
    return result;
}

/*!
 \brief

 \fn ConductorType::getType
 \return const std::string
*/
std::string ConductorType::getType() const{
    return m_type;
}

/*!
 \brief

 \fn ConductorType::getResistivity
 \return const double
*/
double ConductorType::getResistivity() const{
    return m_resistivity;
}

/*!
 \brief

 \fn ConductorType::getPermeability
 \return const double
*/
double ConductorType::getPermeability() const{
    return m_permeability;
}

/*!
 \brief

 \fn ConductorType::setType
 \param type
 \return ConductorType
*/
ConductorType& ConductorType::setType(std::string const type){
    m_type = type;
    return *this;
}

/*!
 \brief

 \fn ConductorType::setResistivity
 \param resistivity
 \return ConductorType
*/
ConductorType& ConductorType::setResistivity(double const resistivity){
    m_resistivity = resistivity;
    return *this;
}

/*!
 \brief

 \fn ConductorType::setPermeability
 \param permeability
 \return ConductorType
*/
ConductorType& ConductorType::setPermeability(double const permeability){
    m_permeability = permeability;
    return *this;
}


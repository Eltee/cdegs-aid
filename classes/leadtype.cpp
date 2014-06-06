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

/*!
 \brief

 \fn LeadType::LeadType
*/
LeadType::LeadType() : Component(0, "", false, true){}

/*!
 \brief

 \fn LeadType::LeadType
 \param name
*/
LeadType::LeadType(std::string const& name) : Component(0, name, false, true){}

LeadType::LeadType(LeadType const* lType){
    m_id = lType->getId();
    m_name = lType->getName();
    m_saveable = lType->isSaveable();
    m_locked = lType->isLocked();
}

/*!
 \brief

 \fn LeadType::~LeadType
*/
LeadType::~LeadType(){}


bool LeadType::operator==(LeadType const* lType){
    bool result = true;
    if(m_id != lType->getId()) result = false;
    if(m_name != lType->getName()) result = false;
    if(m_saveable != lType->isSaveable()) result = false;
    if(m_locked != lType->isLocked()) result = false;
    return result;
}

bool LeadType::operator!=(LeadType const* lType){
    bool result = true;
    if(*this == lType) result = false;
    return result;
}

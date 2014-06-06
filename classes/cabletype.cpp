/******************************************************************************
* Projet:     CDEGS-Aid
*  /Project
*
* Nom/Name:    cabletype.cpp
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

#include "cabletype.h"

/*!
 \brief

 \fn CableType::CableType
*/
CableType::CableType() : Component(0, "", false, false){}

/*!
 \brief

 \fn CableType::CableType
 \param name
*/
CableType::CableType(std::string const& name) : Component(0, name, false, true){}

CableType::CableType(CableType const* cblType){
    m_id = cblType->getId();
    m_name = cblType->getName();
    m_saveable = cblType->isSaveable();
    m_locked = cblType->isLocked();
}

/*!
 \brief

 \fn CableType::~CableType
*/
CableType::~CableType(){}

bool CableType::operator==(CableType const* cblType){
    bool result = true;
    if(m_id != cblType->getId()) result = false;
    if(m_name != cblType->getName()) result = false;
    if(m_saveable != cblType->isSaveable()) result = false;
    if(m_locked != cblType->isLocked()) result = false;
    return result;
}

bool CableType::operator!=(CableType const* cblType){
    bool result = true;
    if(*this == cblType) result = false;
    return result;
}

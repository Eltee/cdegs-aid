/******************************************************************************
* Projet:     CDEGS-Aid
*  /Project
*
* Nom/Name:    coating.cpp
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

#include "coating.h"

/*!
 \brief

 \fn Coating::Coating
*/
Coating::Coating() : Component(-2, "", false, true){}

/*!
 \brief

 \fn Coating::Coating
 \param name
*/
Coating::Coating(std::string const& name) : Component(-2, name, false, true){}

Coating::Coating(Coating const* coat){
    m_id = coat->getId();
    m_name = coat->getName();
    m_saveable = coat->isSaveable();
    m_locked = coat->isLocked();
}

/*!
 \brief

 \fn Coating::~Coating
*/
Coating::~Coating(){}

bool Coating::operator==(Coating const* coat){
    bool result = true;
    if(m_id != coat->getId()) result = false;
    if(m_name != coat->getName()) result = false;
    if(m_saveable != coat->isSaveable()) result = false;
    if(m_locked != coat->isLocked()) result = false;
    return result;
}

bool Coating::operator!=(Coating const* coat){
    bool result = true;
    if(*this == coat) result = false;
    return result;
}

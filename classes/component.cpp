/******************************************************************************
* Projet:     CDEGS-Aid
*  /Project
*
* Nom/Name:    component.cpp
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

#include "component.h"

Component::Component(){
    m_id = "";
    m_name = "default";
    m_locked = false;
    m_saveable = false;
}

Component::Component(std::string id, std::string name, bool locked, bool saveable){
    m_id = id;
    m_name = name;
    m_locked = locked;
    m_saveable = saveable;
}

Component::~Component(){}

std::string const& Component::getId() const{
    return m_id;
}

std::string const& Component::getName() const{
    return m_name;
}

bool const& Component::isLocked() const{
    return m_locked;
}

bool const& Component::isSaveable() const{
    return m_saveable;
}

Component& Component::setId(std::string const& id){
    m_id = id;
    return *this;
}

Component& Component::setName(std::string const& name){
    m_name = name;
    return *this;
}

Component& Component::setLocked(bool const& locked){
    m_locked = locked;
    return *this;
}

Component& Component::setSaveable(bool const& saveable){
    m_saveable = saveable;
    return *this;
}


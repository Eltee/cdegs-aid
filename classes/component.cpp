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

/*!
 \brief Constructeur par défaut.

 \fn Component::Component
*/
Component::Component(){
    m_name = "default";
    m_locked = false;
    m_saveable = false;
}

/*!
 \brief Constructeur qui prend des paramètres.

 \fn Component::Component(int const& id, std::string const& name, bool const& locked, bool const& saveable)
 \param id L'identificateur
 \param name Le nom
 \param locked Barré(?)
 \param saveable Sauvegardable(?)
*/
Component::Component(std::string const& name, bool const& locked, bool const& saveable){
    m_name = name;
    m_locked = locked;
    m_saveable = saveable;
}

/*!
 \brief Destructeur par défaut.

 \fn Component::~Component
*/
Component::~Component(){}

bool const& Component::compare(Component const* c) const{
    if(m_id == c->getId()) return true;
    else return false;
}

double const& Component::getId() const{
    return m_id;
}

/*!
 \brief Fonction qui retourne le nom.

 \fn Component::getName
 \return Le nom
*/
std::string const& Component::getName() const{
    return m_name;
}

/*!
 \brief Fonction qui retourne un booléen indiquant si le composant est barré.

 \fn Component::isLocked
 \return Barré: vrai/faux
*/
bool const& Component::isLocked() const{
    return m_locked;
}

/*!
 \brief Fonction qui retourne un booléen indiquant si le composant est sauvegardable.

 \fn Component::isSaveable
 \return Sauvegardable: vrai/faux
*/
bool const& Component::isSaveable() const{
    return m_saveable;
}

/*!
 \brief Fonction permettant de changer le nom.

 \fn Component::setName
 \param name Le nouveau nom
 \return L'objet lui-même (chaîne d'appels)
*/
Component& Component::setName(std::string const& name){
    m_name = name;
    return *this;
}

/*!
 \brief Fonction permettant de barrer/débarrer le composant.

 \fn Component::setLocked
 \param locked Le nouveau booléen barré(?)
 \return L'objet lui-même (chaîne d'appels)
*/
Component& Component::setLocked(bool const& locked){
    m_locked = locked;
    return *this;
}

/*!
 \brief Fonction permettant de barrer/débarrer le composant.

 \fn Component::setSaveable
 \param saveable Le nouveau booléen sauvegardable(?)
 \return L'objet lui-même (chaîne d'appels)
*/
Component& Component::setSaveable(bool const& saveable){
    m_saveable = saveable;
    return *this;
}

Component& Component::setId(double const& id){
    m_id = id;
    return *this;
}


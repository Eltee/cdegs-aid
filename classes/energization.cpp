/******************************************************************************
* Projet:     CDEGS-Aid
*  /Project
*
* Nom/Name:    energization.cpp
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

#include "energization.h"

/*!
 \brief

 \fn Energization::Energization
*/
Energization::Energization() : Component("", false, true){
    m_identification = "default";
    m_type = "Computed";
    m_frequency = "AC";
    m_angle = 0;
    m_magnitude = 0;
}

/*!
 \brief

 \fn Energization::Energization
 \param identification
 \param type
 \param frequency
 \param magnitude
 \param angle
*/
Energization::Energization(const std::string identification, const std::string type, const std::string frequency, const double magnitude, const int angle) : Component("", false, true){
    m_identification = identification;
    m_type = type;
    m_frequency = frequency;
    m_angle = angle;
    m_magnitude = magnitude;
}

Energization::Energization(Energization const* ener){
    m_id = ener->getId();
    m_name = ener->getName();
    m_locked = ener->isLocked();
    m_saveable = ener->isSaveable();

    m_identification = ener->getIdentification();
    m_type = ener->getType();
    m_frequency = ener->getFrequency();
    m_angle = ener->getAngle();
    m_magnitude = ener->getMagnitude();
}

/*!
 \brief

 \fn Energization::~Energization
*/
Energization::~Energization(){}

bool Energization::operator==(Energization const* ener){
    bool result = true;
    if(m_id != ener->getId()) result = false;
    if(m_name != ener->getName()) result = false;
    if(m_locked != ener->isLocked()) result = false;
    if(m_saveable != ener->isSaveable()) result = false;
    if(m_identification != ener->getIdentification()) result = false;
    if(m_type != ener->getType()) result = false;
    if(m_frequency != ener->getFrequency()) result = false;
    if(m_angle != ener->getAngle()) result = false;
    if(m_magnitude != ener->getMagnitude()) result = false;
    return result;
}

bool Energization::operator!=(Energization const* ener){
    bool result = true;
    if(*this == ener) result = false;
    return result;
}

/*!
 \brief

 \fn Energization::getIdentification
 \return const std::string
*/
std::string Energization::getIdentification() const{
    return m_identification;
}

/*!
 \brief

 \fn Energization::getType
 \return const std::string
*/
std::string Energization::getType() const{
    return m_type;
}

/*!
 \brief

 \fn Energization::getFrequency
 \return const std::string
*/
std::string Energization::getFrequency() const{
    return m_frequency;
}

/*!
 \brief

 \fn Energization::getAngle
 \return const double
*/
double Energization::getAngle() const{
    return m_angle;
}

/*!
 \brief

 \fn Energization::getRealPart
 \return const int
*/
double Energization::getRealPart() const{
    if(m_angle != 0){
        double result = (m_magnitude * std::cos(m_angle * PI / 180));
        return result;
    }
    else{
        return m_magnitude;
    }
}

/*!
 \brief

 \fn Energization::getImaginaryPart
 \return const int
*/
double Energization::getImaginaryPart() const{
    if(m_angle != 0){
        double result = (m_magnitude * std::sin(m_angle * PI / 180));
        return result;
    }
    else{
        return 0;
    }
}

/*!
 \brief

 \fn Energization::getMagnitude
 \return const int
*/
int Energization::getMagnitude() const{
    return m_magnitude;
}

/*!
 \brief

 \fn Energization::setIdentification
 \param identification
 \return Energization
*/
Energization& Energization::setIdentification(std::string const identification){
    m_identification = identification;
    return *this;
}

/*!
 \brief

 \fn Energization::setType
 \param type
 \return Energization
*/
Energization& Energization::setType(std::string const type){
    m_type = type;
    return *this;
}

/*!
 \brief

 \fn Energization::setFrequency
 \param frequency
 \return Energization
*/
Energization& Energization::setFrequency(std::string const frequency){
    m_frequency = frequency;
    return *this;
}

/*!
 \brief

 \fn Energization::setAngle
 \param angle
 \return Energization
*/
Energization& Energization::setAngle(double const angle){
    m_angle = angle;
    return *this;
}

/*!
 \brief

 \fn Energization::setMagnitude
 \param magnitude
 \return Energization
*/
Energization& Energization::setMagnitude(const int magnitude){
    m_magnitude = magnitude;
    return *this;
}

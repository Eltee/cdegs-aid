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

Energization::Energization() : Component(AppUtils::getInstance().uniqueIdGenerator("EnergizationId"), "", false, true){
    m_identification = "default";
    m_type = "default";
    m_frequency = "AC";
    m_angle = 0;
    m_magnitude = 0;
}

Energization::Energization(std::string const& identification, std::string const& type, std::string const& frequency, double const& magnitude, int const& angle) : Component(AppUtils::getInstance().uniqueIdGenerator("EnergizationId"), "", false, true){
    m_identification = identification;
    m_type = type;
    m_frequency = frequency;
    m_angle = angle;
    m_magnitude = magnitude;
}

Energization::~Energization(){}

std::string const& Energization::getIdentification() const{
    return m_identification;
}

std::string const& Energization::getType() const{
    return m_type;
}

std::string const& Energization::getFrequency() const{
    return m_frequency;
}

const double& Energization::getAngle() const{
    return m_angle;
}

double const& Energization::getMagnitude() const{
    return m_magnitude;
}

Energization& Energization::setIdentification(std::string const& identification){
    m_identification = identification;
    return *this;
}

Energization& Energization::setType(std::string const& type){
    m_type = type;
    return *this;
}

Energization& Energization::setFrequency(std::string const& frequency){
    m_frequency = frequency;
    return *this;
}

Energization& Energization::setAngle(double const& angle){
    m_angle = angle;
    return *this;
}

Energization& Energization::setMagnitude(double const& magnitude){
    m_magnitude = magnitude;
    return *this;
}

/******************************************************************************
* Projet:     CDEGS-Aid
*  /Project
*
* Nom/Name:    conductor.cpp
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

#include "conductor.h"

Conductor::Conductor() : Component(AppUtils::getInstance().uniqueIdGenerator("ConductorId"), "", false, true){
    m_radius = 0.0;
}

Conductor::Conductor(Configuration const& config, std::string const& leadType, std::string const& conductorType, std::string const& coating, std::string const& energization, std::string const& cableType, double const& radius) : Component(AppUtils::getInstance().uniqueIdGenerator("ConductorId"), "", false, true){
    m_radius = radius;

    if(leadType != "") m_leadType = config.getLeadTypes().at(leadType);
    if(conductorType != "") m_conductorType = config.getConductorTypes().at(conductorType);
    if(coating != "") m_coating = config.getCoatings().at(coating);
    if(energization != "") m_energization = config.getEnergizations().at(energization);
    if(cableType != "") m_cableType = config.getCableTypes().at(cableType);
}

Conductor::Conductor(LeadType* leadType, ConductorType* conductorType, Coating* coating, Energization* energization, CableType* cableType, double const& radius) : Component(AppUtils::getInstance().uniqueIdGenerator("ConductorId"), "", false, true){
    m_radius = radius;

    m_leadType = leadType;
    m_conductorType = conductorType;
    m_coating = coating;
    m_energization = energization;
    m_cableType = cableType;
}

Conductor::~Conductor(){}

LeadType const* Conductor::getLeadType() const{
    return m_leadType;
}

ConductorType const* Conductor::getConductorType() const{
    return m_conductorType;
}

Coating const* Conductor::getCoating() const{
    return m_coating;
}

Energization const* Conductor::getEnergization() const{
    return m_energization;
}

CableType const* Conductor::getCableType() const{
    return m_cableType;
}

coords const& Conductor::getStartCoords() const{
    return m_startCoords;
}

coords const& Conductor::getEndCoords() const{
    return m_endCoords;
}

double const& Conductor::getRadius() const{
    return m_radius;
}

subDivision const& Conductor::getSubDivision() const{
    return m_subDivision;
}

Conductor& Conductor::setLeadType(LeadType* leadType){
    m_leadType = leadType;
    return *this;
}

Conductor& Conductor::setConductorType(ConductorType* conductorType){
    m_conductorType = conductorType;
    return *this;
}

Conductor& Conductor::setCoating(Coating* coating){
    m_coating = coating;
    return *this;
}

Conductor& Conductor::setEnergization(Energization* energization){
    m_energization = energization;
    return *this;
}

Conductor& Conductor::setStartCoords(coords const& start){
    m_startCoords = start;
    return *this;
}

Conductor& Conductor::setEndCoords(coords const& end){
    m_endCoords = end;
    return *this;
}

Conductor& Conductor::setCoords(coords const& start, coords const& end){
    m_startCoords = start;
    m_endCoords = end;
    return *this;
}

Conductor& Conductor::setRadius(double const& radius){
    m_radius = radius;
    return *this;
}

Conductor& Conductor::setSubDivision(subDivision const& subD){
    m_subDivision = subD;
    return *this;
}

Conductor& Conductor::setCableType(CableType* cableType){
    m_cableType = cableType;
    return *this;
}


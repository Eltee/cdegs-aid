/******************************************************************************
* Projet:     CDEGS-Aid
*  /Project
*
* Nom/Name:    configuration.cpp
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

#include "configuration.h"

Configuration::Configuration(){
    m_id = AppUtils::getInstance().uniqueIdGenerator("ConfigurationId");
    m_identifier = "default";
    m_units = "Metric";
    m_frequency = "AC";

}

Configuration::Configuration(std::string const& identifier, std::string const& units, std::string const& frequency){
    m_id = AppUtils::getInstance().uniqueIdGenerator("ConfigurationId");
    m_identifier = identifier;
    m_units = units;
    m_frequency = frequency;
}

Configuration::Configuration(Configuration const* config){
    m_id = config->getId();
    m_identifier = config->getIdentifier();
    m_units = config->getUnits();
    m_frequency = config->getFrequency();
    m_leadTypes = config->getLeadTypes();
    m_coatings = config->getCoatings();
    m_energizations = config->getEnergizations();
    m_tolerances = config->getTolerances();
    m_conductorTypes = config->getConductorTypes();
    m_conductors = config->getConductors();
    m_buildingConductors = config->getBuildingConductors();
    m_buildings = config->getBuildings();
    m_cableTypes = config->getCableTypes();
    m_computations = config->getComputations();
    m_profiles = config->getProfiles();
}

Configuration::~Configuration(){
    m_leadTypes.clear();

    m_coatings.clear();

    m_energizations.clear();

    m_conductorTypes.clear();

    m_conductors.clear();

    m_buildingConductors.clear();

    m_buildings.clear();

    m_cableTypes.clear();

    m_profiles.clear();
}

Configuration& Configuration::operator=(Configuration const* config){
    m_id = config->getId();
    m_identifier = config->getIdentifier();
    m_units = config->getUnits();
    m_frequency = config->getFrequency();
    m_leadTypes = config->getLeadTypes();
    m_coatings = config->getCoatings();
    m_energizations = config->getEnergizations();
    m_tolerances = config->getTolerances();
    m_conductorTypes = config->getConductorTypes();
    m_conductors = config->getConductors();
    m_buildingConductors = config->getBuildingConductors();
    m_buildings = config->getBuildings();
    m_cableTypes = config->getCableTypes();
    m_computations = config->getComputations();
    m_profiles = config->getProfiles();

    return *this;
}

Configuration& Configuration::setId(std::string const& id){
    m_id = id;
    return *this;
}

Configuration& Configuration::setIdentifier(std::string const& identifier){
    m_identifier = identifier;
    return *this;
}

Configuration& Configuration::setUnits(std::string const& units){
    m_units = units;
    return *this;
}

Configuration& Configuration::setFrequency(std::string const& frequency){
    m_frequency = frequency;
    return *this;
}

Configuration& Configuration::setComputations(computations const& comp){
    m_computations = comp;
    return *this;
}

Configuration& Configuration::addLeadType(LeadType *leadType){
    bool alreadyPresent=false;

    if(m_leadTypes.count(leadType->getId())) alreadyPresent = true;

    if(!alreadyPresent) m_leadTypes.emplace(leadType->getId(), leadType);

    return *this;
}

Configuration& Configuration::removeLeadType(LeadType *leadType){
    if(m_leadTypes.count(leadType->getId())) m_leadTypes.erase(leadType->getId());

    return *this;
}

Configuration& Configuration::addCoating(Coating *coating){
    bool alreadyPresent=false;

    if(m_coatings.count(coating->getId())) alreadyPresent = true;

    if(!alreadyPresent) m_coatings.emplace(coating->getId(), coating);

    return *this;
}

Configuration& Configuration::removeCoating(Coating *coating){
    if(m_coatings.count(coating->getId())) m_coatings.erase(coating->getId());

    return *this;
}

Configuration& Configuration::addEnergization(Energization *energization){
    bool alreadyPresent=false;

    if(m_energizations.count(energization->getId())) alreadyPresent = true;

    if(!alreadyPresent) m_energizations.emplace(energization->getId(), energization);

    return *this;
}

Configuration& Configuration::removeEnergization(Energization *energization){
    if(m_energizations.count(energization->getId())) m_energizations.erase(energization->getId());

    return *this;
}

Configuration& Configuration::addTolerance(double const& tolerance){
    m_tolerances.push_back(tolerance);

    return *this;
}

Configuration& Configuration::removeTolerance(double const& tolerance){
    bool done;

    do{
        done = true;
        for(std::vector<double>::iterator it=m_tolerances.begin(); it!=m_tolerances.end(); it++){
            if(*it == tolerance){
                m_tolerances.erase(it);
                done = false;
                break;
            }
        }
    }while(!done);

    return *this;
}

Configuration& Configuration::addConductorType(ConductorType *conductorType){
    bool alreadyPresent=false;

    if(m_conductorTypes.count(conductorType->getId())) alreadyPresent = true;

    if(!alreadyPresent) m_conductorTypes.emplace(conductorType->getId(), conductorType);

    return *this;
}

Configuration& Configuration::removeConductorType(ConductorType *conductorType){
    if(m_conductorTypes.count(conductorType->getId())) m_conductorTypes.erase(conductorType->getId());

    return *this;
}

Configuration& Configuration::addConductor(Conductor *conductor){
    bool alreadyPresent=false;

    if(m_conductors.count(conductor->getId())) alreadyPresent = true;

    if(!alreadyPresent) m_conductors.emplace(conductor->getId(), conductor);

    return *this;
}

Configuration& Configuration::removeConductor(Conductor *conductor){
    if(m_conductors.count(conductor->getId())) m_conductors.erase(conductor->getId());

    return *this;
}

Configuration& Configuration::addBuildingConductor(Conductor *conductor){
    bool alreadyPresent=false;

    if(m_buildingConductors.count(conductor->getId())) alreadyPresent = true;

    if(!alreadyPresent) m_buildingConductors.emplace(conductor->getId(), conductor);

    return *this;
}

Configuration& Configuration::removeBuildingConductor(Conductor *conductor){
    if(m_buildingConductors.count(conductor->getId())) m_buildingConductors.erase(conductor->getId());

    return *this;
}

Configuration& Configuration::addBuilding(Building *building){
    bool alreadyPresent=false;

    if(m_buildings.count(building->getId())) alreadyPresent = true;

    if(!alreadyPresent) m_buildings.emplace(building->getId(), building);

    return *this;
}

Configuration& Configuration::removeBuilding(Building *building){
    if(m_buildings.count(building->getId())) m_buildings.erase(building->getId());

    return *this;
}

Configuration& Configuration::addProfile(profile* p){
    bool alreadyPresent=false;

    if(m_profiles.count(p->id)) alreadyPresent = true;

    if(!alreadyPresent) m_profiles.emplace(p->id, p);

    return *this;
}

Configuration& Configuration::removeProfile(profile* p){
    if(m_profiles.count(p->id)) m_profiles.erase(p->id);

    return *this;
}

Configuration& Configuration::addCableType(CableType* cableType){
    bool alreadyPresent=false;

    if(m_cableTypes.count(cableType->getId())) alreadyPresent = true;

    if(!alreadyPresent) m_cableTypes.emplace(cableType->getId(), cableType);

    return *this;
}

Configuration& Configuration::removeCableType(CableType* cableType){
    if(m_cableTypes.count(cableType->getId())) m_cableTypes.erase(cableType->getId());

    return *this;
}

computations& Configuration::setComputations(){
    return m_computations;
}

std::string const& Configuration::getId() const{
    return m_id;
}

std::string const& Configuration::getIdentifier() const{
    return m_identifier;
}

std::string const& Configuration::getUnits() const{
    return m_units;
}

std::string const& Configuration::getFrequency() const{
    return m_frequency;
}

std::unordered_map<std::string, LeadType*> Configuration::getLeadTypes() const{
    return m_leadTypes;
}

std::unordered_map<std::string, Coating*> Configuration::getCoatings() const{
    return m_coatings;
}

std::unordered_map<std::string, Energization*> Configuration::getEnergizations() const{
    return m_energizations;
}

std::vector<double> Configuration::getTolerances() const{
    return m_tolerances;
}

std::unordered_map<std::string, ConductorType*> Configuration::getConductorTypes() const{
    return m_conductorTypes;
}

std::unordered_map<std::string, Conductor*> Configuration::getConductors() const{
    return m_conductors;
}

std::unordered_map<std::string, Conductor*> Configuration::getBuildingConductors() const{
    return m_buildingConductors;
}

std::unordered_map<std::string, Building*> Configuration::getBuildings() const{
    return m_buildings;
}

computations const& Configuration::getComputations() const{
    return m_computations;
}

std::unordered_map<std::string, profile*> Configuration::getProfiles() const{
    return m_profiles;
}

std::unordered_map<std::string, CableType*> Configuration::getCableTypes() const{
    return m_cableTypes;
}

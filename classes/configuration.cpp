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

/*!
 \brief

 \fn Configuration::Configuration
*/
Configuration::Configuration(){
    m_identifier = "default";
    m_units = "Metric";
    m_frequency = "AC";
    m_modified = false;
}

/*!
 \brief

 \fn Configuration::Configuration
 \param identifier
 \param units
 \param frequency
*/
Configuration::Configuration(std::string const& identifier, std::string const& units, std::string const& frequency){
    m_identifier = identifier;
    m_units = units;
    m_frequency = frequency;
    m_modified = false;
}

/*!
 \brief

 \fn Configuration::Configuration
 \param config
*/
Configuration::Configuration(Configuration const* config){
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
    m_modified = false;
}

/*Configuration::Configuration(Configuration const* config){
    m_identifier = config->getIdentifier();
    m_units = config->getUnits();
    m_frequency = config->getFrequency();


    for(auto& lType : config->getLeadTypes()){
        m_leadTypes.emplace(lType.first, new LeadType(lType.second));
    }

    for(auto& coat : config->getCoatings()){
        m_coatings.emplace(coat.first, new Coating(coat.second));
    }

    for(auto& ener : config->getEnergizations()){
        m_energizations.emplace(ener.first, new Energization(ener.second));
    }

    m_tolerances = config->getTolerances();

    for(auto& cType : config->getConductorTypes()){
        m_conductorTypes.emplace(cType.first, new ConductorType(cType.second));
    }

    for(auto& cond : config->getConductors()){
        m_conductors.emplace(cond.first, new Conductor(cond.second));
    }

    for(auto& cond : config->getBuildingConductors()){
        m_buildingConductors.emplace(cond.first, new Conductor(cond.second));
    }

    for(auto& build : config->getBuildings()){
        m_buildings.emplace(build.first, new Building(build.second));
    }

    for(auto& cab : config->getCableTypes()){
        m_cableTypes.emplace(cab.first, new CableType(cab.second));
    }

    m_computations = config->getComputations();

    for(auto& pro : config->getProfiles()){
        profile* p;
        p = new profile();
        *p = *pro.second;
        m_profiles.emplace(pro.first, p);
    }
}*/

/*!
 \brief

 \fn Configuration::~Configuration
*/
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

bool Configuration::operator==(Configuration const* config){
    bool result = true;
    if(m_identifier != config->getIdentifier()) result = false;
    if(m_units != config->getUnits()) result = false;
    if(m_frequency != config->getFrequency()) result = false;

    if(m_leadTypes.size() == config->getLeadTypes().size()){
        for(auto& lType : m_leadTypes){
            if(lType.second != config->getLeadTypes().at(lType.first)) result = false;
        }
    }
    else{
        result = false;
    }

    if(m_coatings.size() == config->getCoatings().size()){
        for(auto& coat : m_coatings){
            if(coat.second != config->getCoatings().at(coat.first)) result = false;
        }
    }
    else{
        result = false;
    }

    if(m_energizations.size() == config->getEnergizations().size()){
        for(auto& ener : m_energizations){
            if(ener.second != config->getEnergizations().at(ener.first)) result = false;
        }
    }
    else{
        result = false;
    }

    if(m_tolerances.size() == config->getTolerances().size()){
        for(int i=0; i<m_tolerances.size(); i++){
            if(m_tolerances.at(i) != config->getTolerances().at(i)) result = false;
        }
    }
    else{
        result = false;
    }

    if(m_conductorTypes.size() == config->getConductorTypes().size()){
        for(auto& cType : m_conductorTypes){
            if(cType.second != config->getConductorTypes().at(cType.first)) result = false;
        }
    }
    else{
        result = false;
    }

    if(m_conductors.size() == config->getConductors().size()){
        for(auto& cond : m_conductors){
            if(cond.second != config->getConductors().at(cond.first)) result = false;
        }
    }
    else{
        result = false;
    }

    if(m_buildingConductors.size() == config->getBuildingConductors().size()){
        for(auto& cond : m_buildingConductors){
            if(cond.second != config->getBuildingConductors().at(cond.first)) result = false;
        }
    }
    else{
        result = false;
    }

    if(m_buildings.size() == config->getBuildings().size()){
        for(auto& build : m_buildings){
            if(build.second != config->getBuildings().at(build.first)) result = false;
        }
    }
    else{
        result = false;
    }

    if(m_cableTypes.size() == config->getCableTypes().size()){
        for(auto& cab : m_cableTypes){
            if(cab.second != config->getCableTypes().at(cab.first)) result = false;
        }
    }
    else{
        result = false;
    }

    if(m_computations != config->getComputations()) result = false;

    if(m_profiles.size() == config->getProfiles().size()){
        for(auto& pro : m_profiles){
            if(pro.second != config->getProfiles().at(pro.first)) result = false;
        }
    }
    else{
        result = false;
    }

    return result;
}

bool Configuration::operator!=(Configuration const* config){
    bool result = true;
    if(*this == config) result = false;
    return result;
}

/*!
 \brief

 \fn Configuration::operator =
 \param config
 \return Configuration &Configuration::operator
*/
Configuration& Configuration::operator=(Configuration const* config){
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

/*!
 \brief

 \fn Configuration::setIdentifier
 \param identifier
 \return Configuration
*/
Configuration& Configuration::setIdentifier(std::string const& identifier){
    m_identifier = identifier;
    return *this;
}

/*!
 \brief

 \fn Configuration::setUnits
 \param units
 \return Configuration
*/
Configuration& Configuration::setUnits(std::string const& units){
    m_units = units;
    return *this;
}

/*!
 \brief

 \fn Configuration::setFrequency
 \param frequency
 \return Configuration
*/
Configuration& Configuration::setFrequency(std::string const& frequency){
    m_frequency = frequency;
    return *this;
}

/*!
 \brief

 \fn Configuration::setComputations
 \param comp
 \return Configuration
*/
Configuration& Configuration::setComputations(computations const& comp){
    m_computations = comp;
    return *this;
}

/*!
 \brief

 \fn Configuration::addLeadType
 \param leadType
 \param newAdd
 \return Configuration
*/
Configuration& Configuration::addLeadType(std::shared_ptr<LeadType> leadType, bool const& newAdd){
    bool alreadyPresent=false;

    if(!newAdd){
        m_leadTypes.emplace(leadType->getId(), leadType);
    }
    else{
        if(m_leadTypes.count(leadType->getId())) alreadyPresent = true;

        if(!alreadyPresent){
            if(m_leadTypes.count(m_leadTypes.size()-1)){
                leadType->setId(m_leadTypes.size());
            }
            else{
                leadType->setId(m_leadTypes.size()-1);
            }
            m_leadTypes.emplace(leadType->getId(), leadType);
        }
    }

    return *this;
}

/*!
 \brief

 \fn Configuration::removeLeadType
 \param leadType
 \return Configuration
*/
int Configuration::removeLeadType(std::shared_ptr<LeadType> leadType){
    int errorCode = 0;

    if(!m_conductors.empty() || !m_buildingConductors.empty()){
        for(auto& cond : m_conductors){
            if(cond.second->getLeadType() == leadType) errorCode = 1;
        }

        for(auto& cond : m_buildingConductors){
            if(cond.second->getLeadType() == leadType) errorCode = 1;
        }

        if(errorCode == 0){
            if(m_leadTypes.count(leadType->getId())) m_leadTypes.erase(leadType->getId());
        }
    }
    else{
        if(m_leadTypes.count(leadType->getId())) m_leadTypes.erase(leadType->getId());
    }

    return errorCode;
}

int Configuration::replaceLeadType(std::shared_ptr<LeadType> leadType){
    int errorCode = 0;

    if(m_leadTypes.count(leadType->getId())) m_leadTypes.at(leadType->getId()) = leadType;

    if(!m_conductors.empty() || !m_buildingConductors.empty()){
        for(auto& cond : m_conductors){
            if(cond.second->getLeadType()->getId() == leadType->getId()){
                cond.second->setLeadType(m_leadTypes.at(leadType->getId()));
            }
        }

        for(auto& cond : m_buildingConductors){
            if(cond.second->getLeadType()->getId() == leadType->getId()){
                cond.second->setLeadType(m_leadTypes.at(leadType->getId()));
            }
        }
    }

    return errorCode;
}

/*!
 \brief

 \fn Configuration::addCoating
 \param coating
 \param newAdd
 \return Configuration
*/
Configuration& Configuration::addCoating(std::shared_ptr<Coating> coating, bool const& newAdd){
    bool alreadyPresent=false;

    if(!newAdd){
        m_coatings.emplace(coating->getId(), coating);
    }
    else{
        if(m_coatings.count(coating->getId())) alreadyPresent = true;

        if(!alreadyPresent){
            if(m_coatings.count(m_coatings.size()-1)){
                coating->setId(m_coatings.size());
            }
            else{
                coating->setId(m_coatings.size()-1);
            }
            m_coatings.emplace(coating->getId(), coating);
        }
    }

    return *this;
}

/*!
 \brief

 \fn Configuration::removeCoating
 \param coating
 \return Configuration
*/
int Configuration::removeCoating(std::shared_ptr<Coating> coating){
    int errorCode = 0;

    if(!m_conductors.empty() || !m_buildingConductors.empty()){
        for(auto& cond : m_conductors){
            if(cond.second->getCoating() == coating) errorCode = 1;
        }

        for(auto& cond : m_buildingConductors){
            if(cond.second->getCoating() == coating) errorCode = 1;
        }

        if(errorCode == 0){
            if(m_coatings.count(coating->getId())) m_coatings.erase(coating->getId());
        }
    }
    else{
        if(m_coatings.count(coating->getId())) m_coatings.erase(coating->getId());
    }

    return errorCode;
}

int Configuration::replaceCoating(std::shared_ptr<Coating> coating){
    int errorCode = 0;

    if(m_coatings.count(coating->getId())) m_coatings.at(coating->getId()) = coating;

    if(!m_conductors.empty() || !m_buildingConductors.empty()){
        for(auto& cond : m_conductors){
            if(cond.second->getCoating()->getId() == coating->getId()){
                cond.second->setCoating(m_coatings.at(coating->getId()));
            }
        }

        for(auto& cond : m_buildingConductors){
            if(cond.second->getCoating()->getId() == coating->getId()){
                cond.second->setCoating(m_coatings.at(coating->getId()));
            }
        }
    }

    return errorCode;
}

/*!
 \brief

 \fn Configuration::addEnergization
 \param energization
 \param newAdd
 \return Configuration
*/
Configuration& Configuration::addEnergization(std::shared_ptr<Energization> energization, bool const& newAdd){
    bool alreadyPresent=false;

    if(!newAdd){
        m_energizations.emplace(energization->getId(), energization);
    }
    else{
        if(m_energizations.count(energization->getId())) alreadyPresent = true;

        if(!alreadyPresent){
            if(m_energizations.count(m_energizations.size())){
                energization->setId(m_energizations.size()+1);
            }
            else{
                energization->setId(m_energizations.size());
            }
            m_energizations.emplace(energization->getId(), energization);
        }
    }

    return *this;
}

/*!
 \brief

 \fn Configuration::removeEnergization
 \param energization
 \return Configuration
*/
int Configuration::removeEnergization(std::shared_ptr<Energization> energization){
    int errorCode = 0;

    if(!m_conductors.empty() || !m_buildingConductors.empty()){
        for(auto& cond : m_conductors){
            if(cond.second->getEnergization() == energization) errorCode = 1;
        }

        for(auto& cond : m_buildingConductors){
            if(cond.second->getEnergization() == energization) errorCode = 1;
        }

        if(errorCode == 0){
            if(m_energizations.count(energization->getId())) m_energizations.erase(energization->getId());
        }
    }
    else{
        if(m_energizations.count(energization->getId())) m_energizations.erase(energization->getId());
    }

    return errorCode;
}

int Configuration::replaceEnergization(std::shared_ptr<Energization> energization){
    int errorCode = 0;

    if(m_energizations.count(energization->getId())) m_energizations.at(energization->getId()) = energization;

    if(!m_conductors.empty() || !m_buildingConductors.empty()){
        for(auto& cond : m_conductors){
            if(cond.second->getEnergization()->getId() == energization->getId()){
                cond.second->setEnergization(m_energizations.at(energization->getId()));
            }
        }

        for(auto& cond : m_buildingConductors){
            if(cond.second->getEnergization()->getId() == energization->getId()){
                cond.second->setEnergization(m_energizations.at(energization->getId()));
            }
        }
    }

    return errorCode;
}

/*!
 \brief

 \fn Configuration::addTolerance
 \param tolerance
 \return Configuration
*/
Configuration& Configuration::addTolerance(double const& tolerance){
    m_tolerances.push_back(tolerance);

    return *this;
}

/*!
 \brief

 \fn Configuration::removeTolerance
 \param tolerance
 \return Configuration
*/
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

/*!
 \brief

 \fn Configuration::addConductorType
 \param conductorType
 \param newAdd
 \return Configuration
*/
Configuration& Configuration::addConductorType(std::shared_ptr<ConductorType> conductorType, bool const& newAdd){
    bool alreadyPresent=false;

    if(!newAdd){
        m_conductorTypes.emplace(conductorType->getId(), conductorType);
    }
    else{
        if(m_conductorTypes.count(conductorType->getId())) alreadyPresent = true;

        if(!alreadyPresent){
            if(m_conductorTypes.count(m_conductorTypes.size()-1)){
                conductorType->setId(m_conductorTypes.size());
            }
            else{
                conductorType->setId(m_conductorTypes.size()-1);
            }
            m_conductorTypes.emplace(conductorType->getId(), conductorType);
        }
    }

    return *this;
}

/*!
 \brief

 \fn Configuration::removeConductorType
 \param conductorType
 \return Configuration
*/
int Configuration::removeConductorType(std::shared_ptr<ConductorType> conductorType){
    int errorCode = 0;

    if(!m_conductors.empty() || !m_buildingConductors.empty()){
        for(auto& cond : m_conductors){
            if(cond.second->getConductorType() == conductorType) errorCode = 1;
        }

        for(auto& cond : m_buildingConductors){
            if(cond.second->getConductorType() == conductorType) errorCode = 1;
        }

        if(errorCode == 0){
            if(m_conductorTypes.count(conductorType->getId())) m_conductorTypes.erase(conductorType->getId());
        }
    }
    else{
        if(m_conductorTypes.count(conductorType->getId())) m_conductorTypes.erase(conductorType->getId());
    }

    return errorCode;
}

int Configuration::replaceConductorType(std::shared_ptr<ConductorType> conductorType){
    int errorCode = 0;

    if(m_conductorTypes.count(conductorType->getId())) m_conductorTypes.at(conductorType->getId()) = conductorType;

    if(!m_conductors.empty() || !m_buildingConductors.empty()){
        for(auto& cond : m_conductors){
            if(cond.second->getConductorType()->getId() == conductorType->getId()){
                cond.second->setConductorType(m_conductorTypes.at(conductorType->getId()));
            }
        }

        for(auto& cond : m_buildingConductors){
            if(cond.second->getConductorType()->getId() == conductorType->getId()){
                cond.second->setConductorType(m_conductorTypes.at(conductorType->getId()));
            }
        }
    }

    return errorCode;
}

/*!
 \brief

 \fn Configuration::addConductor
 \param conductor
 \param newAdd
 \return Configuration
*/
Configuration& Configuration::addConductor(Conductor *conductor, bool const& newAdd){
    bool alreadyPresent=false;

    if(!newAdd){
        m_conductors.emplace(conductor->getId(), conductor);
    }
    else{
        if(m_conductors.count(conductor->getId())) alreadyPresent = true;

        if(!alreadyPresent){
            if(m_conductors.count(m_conductors.size())){
                conductor->setId(m_conductors.size()+1);
            }
            else{
                conductor->setId(m_conductors.size());
            }
            m_conductors.emplace(conductor->getId(), conductor);
        }
    }

    return *this;
}

/*!
 \brief

 \fn Configuration::removeConductor
 \param conductor
 \return Configuration
*/
Configuration& Configuration::removeConductor(Conductor *conductor){
    if(m_conductors.count(conductor->getId())) m_conductors.erase(conductor->getId());

    return *this;
}

/*!
 \brief

 \fn Configuration::addBuildingConductor
 \param conductor
 \param newAdd
 \return Configuration
*/
Configuration& Configuration::addBuildingConductor(Conductor *conductor, bool const& newAdd){
    bool alreadyPresent=false;

    if(!newAdd){
        m_buildingConductors.emplace(conductor->getId(), conductor);
    }
    else{
        if(m_buildingConductors.count(conductor->getId())) alreadyPresent = true;

        if(!alreadyPresent){
            if(m_buildingConductors.count(m_buildingConductors.size())){
                conductor->setId(m_buildingConductors.size()+1);
            }
            else{
                conductor->setId(m_buildingConductors.size());
            }
            m_buildingConductors.emplace(conductor->getId(), conductor);
        }
    }



    return *this;
}

/*!
 \brief

 \fn Configuration::removeBuildingConductor
 \param conductor
 \return Configuration
*/
Configuration& Configuration::removeBuildingConductor(Conductor *conductor){
    if(m_buildingConductors.count(conductor->getId())) m_buildingConductors.erase(conductor->getId());

    return *this;
}

/*!
 \brief

 \fn Configuration::addBuilding
 \param building
 \param newAdd
 \return Configuration
*/
Configuration& Configuration::addBuilding(std::shared_ptr<Building> building, bool const& newAdd){
    bool alreadyPresent=false;

    if(!newAdd){
        m_buildings.emplace(building->getId(), building);
    }
    else{
        if(m_buildings.count(building->getId())) alreadyPresent = true;

        if(!alreadyPresent){
            if(m_buildings.count(m_buildings.size())){
                building->setId(m_buildings.size()+1);
            }
            else{
                building->setId(m_buildings.size());
            }
            m_buildings.emplace(building->getId(), building);
        }
    }

    return *this;
}

/*!
 \brief

 \fn Configuration::removeBuilding
 \param building
 \return Configuration
*/
Configuration& Configuration::removeBuilding(std::shared_ptr<Building> building){
    if(m_buildings.count(building->getId())) m_buildings.erase(building->getId());

    return *this;
}

/*!
 \brief

 \fn Configuration::addProfile
 \param p
 \param newAdd
 \return Configuration
*/
Configuration& Configuration::addProfile(std::shared_ptr<profile> p, bool const& newAdd){
    bool alreadyPresent=false;

    if(!newAdd){
        m_profiles.emplace(p->id, p);
    }
    else{
        if(m_profiles.count(p->id)) alreadyPresent = true;

        if(!alreadyPresent){
            if(m_profiles.count(m_profiles.size()+1)){
                p->id = m_profiles.size()+2;
            }
            else{
                p->id = m_profiles.size()+1;
            }
            m_profiles.emplace(p->id, p);
        }
    }

    return *this;
}

/*!
 \brief

 \fn Configuration::removeProfile
 \param p
 \return Configuration
*/
Configuration& Configuration::removeProfile(std::shared_ptr<profile> p){
    if(m_profiles.count(p->id)) m_profiles.erase(p->id);

    return *this;
}

/*!
 \brief

 \fn Configuration::addCableType
 \param cableType
 \param newAdd
 \return Configuration
*/
Configuration& Configuration::addCableType(std::shared_ptr<CableType> cableType, bool const& newAdd){
    bool alreadyPresent=false;

    if(!newAdd){
        m_cableTypes.emplace(cableType->getId(), cableType);
    }
    else{
        if(m_cableTypes.count(cableType->getId())) alreadyPresent = true;

        if(!alreadyPresent){
            cableType->setId(m_cableTypes.size());
            m_cableTypes.emplace(cableType->getId(), cableType);
        }
    }

    return *this;
}

/*!
 \brief

 \fn Configuration::removeCableType
 \param cableType
 \return Configuration
*/
int Configuration::removeCableType(std::shared_ptr<CableType> cableType){
    int errorCode = 0;

    if(!m_conductors.empty() || !m_buildingConductors.empty()){
        for(auto& cond : m_conductors){
            if(cond.second->getCableType() == cableType) errorCode = 1;
        }

        for(auto& cond : m_buildingConductors){
            if(cond.second->getCableType() == cableType) errorCode = 1;
        }

        if(errorCode == 0){
            if(m_cableTypes.count(cableType->getId())) m_cableTypes.erase(cableType->getId());
        }
    }
    else{
        if(m_cableTypes.count(cableType->getId())) m_cableTypes.erase(cableType->getId());
    }

    return errorCode;
}

int Configuration::replaceCableType(std::shared_ptr<CableType> cableType){
    int errorCode = 0;

    if(m_cableTypes.count(cableType->getId())) m_cableTypes.at(cableType->getId()) = cableType;

    if(!m_conductors.empty() || !m_buildingConductors.empty()){
        for(auto& cond : m_conductors){
            if(cond.second->getCableType()->getId() == cableType->getId()){
                cond.second->setCableType(m_cableTypes.at(cableType->getId()));
            }
        }

        for(auto& cond : m_buildingConductors){
            if(cond.second->getCableType()->getId() == cableType->getId()){
                cond.second->setCableType(m_cableTypes.at(cableType->getId()));
            }
        }
    }

    return errorCode;
}

/*!
 \brief

 \fn Configuration::setComputations
 \return computations
*/
computations& Configuration::setComputations(){
    return m_computations;
}

/*!
 \brief

 \fn Configuration::getIdentifier
 \return const std::string
*/
std::string const& Configuration::getIdentifier() const{
    return m_identifier;
}

/*!
 \brief

 \fn Configuration::getUnits
 \return const std::string
*/
std::string const& Configuration::getUnits() const{
    return m_units;
}

/*!
 \brief

 \fn Configuration::getFrequency
 \return const std::string
*/
std::string const& Configuration::getFrequency() const{
    return m_frequency;
}

/*!
 \brief

 \fn Configuration::getLeadTypes
 \return std::unordered_map<int, LeadType *>
*/
std::unordered_map<int, std::shared_ptr<LeadType> > Configuration::getLeadTypes() const{
    return m_leadTypes;
}

/*!
 \brief

 \fn Configuration::getCoatings
 \return std::unordered_map<int, Coating *>
*/
std::unordered_map<int, std::shared_ptr<Coating>> Configuration::getCoatings() const{
    return m_coatings;
}

/*!
 \brief

 \fn Configuration::getEnergizations
 \return std::unordered_map<int, Energization *>
*/
std::unordered_map<int, std::shared_ptr<Energization> > Configuration::getEnergizations() const{
    return m_energizations;
}

/*!
 \brief

 \fn Configuration::getTolerances
 \return std::vector<double>
*/
std::vector<double> Configuration::getTolerances() const{
    return m_tolerances;
}

/*!
 \brief

 \fn Configuration::getConductorTypes
 \return std::unordered_map<int, ConductorType *>
*/
std::unordered_map<int, std::shared_ptr<ConductorType> > Configuration::getConductorTypes() const{
    return m_conductorTypes;
}

/*!
 \brief

 \fn Configuration::getConductors
 \return std::unordered_map<int, Conductor *>
*/
std::unordered_map<int, Conductor*> Configuration::getConductors() const{
    return m_conductors;
}

/*!
 \brief

 \fn Configuration::getBuildingConductors
 \return std::unordered_map<int, Conductor *>
*/
std::unordered_map<int, Conductor*> Configuration::getBuildingConductors() const{
    return m_buildingConductors;
}

/*!
 \brief

 \fn Configuration::getBuildings
 \return std::unordered_map<int, Building *>
*/
std::unordered_map<int, std::shared_ptr<Building> > Configuration::getBuildings() const{
    return m_buildings;
}

/*!
 \brief

 \fn Configuration::getComputations
 \return const computations
*/
computations const& Configuration::getComputations() const{
    return m_computations;
}

/*!
 \brief

 \fn Configuration::getProfiles
 \return std::unordered_map<int, profile *>
*/
std::unordered_map<int, std::shared_ptr<profile> > Configuration::getProfiles() const{
    return m_profiles;
}

/*!
 \brief

 \fn Configuration::getCableTypes
 \return std::unordered_map<int, CableType *>
*/
std::unordered_map<int, std::shared_ptr<CableType> > Configuration::getCableTypes() const{
    return m_cableTypes;
}

Configuration& Configuration::setModified(bool const& modified){
    m_modified = modified;
    return *this;
}

bool const& Configuration::isModified() const{
    return m_modified;
}

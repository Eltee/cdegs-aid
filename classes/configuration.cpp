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

Configuration::~Configuration(){
    for(std::vector<LeadType*>::iterator it=m_leadTypes.begin(); it!=m_leadTypes.end(); it++){
        delete(*it);
    }
    for(std::vector<Coating*>::iterator it=m_coatings.begin(); it!=m_coatings.end(); it++){
        delete(*it);
    }
    for(std::vector<Energization*>::iterator it=m_energizations.begin(); it!=m_energizations.end(); it++){
        delete(*it);
    }
    for(std::vector<ConductorType*>::iterator it=m_conductorTypes.begin(); it!=m_conductorTypes.end(); it++){
        delete(*it);
    }
    for(std::vector<Conductor*>::iterator it=m_conductors.begin(); it!=m_conductors.end(); it++){
        delete(*it);
    }
    for(std::vector<Conductor*>::iterator it=m_buildingConductors.begin(); it!=m_buildingConductors.end(); it++){
        delete(*it);
    }
    for(std::vector<Building*>::iterator it=m_buildings.begin(); it!=m_buildings.end(); it++){
        delete(*it);
    }
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

    for(std::vector<LeadType*>::iterator it=m_leadTypes.begin(); it!=m_leadTypes.end(); it++){
        if(*it == leadType){
            alreadyPresent = true;
            break;
        }
    }

    if(!alreadyPresent){
        m_leadTypes.push_back(leadType);
    }

    return *this;
}

Configuration& Configuration::removeLeadType(LeadType *leadType){
    bool done;

    do{
        done = true;
        for(std::vector<LeadType*>::iterator it=m_leadTypes.begin(); it!=m_leadTypes.end(); it++){
            if(*it == leadType){
                m_leadTypes.erase(it);
                done = false;
                break;
            }
        }
    }while(!done);

    return *this;
}

Configuration& Configuration::addCoating(Coating *coating){
    bool alreadyPresent=false;

    for(std::vector<Coating*>::iterator it=m_coatings.begin(); it!=m_coatings.end(); it++){
        if(*it == coating){
            alreadyPresent = true;
            break;
        }
    }

    if(!alreadyPresent){
        m_coatings.push_back(coating);
    }

    return *this;
}

Configuration& Configuration::removeCoating(Coating *coating){
    bool done;

    do{
        done = true;
        for(std::vector<Coating*>::iterator it=m_coatings.begin(); it!=m_coatings.end(); it++){
            if(*it == coating){
                m_coatings.erase(it);
                done = false;
                break;
            }
        }
    }while(!done);

    return *this;
}

Configuration& Configuration::addEnergization(Energization *energization){
    bool alreadyPresent=false;

    for(std::vector<Energization*>::iterator it=m_energizations.begin(); it!=m_energizations.end(); it++){
        if(*it == energization){
            alreadyPresent = true;
            break;
        }
    }

    if(!alreadyPresent){
        m_energizations.push_back(energization);
    }

    return *this;
}

Configuration& Configuration::removeEnergization(Energization *energization){
    bool done;

    do{
        done = true;
        for(std::vector<Energization*>::iterator it=m_energizations.begin(); it!=m_energizations.end(); it++){
            if(*it == energization){
                m_energizations.erase(it);
                done = false;
                break;
            }
        }
    }while(!done);

    return *this;
}

Configuration& Configuration::addTolerance(double const& tolerance){
    bool alreadyPresent=false;

    for(std::vector<double>::iterator it=m_tolerances.begin(); it!=m_tolerances.end(); it++){
        if(*it == tolerance){
            alreadyPresent = true;
            break;
        }
    }

    if(!alreadyPresent){
        m_tolerances.push_back(tolerance);
    }

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

    for(std::vector<ConductorType*>::iterator it=m_conductorTypes.begin(); it!=m_conductorTypes.end(); it++){
        if(*it == conductorType){
            alreadyPresent = true;
            break;
        }
    }

    if(!alreadyPresent){
        m_conductorTypes.push_back(conductorType);
    }

    return *this;
}

Configuration& Configuration::removeConductorType(ConductorType *conductorType){
    bool done;

    do{
        done = true;
        for(std::vector<ConductorType*>::iterator it=m_conductorTypes.begin(); it!=m_conductorTypes.end(); it++){
            if(*it == conductorType){
                m_conductorTypes.erase(it);
                done = false;
                break;
            }
        }
    }while(!done);

    return *this;
}

Configuration& Configuration::addConductor(Conductor *conductor){
    bool alreadyPresent=false;

    for(std::vector<Conductor*>::iterator it=m_conductors.begin(); it!=m_conductors.end(); it++){
        if(*it == conductor){
            alreadyPresent = true;
            break;
        }
    }

    if(!alreadyPresent){
        m_conductors.push_back(conductor);
    }

    return *this;
}

Configuration& Configuration::removeConductor(Conductor *conductor){
    bool done;

    do{
        done = true;
        for(std::vector<Conductor*>::iterator it=m_conductors.begin(); it!=m_conductors.end(); it++){
            if(*it == conductor){
                m_conductors.erase(it);
                done = false;
                break;
            }
        }
    }while(!done);

    return *this;
}

Configuration& Configuration::addBuilding(Building *building){
    bool alreadyPresent=false;

    for(std::vector<Building*>::iterator it=m_buildings.begin(); it!=m_buildings.end(); it++){
        if(*it == building){
            alreadyPresent = true;
            break;
        }
    }

    if(!alreadyPresent){
        m_buildings.push_back(building);
    }

    return *this;
}

Configuration& Configuration::removeBuilding(Building *building){
    bool done;

    do{
        done = true;
        for(std::vector<Building*>::iterator it=m_buildings.begin(); it!=m_buildings.end(); it++){
            if(*it == building){
                m_buildings.erase(it);
                done = false;
                break;
            }
        }
    }while(!done);

    return *this;
}

Configuration& Configuration::addProfile(profile const& p){
    bool alreadyPresent=false;

    for(std::vector<profile>::iterator it=m_profiles.begin(); it!=m_profiles.end(); it++){
        if(*it == p){
            alreadyPresent = true;
            break;
        }
    }

    if(!alreadyPresent){
        m_profiles.push_back(p);
    }

    return *this;
}

Configuration& Configuration::removeProfile(profile const& p){
    bool done;

    do{
        done = true;
        for(std::vector<profile>::iterator it=m_profiles.begin(); it!=m_profiles.end(); it++){
            if(*it == p){
                m_profiles.erase(it);
                done = false;
                break;
            }
        }
    }while(!done);

    return *this;
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

std::vector<LeadType*> const& Configuration::getLeadTypes() const{
    return m_leadTypes;
}

std::vector<Coating*> const& Configuration::getCoatings() const{
    return m_coatings;
}

std::vector<Energization*> const& Configuration::getEnergizations() const{
    return m_energizations;
}

std::vector<double> const& Configuration::getTolerances() const{
    return m_tolerances;
}

std::vector<ConductorType*> const& Configuration::getConductorTypes() const{
    return m_conductorTypes;
}

std::vector<Conductor*> const& Configuration::getConductors() const{
    return m_conductors;
}

std::vector<Conductor*> const& Configuration::getBuildingConductors() const{
    return m_buildingConductors;
}

std::vector<Building*> const& Configuration::getBuildings() const{
    return m_buildings;
}

computations const& Configuration::getComputations() const{
    return m_computations;
}

std::vector<profile> const& Configuration::getProfiles() const{
    return m_profiles;
}

/******************************************************************************
* Projet:     CDEGS-Aid
*  /Project
*
* Nom/Name:    configuration.h
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

#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <string>
#include <unordered_map>
#include <vector>
#include "energization.h"
#include "conductortype.h"
#include "conductor.h"
#include "building.h"
#include "leadtype.h"
#include "coating.h"
#include "cabletype.h"
#include "util/apputils.h"

class LeadType;
class Energization;
class Coating;
class ConductorType;
class Conductor;
class Building;
class CableType;

struct computations{
    bool GPR = false;
    bool POTENTIAL_SCALAR = false;
    bool ELECTRIC = false;
    bool MAGNETIC = false;
    bool VECTOR_POTENTIAL = false;
    bool GRADIENT_SCALAR = false;
};

struct profile{
    std::string id = "PR0";
    struct coords{
        double start = 0.0;
        double end = 0.0;
        double step = 0.0;
        bool operator==(const coords& c) const{
            bool result = true;
            if(start != c.start) result = false;
            if(end != c.end) result = false;
            if(step != c.step) result = false;
            return result;
        }
        bool operator!=(const coords& c) const{
            bool result = true;
            if(*this == c) result = false;
            return result;
        }
    } xCoords, yCoords;
    double NLine = 0.0;
    double MCol = 0.0;
    bool operator==(const profile& p) const{
        bool result = true;
        if(NLine !=  p.NLine) result = false;
        if(MCol != p.MCol) result = false;
        if(xCoords != p.xCoords) result = false;
        if(yCoords != p.yCoords) result = false;
        return result;
    }
    bool operator!=(const profile& p) const{
        bool result = true;
        if(*this == p) result = false;
        return result;
    }
};

class Configuration
{
    public:
        Configuration();
        Configuration(std::string const& identifier, std::string const& units, std::string const& frequency);
        Configuration(Configuration const* config);
        ~Configuration();
        Configuration& operator=(Configuration const* config);
        void setDefaultTypes();
    //Setters start-----------------------------------------------------
        Configuration& setId(std::string const& id);
        Configuration& setIdentifier(std::string const& identifier);
        Configuration& setUnits(std::string const& units);
        Configuration& setFrequency(std::string const& frequency);
        Configuration& addLeadType(LeadType* leadType);
        Configuration& removeLeadType(LeadType* leadType);
        Configuration& addCoating(Coating* coating);
        Configuration& removeCoating(Coating* coating);
        Configuration& addEnergization(Energization* energization);
        Configuration& removeEnergization(Energization* energization);
        Configuration& addTolerance(double const& tolerance);
        Configuration& removeTolerance(double const& tolerance);
        Configuration& addConductorType(ConductorType* conductorType);
        Configuration& removeConductorType(ConductorType* conductorType);
        Configuration& addConductor(Conductor* conductor);
        Configuration& removeConductor(Conductor* conductor);
        Configuration& addBuildingConductor(Conductor* conductor);
        Configuration& removeBuildingConductor(Conductor* conductor);
        Configuration& addBuilding(Building* building);
        Configuration& removeBuilding(Building* building);
        Configuration& setComputations(computations const& comp);
        Configuration& addProfile(profile* p);
        Configuration& removeProfile(profile* p);
        Configuration& addCableType(CableType* cableType);
        Configuration& removeCableType(CableType* cableType);
        computations& setComputations();
    //Setters end-------------------------------------------------------
    //Getters start-----------------------------------------------------
        std::string const& getId() const;
        std::string const& getIdentifier() const;
        std::string const& getUnits() const;
        std::string const& getFrequency() const;
        std::unordered_map<std::string, LeadType*> getLeadTypes() const;
        std::unordered_map<std::string, Coating*> getCoatings() const;
        std::unordered_map<std::string, Energization*> getEnergizations() const;
        std::vector<double> getTolerances() const;
        std::unordered_map<std::string, ConductorType*> getConductorTypes() const;
        std::unordered_map<std::string, Conductor*> getConductors() const;
        std::unordered_map<std::string, Conductor*> getBuildingConductors() const;
        std::unordered_map<std::string, Building*> getBuildings() const;
        computations const& getComputations() const;
        std::unordered_map<std::string, profile*> getProfiles() const;
        std::unordered_map<std::string, CableType*> getCableTypes() const;
    //Getters end-------------------------------------------------------

    private:
        std::string m_id, m_identifier, m_units, m_frequency;
        std::unordered_map<std::string, LeadType*> m_leadTypes;
        std::unordered_map<std::string, Coating*> m_coatings;
        std::unordered_map<std::string, Energization*> m_energizations;
        std::vector<double> m_tolerances;
        std::unordered_map<std::string, ConductorType*> m_conductorTypes;
        std::unordered_map<std::string, Conductor*> m_conductors, m_buildingConductors;
        std::unordered_map<std::string, Building*> m_buildings;
        std::unordered_map<std::string, CableType*> m_cableTypes;
        computations m_computations;
        std::unordered_map<std::string, profile*> m_profiles;
};

#endif // CONFIGURATION_H

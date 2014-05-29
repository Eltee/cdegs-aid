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
    int id = 1;

    struct coords{
        double x = 0.0;
        double y = 0.0;
        double z = 0.0;
        bool operator==(const coords& c) const{
            bool result = true;
            if(x != c.x) result = false;
            if(y != c.y) result = false;
            if(z != c.z) result = false;
            return result;
        }
        bool operator!=(const coords& c) const{
            bool result = true;
            if(*this == c) result = false;
            return result;
        }
    } start, ptStep, prStep;

    int ptNum = 0.0;
    int prNum = 0.0;

    void fromStepToCoords(){

    }

    void fromCoordsToStep(){

    }

    bool operator==(const profile& p) const{
        bool result = true;
        if(ptNum !=  p.ptNum) result = false;
        if(prNum != p.prNum) result = false;
        if(start != p.start) result = false;
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
        int idGenerator(const std::string& type);
    //Setters start-----------------------------------------------------
        Configuration& setIdentifier(std::string const& identifier);
        Configuration& setUnits(std::string const& units);
        Configuration& setFrequency(std::string const& frequency);
        Configuration& addLeadType(LeadType* leadType, bool const& newAdd=false);
        Configuration& removeLeadType(LeadType* leadType);
        Configuration& addCoating(Coating* coating, bool const& newAdd=false);
        Configuration& removeCoating(Coating* coating);
        Configuration& addEnergization(Energization* energization, bool const& newAdd=false);
        Configuration& removeEnergization(Energization* energization);
        Configuration& addTolerance(double const& tolerance);
        Configuration& removeTolerance(double const& tolerance);
        Configuration& addConductorType(ConductorType* conductorType, bool const& newAdd=false);
        Configuration& removeConductorType(ConductorType* conductorType);
        Configuration& addConductor(Conductor* conductor, bool const& newAdd=false);
        Configuration& removeConductor(Conductor* conductor);
        Configuration& addBuildingConductor(Conductor* conductor, bool const& newAdd=false);
        Configuration& removeBuildingConductor(Conductor* conductor);
        Configuration& addBuilding(Building* building, bool const& newAdd=false);
        Configuration& removeBuilding(Building* building);
        Configuration& setComputations(computations const& comp);
        Configuration& addProfile(profile* p, bool const& newAdd=false);
        Configuration& removeProfile(profile* p);
        Configuration& addCableType(CableType* cableType, bool const& newAdd=false);
        Configuration& removeCableType(CableType* cableType);
        computations& setComputations();
    //Setters end-------------------------------------------------------
    //Getters start-----------------------------------------------------
        std::string const& getIdentifier() const;
        std::string const& getUnits() const;
        std::string const& getFrequency() const;
        std::unordered_map<int, LeadType*> getLeadTypes() const;
        std::unordered_map<int, Coating*> getCoatings() const;
        std::unordered_map<int, Energization*> getEnergizations() const;
        std::vector<double> getTolerances() const;
        std::unordered_map<int, ConductorType*> getConductorTypes() const;
        std::unordered_map<int, Conductor*> getConductors() const;
        std::unordered_map<int, Conductor*> getBuildingConductors() const;
        std::unordered_map<int, Building*> getBuildings() const;
        computations const& getComputations() const;
        std::unordered_map<int, profile*> getProfiles() const;
        std::unordered_map<int, CableType*> getCableTypes() const;
    //Getters end-------------------------------------------------------

    private:
        std::string m_identifier, m_units, m_frequency;
        std::unordered_map<int, LeadType*> m_leadTypes;
        std::unordered_map<int, Coating*> m_coatings;
        std::unordered_map<int, Energization*> m_energizations;
        std::vector<double> m_tolerances;
        std::unordered_map<int, ConductorType*> m_conductorTypes;
        std::unordered_map<int, Conductor*> m_conductors, m_buildingConductors;
        std::unordered_map<int, Building*> m_buildings;
        std::unordered_map<int, CableType*> m_cableTypes;
        computations m_computations;
        std::unordered_map<int, profile*> m_profiles;
        struct ids{
                double leadTypeId=1;
                double coatingId=1;
                double energizationId=1;
                double conductorTypeId=1;
                double cableTypeId=1;
                double conductorId=1;
                double buildingConductorId=1;
                double buildingId=1;
                double profileId=1;
        } m_ids;
};

#endif // CONFIGURATION_H

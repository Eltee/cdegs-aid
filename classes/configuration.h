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
#include <cstdlib>
#include "structs.h"
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

/*!
 \brief Classe conteneur qui représente une configuration de simulation HiFreq

 Cette classe est un des gros morceaux du projet, contenant toutes les données requises pour générer un fichier de simulation HiFreq.

 \class Configuration configuration.h "classes/configuration.h"
*/
class Configuration
{
    public:
        Configuration();
        Configuration(std::string const& identifier, std::string const& units, std::string const& frequency);
        Configuration(Configuration const* config);
        ~Configuration();
        bool operator==(Configuration const* config);
        bool operator!=(Configuration const* config);
        Configuration& operator=(Configuration const* config);
        void setDefaultTypes();
        int idGenerator(const std::string& type);
    //Setters start-----------------------------------------------------
        Configuration& setIdentifier(std::string const& identifier);
        Configuration& setUnits(std::string const& units);
        Configuration& setFrequency(std::string const& frequency);
        Configuration& addLeadType(std::shared_ptr<LeadType> leadType, bool const& newAdd=false);
        Configuration& removeLeadType(std::shared_ptr<LeadType> leadType);
        Configuration& addCoating(std::shared_ptr<Coating> coating, bool const& newAdd=false);
        Configuration& removeCoating(std::shared_ptr<Coating> coating);
        Configuration& addEnergization(std::shared_ptr<Energization> energization, bool const& newAdd=false);
        Configuration& removeEnergization(std::shared_ptr<Energization> energization);
        Configuration& addTolerance(double const& tolerance);
        Configuration& removeTolerance(double const& tolerance);
        Configuration& addConductorType(std::shared_ptr<ConductorType> conductorType, bool const& newAdd=false);
        Configuration& removeConductorType(std::shared_ptr<ConductorType> conductorType);
        Configuration& addConductor(Conductor* conductor, bool const& newAdd=false);
        Configuration& removeConductor(Conductor* conductor);
        Configuration& addBuildingConductor(Conductor* conductor, bool const& newAdd=false);
        Configuration& removeBuildingConductor(Conductor* conductor);
        Configuration& addBuilding(std::shared_ptr<Building> building, bool const& newAdd=false);
        Configuration& removeBuilding(std::shared_ptr<Building> building);
        Configuration& setComputations(computations const& comp);
        Configuration& addProfile(std::shared_ptr<profile> p, bool const& newAdd=false);
        Configuration& removeProfile(std::shared_ptr<profile> p);
        Configuration& addCableType(std::shared_ptr<CableType> cableType, bool const& newAdd=false);
        Configuration& removeCableType(std::shared_ptr<CableType> cableType);
        computations& setComputations();
        Configuration& setModified(bool const& modified);
    //Setters end-------------------------------------------------------
    //Getters start-----------------------------------------------------
        std::string const& getIdentifier() const;
        std::string const& getUnits() const;
        std::string const& getFrequency() const;
        std::unordered_map<int, std::shared_ptr<LeadType>> getLeadTypes() const;
        std::unordered_map<int, std::shared_ptr<Coating>> getCoatings() const;
        std::unordered_map<int, std::shared_ptr<Energization>> getEnergizations() const;
        std::vector<double> getTolerances() const;
        std::unordered_map<int, std::shared_ptr<ConductorType>> getConductorTypes() const;
        std::unordered_map<int, Conductor*> getConductors() const;
        std::unordered_map<int, Conductor*> getBuildingConductors() const;
        std::unordered_map<int, std::shared_ptr<Building>> getBuildings() const;
        computations const& getComputations() const;
        std::unordered_map<int, std::shared_ptr<profile>> getProfiles() const;
        std::unordered_map<int, std::shared_ptr<CableType>> getCableTypes() const;
        bool const& isModified() const;
    //Getters end-------------------------------------------------------

    private:
        std::string m_identifier, m_units, m_frequency;
        std::unordered_map<int, std::shared_ptr<LeadType>> m_leadTypes;
        std::unordered_map<int, std::shared_ptr<Coating>> m_coatings;
        std::unordered_map<int, std::shared_ptr<Energization>> m_energizations;
        std::vector<double> m_tolerances;
        std::unordered_map<int, std::shared_ptr<ConductorType>> m_conductorTypes;
        std::unordered_map<int, Conductor*> m_conductors, m_buildingConductors;
        std::unordered_map<int, std::shared_ptr<Building>> m_buildings;
        std::unordered_map<int, std::shared_ptr<CableType>> m_cableTypes;
        computations m_computations;
        std::unordered_map<int, std::shared_ptr<profile>> m_profiles;
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
        bool m_modified;
};

#endif // CONFIGURATION_H

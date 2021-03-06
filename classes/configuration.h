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
        Configuration(std::string const identifier, std::string const units, std::string const frequency);
        Configuration(Configuration const* config);
        ~Configuration();
        bool operator==(Configuration const* config);
        bool operator!=(Configuration const* config);
        Configuration& operator=(Configuration const* config);
        void setDefaultTypes();
        bool validateConfig();
        double componentIdGenerator();
        void updateBuildingConductors(std::shared_ptr<Building> build);
        void clearBuildingConductors();
        int generateProfile(bool twoSided = false, bool rightSided = true, double step = 0.25, bool surface = true, double height = -1);
        void clearProfiles();
    //Setters start-----------------------------------------------------
        Configuration& setIdentifier(std::string const identifier);
        Configuration& setUnits(std::string const units);
        Configuration& setFrequency(std::string const frequency);
        Configuration& addLeadType(std::shared_ptr<LeadType> leadType);
        int removeLeadType(std::shared_ptr<LeadType> leadType);
        int replaceLeadType(std::shared_ptr<LeadType> leadType);
        Configuration& addCoating(std::shared_ptr<Coating> coating);
        int removeCoating(std::shared_ptr<Coating> coating);
        int replaceCoating(std::shared_ptr<Coating> coating);
        Configuration& addEnergization(std::shared_ptr<Energization> energization);
        int removeEnergization(std::shared_ptr<Energization> energization);
        int replaceEnergization(std::shared_ptr<Energization> energization);
        Configuration& addTolerance(double const tolerance);
        Configuration& removeTolerance(double const tolerance);
        Configuration& addConductorType(std::shared_ptr<ConductorType> conductorType);
        int removeConductorType(std::shared_ptr<ConductorType> conductorType);
        int replaceConductorType(std::shared_ptr<ConductorType> conductorType);
        Configuration& addConductor(std::shared_ptr<Conductor> conductor);
        int removeConductor(std::shared_ptr<Conductor> conductor);
        int replaceConductor(std::shared_ptr<Conductor> conductor);
        Configuration& addBuildingConductor(std::shared_ptr<Conductor> conductor);
        int removeBuildingConductor(std::shared_ptr<Conductor> conductor);
        int replaceBuildingConductor(std::shared_ptr<Conductor> conductor);
        Configuration& addBuilding(std::shared_ptr<Building> building);
        int removeBuilding(std::shared_ptr<Building> building);
        int replaceBuilding(std::shared_ptr<Building> building);
        Configuration& setComputations(computations const& comp);
        Configuration& addProfile(std::shared_ptr<profile> p);
        int removeProfile(std::shared_ptr<profile> p);
        int replaceProfile(std::shared_ptr<profile> p);
        Configuration& addCableType(std::shared_ptr<CableType> cableType);
        int removeCableType(std::shared_ptr<CableType> cableType);
        int replaceCableType(std::shared_ptr<CableType> cableType);
        computations& setComputations();
        Configuration& setModified(bool const modified);
        Configuration& setId(int const i);
    //Setters end-------------------------------------------------------
    //Getters start-----------------------------------------------------
        int getId() const;
        std::string getIdentifier() const;
        std::string getUnits() const;
        std::string getFrequency() const;
        std::vector<std::shared_ptr<LeadType>> getLeadTypes() const;
        std::vector<std::shared_ptr<Coating>> getCoatings() const;
        std::vector<std::shared_ptr<Energization>> getEnergizations() const;
        std::vector<double> getTolerances() const;
        std::vector<std::shared_ptr<ConductorType>> getConductorTypes() const;
        std::vector<std::shared_ptr<Conductor>> getConductors() const;
        std::vector<std::shared_ptr<Conductor>> getBuildingConductors() const;
        std::vector<std::shared_ptr<Building>> getBuildings() const;
        computations const& getComputations() const;
        std::vector<std::shared_ptr<profile>> getProfiles() const;
        std::vector<std::shared_ptr<CableType>> getCableTypes() const;
        bool isModified() const;
        std::shared_ptr<LeadType> getLeadType(double id) const;
        std::shared_ptr<Coating> getCoating(double id) const;
        std::shared_ptr<Energization> getEnergization(double id) const;
        std::shared_ptr<ConductorType> getConductorType(double id) const;
        std::shared_ptr<Conductor> getConductor(double id) const;
        std::shared_ptr<Conductor> getBuildingConductor(double id) const;
        std::shared_ptr<Building> getBuilding(double id) const;
        std::shared_ptr<profile> getProfile(double id) const;
        std::shared_ptr<CableType> getCableType(double id) const;
    //Getters end-------------------------------------------------------

    private:
        int m_id;
        std::string m_identifier, m_units, m_frequency;
        std::vector<std::shared_ptr<LeadType>> m_leadTypes;
        std::vector<std::shared_ptr<Coating>> m_coatings;
        std::vector<std::shared_ptr<Energization>> m_energizations;
        std::vector<double> m_tolerances;
        std::vector<std::shared_ptr<ConductorType>> m_conductorTypes;
        std::vector<std::shared_ptr<Conductor>> m_conductors, m_buildingConductors;
        std::vector<std::shared_ptr<Building>> m_buildings;
        std::vector<std::shared_ptr<CableType>> m_cableTypes;
        computations m_computations;
        std::vector<std::shared_ptr<profile>> m_profiles;
        bool m_modified;
        double m_componentId = -1;
};

#endif // CONFIGURATION_H

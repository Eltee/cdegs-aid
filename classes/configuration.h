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
 \brief Structure qui représente les computations demandée à HiFreq

 \class computations configuration.h "classes/configuration.h"
*/
struct computations{
    bool GPR = false;
    bool POTENTIAL_SCALAR = false;
    bool ELECTRIC = false;
    bool MAGNETIC = false;
    bool VECTOR_POTENTIAL = false;
    bool GRADIENT_SCALAR = false;
};

/*!
 \brief Structure qui représente un profil d'analyse fournis à HiFreq

 \class profile configuration.h "classes/configuration.h"
*/
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

    std::vector<coords> toCoords(){
        std::vector<coords> points;
        coords ptA, ptB, ptC;
        ptA.x = start.x;
        ptA.y = start.y;
        ptA.z = start.z;
        points.push_back(ptA);
        ptB.x = start.x + ((ptNum - 1) * ptStep.x);
        ptB.y = start.y + ((ptNum - 1) * ptStep.y);
        ptB.z = start.z + ((ptNum - 1) * ptStep.z);
        points.push_back(ptB);
        ptC.x = start.x + ((prNum - 1) * prStep.x);
        ptC.y = start.y + ((prNum - 1) * prStep.y);
        ptC.z = start.z + ((prNum - 1) * prStep.z);
        points.push_back(ptC);
        return points;
    }

    void fromCoordsToStep(double const& ptA_x, double const& ptA_y, double const& ptA_z, double const& ptB_x, double const& ptB_y, double const& ptB_z, double const& ptC_x, double const& ptC_y, double const& ptC_z, int const& numPt, int const& numPr){
       //Valeur de la coordonnée de départ
        start.x = ptA_x;
        start.y = ptA_y;
        start.z = ptA_z;

        coords ptA, ptB, ptC;

        ptA = start;

        ptB.x = ptB_x;
        ptB.y = ptB_y;
        ptB.z = ptB_z;

        ptC.x = ptC_x;
        ptC.y = ptC_y;
        ptC.z = ptC_z;

        ptNum = numPt;
        prNum = numPr;

        //Valeur Dx du Point Step
        if(ptA.x > 0 && ptB.x > 0){
            if(ptA.x > ptB.x) ptStep.x = -(ptA.x - ptB.x);
            else if(ptA.x < ptB.x) ptStep.x = (ptB.x - ptA.x);
        }
        else if(ptA.x > 0 && ptB.x < 0){
            ptStep.x = -(ptA.x + std::abs(ptB.x));
        }
        else if(ptA.x < 0 && ptB.x > 0){
            ptStep.x = (std::abs(ptA.x) + ptB.x);
        }
        else if(ptA.x < 0 && ptB.x < 0){
            if(ptA.x > ptB.x) ptStep.x = -(std::abs(ptB.x) - std::abs(ptA.x));
            else if(ptA.x < ptB.x) ptStep.x = (std::abs(ptA.x) - std::abs(ptB.x));
        }
        else if(ptA.x == 0 && ptB.x != 0){
            ptStep.x = ptB.x;
        }
        else if(ptA.x > 0 && ptB.x == 0){
            ptStep.x = -ptA.x;
        }
        else if(ptA.x < 0 && ptB.x == 0){
            ptStep.x = std::abs(ptA.x);
        }

        //Valeur Dy du Point Step
        if(ptA.y > 0 && ptB.y > 0){
            if(ptA.y > ptB.y) ptStep.y = -(ptA.y - ptB.y);
            else if(ptA.y < ptB.y) ptStep.y = (ptB.y - ptA.y);
        }
        else if(ptA.y > 0 && ptB.y < 0){
            ptStep.y = -(ptA.y + std::abs(ptB.y));
        }
        else if(ptA.y < 0 && ptB.y > 0){
            ptStep.y = (std::abs(ptA.y) + ptB.y);
        }
        else if(ptA.y < 0 && ptB.y < 0){
            if(ptA.y > ptB.y) ptStep.y = -(std::abs(ptB.y) - std::abs(ptA.y));
            else if(ptA.y < ptB.y) ptStep.y = (std::abs(ptA.y) - std::abs(ptB.y));
        }
        else if(ptA.y == 0 && ptB.y != 0){
            ptStep.y = ptB.y;
        }
        else if(ptA.y > 0 && ptB.y == 0){
            ptStep.y = -ptA.y;
        }
        else if(ptA.y < 0 && ptB.y == 0){
            ptStep.y = std::abs(ptA.y);
        }

        //Valeur Dz du Point Step
        if(ptA.z > 0 && ptB.z > 0){
            if(ptA.z > ptB.z) ptStep.z = -(ptA.z - ptB.z);
            else if(ptA.z < ptB.z) ptStep.z = (ptB.z - ptA.z);
        }
        else if(ptA.z > 0 && ptB.z < 0){
            ptStep.z = -(ptA.z + std::abs(ptB.z));
        }
        else if(ptA.z < 0 && ptB.z > 0){
            ptStep.z = (std::abs(ptA.z) + ptB.z);
        }
        else if(ptA.z < 0 && ptB.z < 0){
            if(ptA.z > ptB.z) ptStep.z = -(std::abs(ptB.z) - std::abs(ptA.z));
            else if(ptA.z < ptB.z) ptStep.z = (std::abs(ptA.z) - std::abs(ptB.z));
        }
        else if(ptA.z == 0 && ptB.z != 0){
            ptStep.z = ptB.z;
        }
        else if(ptA.z > 0 && ptB.z == 0){
            ptStep.z = -ptA.z;
        }
        else if(ptA.z < 0 && ptB.z == 0){
            ptStep.z = std::abs(ptA.z);
        }

        //Valeur Dx du Profile Step
        if(ptA.x > 0 && ptC.x > 0){
            if(ptA.x > ptC.x) prStep.x = -(ptA.x - ptC.x);
            else if(ptA.x < ptC.x) prStep.x = (ptC.x - ptA.x);
        }
        else if(ptA.x > 0 && ptC.x < 0){
            prStep.x = -(ptA.x + std::abs(ptC.x));
        }
        else if(ptA.x < 0 && ptC.x > 0){
            prStep.x = (std::abs(ptA.x) + ptC.x);
        }
        else if(ptA.x < 0 && ptC.x < 0){
            if(ptA.x > ptC.x) prStep.x = -(std::abs(ptC.x) - std::abs(ptA.x));
            else if(ptA.x < ptC.x) prStep.x = (std::abs(ptA.x) - std::abs(ptC.x));
        }
        else if(ptA.x == 0 && ptC.x != 0){
            prStep.x = ptB.x;
        }
        else if(ptA.x > 0 && ptC.x == 0){
            prStep.x = -ptA.x;
        }
        else if(ptA.x < 0 && ptC.x == 0){
            prStep.x = std::abs(ptA.x);
        }

        //Valeur Dy du Profile Step
        if(ptA.y > 0 && ptC.y > 0){
            if(ptA.y > ptC.y) prStep.y = -(ptA.y - ptC.y);
            else if(ptA.y < ptC.y) prStep.y = (ptC.y - ptA.y);
        }
        else if(ptA.y > 0 && ptC.y < 0){
            prStep.y = -(ptA.y + std::abs(ptC.y));
        }
        else if(ptA.y < 0 && ptC.y > 0){
            prStep.y = (std::abs(ptA.y) + ptC.y);
        }
        else if(ptA.y < 0 && ptC.y < 0){
            if(ptA.y > ptC.y) prStep.y = -(std::abs(ptC.y) - std::abs(ptA.y));
            else if(ptA.y < ptC.y) prStep.y = (std::abs(ptA.y) - std::abs(ptC.y));
        }
        else if(ptA.y == 0 && ptC.y != 0){
            prStep.y = ptB.y;
        }
        else if(ptA.y > 0 && ptC.y == 0){
            prStep.y = -ptA.y;
        }
        else if(ptA.y < 0 && ptC.y == 0){
            prStep.y = std::abs(ptA.y);
        }

        //Valeur Dz du Profile Step
        if(ptA.z > 0 && ptC.z > 0){
            if(ptA.z > ptC.z) prStep.z = -(ptA.z - ptC.z);
            else if(ptA.z < ptC.z) prStep.z = (ptC.z - ptA.z);
        }
        else if(ptA.z > 0 && ptC.z < 0){
            prStep.z = -(ptA.z + std::abs(ptC.z));
        }
        else if(ptA.z < 0 && ptC.z > 0){
            prStep.z = (std::abs(ptA.z) + ptC.z);
        }
        else if(ptA.z < 0 && ptC.z < 0){
            if(ptA.z > ptC.z) prStep.z = -(std::abs(ptC.z) - std::abs(ptA.z));
            else if(ptA.z < ptC.z) prStep.z = (std::abs(ptA.z) - std::abs(ptC.z));
        }
        else if(ptA.z == 0 && ptC.z != 0){
            prStep.z = ptB.z;
        }
        else if(ptA.z > 0 && ptC.z == 0){
            prStep.z = -ptA.z;
        }
        else if(ptA.z < 0 && ptC.z == 0){
            prStep.z = std::abs(ptA.z);
        }

        prStep.x /= (prNum - 1);
        prStep.y /= (prNum - 1);
        prStep.z /= (prNum - 1);
        ptStep.x /= (ptNum - 1);
        ptStep.y /= (ptNum - 1);
        ptStep.z /= (ptNum - 1);

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

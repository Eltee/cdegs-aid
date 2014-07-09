/******************************************************************************
* Projet:     CDEGS-Aid
*  /Project
*
* Nom/Name:    building.cpp
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

#include "building.h"

/*!
 \brief

 \fn Building::Building
*/
Building::Building() : Component("", false, true){
    m_faces = 2;
    m_height = 6.0;
    m_distance = 4.0;
    m_length = 6.0;
    m_step = 0.01;
}

/*!
 \brief

 \fn Building::Building
 \param faces
 \param height
 \param distanceMin
 \param distanceMax
 \param step
*/
Building::Building(const int faces, const double height, const double distance, const double step) : Component("", false, true){
    m_faces = faces;
    m_height = height;
    m_distance = distance;
    m_step = step;
}

Building::Building(Building const* build){
    m_id = build->getId();
    m_name = build->getName();
    m_locked = build->isLocked();
    m_saveable = build->isSaveable();
    m_faces = build->getFaces();
    m_height = build->getHeight();
    m_distance = build->getDistance();
    m_length = build->getLength();
    m_width = build->getWidth();
    m_radius = build->getRadius();
    m_step = build->getStep();
    m_leadType = build->getLeadType();
    m_conductorType = build->getConductorType();
    m_coating = build->getCoating();
    m_energization = build->getEnergization();
    m_cableType = build->getCableType();
}

/*!
 \brief

 \fn Building::~Building
*/
Building::~Building(){}

bool Building::operator==(Building const* build){
    bool result = true;
    if(m_id != build->getId()) result = false;
    if(m_name != build->getName()) result = false;
    if(m_locked != build->isLocked()) result = false;
    if(m_saveable != build->isSaveable()) result = false;
    if(m_faces != build->getFaces()) result = false;
    if(m_height != build->getHeight()) result = false;
    if(m_width != build->getWidth()) result = false;
    if(m_distance != build->getDistance()) result = false;
    if(m_length != build->getLength()) result = false;
    if(m_step != build->getStep()) result = false;
    if(m_radius != build->getRadius()) result = false;
    if(m_leadType->getId() != build->getLeadType()->getId()) result = false;
    if(m_conductorType->getId() != build->getConductorType()->getId()) result = false;
    if(m_coating->getId() != build->getCoating()->getId()) result = false;
    if(m_energization->getId() != build->getEnergization()->getId()) result = false;
    if(m_cableType->getId() != build->getCableType()->getId()) result = false;
    return result;
}

bool Building::operator!=(Building const* build){
    bool result = true;
    if(*this == build) result = false;
    return result;
}

/*!
 \brief

 \fn Building::getFaces
 \return const int
*/
int Building::getFaces() const{
    return m_faces;
}

/*!
 \brief

 \fn Building::getHeight
 \return const double
*/
int Building::getHeight() const{
    return m_height;
}

/*!
 \brief

 \fn Building::getDistanceMin
 \return const double
*/
int Building::getDistance() const{
    return m_distance;
}

/*!
 \brief

 \fn Building::getDistanceMax
 \return const double
*/
int Building::getLength() const{
    return m_length;
}

/*!
 \brief

 \fn Building::getDistanceMax
 \return const double
*/
int Building::getWidth() const{
    return m_width;
}

/*!
 \brief

 \fn Building::getStep
 \return const double
*/
double Building::getStep() const{
    return m_step;
}

double Building::getRadius() const{
    return m_radius;
}

/**
 * @brief
 *
 * @return LeadType
 */
std::shared_ptr<LeadType> Building::getLeadType() const{
    return m_leadType;
}

/**
 * @brief
 *
 * @return ConductorType
 */
std::shared_ptr<ConductorType> Building::getConductorType() const{
    return m_conductorType;
}

/**
 * @brief
 *
 * @return Coating
 */
std::shared_ptr<Coating> Building::getCoating() const{
    return m_coating;
}

/**
 * @brief
 *
 * @return Energization
 */
std::shared_ptr<Energization> Building::getEnergization() const{
    return m_energization;
}

/**
 * @brief
 *
 * @return CableType
 */
std::shared_ptr<CableType> Building::getCableType() const{
    return m_cableType;
}

/*!
 \brief

 \fn Building::setFaces
 \param faces
 \return Building
*/
Building& Building::setFaces(int const faces){
    m_faces = faces;
    return *this;
}

/*!
 \brief

 \fn Building::setHeight
 \param height
 \return Building
*/
Building& Building::setHeight(int const height){
    m_height = height;
    return *this;
}

/*!
 \brief

 \fn Building::setDistanceMin
 \param distanceMin
 \return Building
*/
Building& Building::setDistance(int const distance){
    m_distance = distance;
    return *this;
}

/*!
 \brief

 \fn Building::setDistanceMax
 \param distanceMax
 \return Building
*/
Building& Building::setLength(int const length){
    m_length = length;
    return *this;
}

/*!
 \brief

 \fn Building::setDistanceMax
 \param distanceMax
 \return Building
*/
Building& Building::setWidth(int const width){
    m_width = width;
    return *this;
}

/*!
 \brief

 \fn Building::setStep
 \param step
 \return Building
*/
Building& Building::setStep(double const step){
    m_step = step;
    return *this;
}

Building& Building::setRadius(double const radius){
    m_radius = radius;
    return *this;
}

/**
 * @brief
 *
 * @param leadType
 * @return Conductor
 */
Building& Building::setLeadType(std::shared_ptr<LeadType> leadType){
    m_leadType = leadType;
    return *this;
}

/**
 * @brief
 *
 * @param conductorType
 * @return Conductor
 */
Building& Building::setConductorType(std::shared_ptr<ConductorType> conductorType){
    m_conductorType = conductorType;
    return *this;
}

/**
 * @brief
 *
 * @param coating
 * @return Conductor
 */
Building& Building::setCoating(std::shared_ptr<Coating> coating){
    m_coating = coating;
    return *this;
}

/**
 * @brief
 *
 * @param energization
 * @return Conductor
 */
Building& Building::setEnergization(std::shared_ptr<Energization> energization){
    m_energization = energization;
    return *this;
}

/**
 * @brief
 *
 * @param cableType
 * @return Conductor
 */
Building& Building::setCableType(std::shared_ptr<CableType> cableType){
    m_cableType = cableType;
    return *this;
}

bool Building::validateBuilding(){
    bool valid = true;

    if(!m_leadType) valid = false;
    if(!m_coating) valid = false;
    if(!m_conductorType) valid = false;
    if(!m_energization) valid = false;
    if(!m_cableType) valid = false;

    if(m_faces < 2 || m_faces > 5) valid = false;
    if(m_height < 1 || m_height > 9999) valid = false;
    if(m_distance < 1 || m_distance > 9999) valid = false;
    if(m_length < 1 || m_length > 9999) valid = false;
    if(m_radius <= 0 || m_radius > 9999) valid = false;
    if(m_step == 0) valid = false;

    return valid;
}

std::vector<std::shared_ptr<Conductor>> Building::generateConductors(){
    std::vector<std::shared_ptr<Conductor>> conductors;

    int startX, startY, startZ;

    startX = -(m_width / 2);
    startZ = 1;
    startY = m_distance;

    if(m_faces >= 2){
        //front face - horizontal
        for(double d = startZ; d >= -m_height; d -= m_step){
            std::shared_ptr<Conductor> cond;
            cond.reset(new Conductor());
            coords start, end;
            start.x = startX;
            end.x = (startX + m_width - 1);
            start.y = startY;
            end.y = startY;
            start.z = d;
            end.z = d;
            cond->setCoords(start, end);
            cond->setRadius(m_radius);
            cond->setLeadType(m_leadType);
            cond->setCoating(m_coating);
            cond->setConductorType(m_conductorType);
            cond->setEnergization(m_energization);
            cond->setCableType(m_cableType);
            conductors.push_back(cond);
        }

        //front face - vertical
        for(double d = startX; d <= (startX + m_width - 1); d += m_step){
            std::shared_ptr<Conductor> cond;
            cond.reset(new Conductor());
            coords start, end;
            start.x = d;
            end.x = d;
            start.y = startY;
            end.y = startY;
            start.z = startZ;
            end.z = -m_height;
            cond->setCoords(start, end);
            cond->setRadius(m_radius);
            cond->setLeadType(m_leadType);
            cond->setCoating(m_coating);
            cond->setConductorType(m_conductorType);
            cond->setEnergization(m_energization);
            cond->setCableType(m_cableType);
            conductors.push_back(cond);
        }

        //roof - horizontal (skips the first, already done by front - horizontal)
        for(double d = (startY + m_step); d <= (startY + m_length - 1); d += m_step){
            std::shared_ptr<Conductor> cond;
            cond.reset(new Conductor());
            coords start, end;
            start.x = startX;
            end.x = (startX + m_width - 1);
            start.y = d;
            end.y = d;
            start.z = -m_height;
            end.z = -m_height;
            cond->setCoords(start, end);
            cond->setRadius(m_radius);
            cond->setLeadType(m_leadType);
            cond->setCoating(m_coating);
            cond->setConductorType(m_conductorType);
            cond->setEnergization(m_energization);
            cond->setCableType(m_cableType);
            conductors.push_back(cond);
        }

        //roof - vertical
        for(double d = startX; d <= (startX + m_width - 1); d += m_step){
            std::shared_ptr<Conductor> cond;
            cond.reset(new Conductor());
            coords start, end;
            start.x = d;
            end.x = d;
            start.y = startY;
            end.y = (startY + m_length - 1);
            start.z = -m_height;
            end.z = -m_height;
            cond->setCoords(start, end);
            cond->setRadius(m_radius);
            cond->setLeadType(m_leadType);
            cond->setCoating(m_coating);
            cond->setConductorType(m_conductorType);
            cond->setEnergization(m_energization);
            cond->setCableType(m_cableType);
            conductors.push_back(cond);
        }
    }

    //side faces
    if(m_faces >= 3){
        //horizontal (skips the last, already done by roof - vertical)
        for(double d = startZ; d >= -(m_height - m_step); d -= m_step){
            std::shared_ptr<Conductor> cond;
            cond.reset(new Conductor());
            coords start, end;
            start.x = startX;
            end.x = startX;
            start.y = startY;
            end.y = (startY + m_length - 1);
            start.z = d;
            end.z = d;
            cond->setCoords(start, end);
            cond->setRadius(m_radius);
            cond->setLeadType(m_leadType);
            cond->setCoating(m_coating);
            cond->setConductorType(m_conductorType);
            cond->setEnergization(m_energization);
            cond->setCableType(m_cableType);
            conductors.push_back(cond);
        }

        //vertical (skips the first, already done by front - vertical)
        for(double d = (startY + m_step); d <= (startY + m_length - 1); d += m_step){
            std::shared_ptr<Conductor> cond;
            cond.reset(new Conductor());
            coords start, end;
            start.x = startX;
            end.x = startX;
            start.y = d;
            end.y = d;
            start.z = startZ;
            end.z = -m_height;
            cond->setCoords(start, end);
            cond->setRadius(m_radius);
            cond->setLeadType(m_leadType);
            cond->setCoating(m_coating);
            cond->setConductorType(m_conductorType);
            cond->setEnergization(m_energization);
            cond->setCableType(m_cableType);
            conductors.push_back(cond);
        }
    }

    if(m_faces >= 4){
        //horizontal (skips the last, already done by roof - vertical)
        for(double d = startZ; d >= -(m_height - m_step); d -= m_step){
            std::shared_ptr<Conductor> cond;
            cond.reset(new Conductor());
            coords start, end;
            start.x = (startX + m_width - 1);
            end.x = (startX + m_width - 1);
            start.y = startY;
            end.y = (startY + m_length - 1);
            start.z = d;
            end.z = d;
            cond->setCoords(start, end);
            cond->setRadius(m_radius);
            cond->setLeadType(m_leadType);
            cond->setCoating(m_coating);
            cond->setConductorType(m_conductorType);
            cond->setEnergization(m_energization);
            cond->setCableType(m_cableType);
            conductors.push_back(cond);
        }

        //vertical (skips the first, already done by front - vertical)
        for(double d = (startY + m_step); d <= (startY + m_length - 1); d += m_step){
            std::shared_ptr<Conductor> cond;
            cond.reset(new Conductor());
            coords start, end;
            start.x = (startX + m_width - 1);
            end.x = (startX + m_width - 1);
            start.y = d;
            end.y = d;
            start.z = startZ;
            end.z = -m_height;
            cond->setCoords(start, end);
            cond->setRadius(m_radius);
            cond->setLeadType(m_leadType);
            cond->setCoating(m_coating);
            cond->setConductorType(m_conductorType);
            cond->setEnergization(m_energization);
            cond->setCableType(m_cableType);
            conductors.push_back(cond);
        }
    }

    if(m_faces >= 5){
        //back face - horizontal (skips the last; already done by roof - horizontal)
        for(double d = startZ; d >= -(m_height - m_step); d -= m_step){
            std::shared_ptr<Conductor> cond;
            cond.reset(new Conductor());
            coords start, end;
            start.x = startX;
            end.x = (startX + m_width - 1);
            start.y = (startY + m_length - 1);
            end.y = (startY + m_length - 1);
            start.z = d;
            end.z = d;
            cond->setCoords(start, end);
            cond->setRadius(m_radius);
            cond->setLeadType(m_leadType);
            cond->setCoating(m_coating);
            cond->setConductorType(m_conductorType);
            cond->setEnergization(m_energization);
            cond->setCableType(m_cableType);
            conductors.push_back(cond);
        }

        //back face - vertical (skips first and last; both done by both sides)
        for(double d = (startX + m_step); d <= (startX + m_width - 1 - m_step); d += m_step){
            std::shared_ptr<Conductor> cond;
            cond.reset(new Conductor());
            coords start, end;
            start.x = d;
            end.x = d;
            start.y = (startY + m_length - 1);
            end.y = (startY + m_length - 1);
            start.z = startZ;
            end.z = -m_height;
            cond->setCoords(start, end);
            cond->setRadius(m_radius);
            cond->setLeadType(m_leadType);
            cond->setCoating(m_coating);
            cond->setConductorType(m_conductorType);
            cond->setEnergization(m_energization);
            cond->setCableType(m_cableType);
            conductors.push_back(cond);
        }
    }

    return conductors;
}

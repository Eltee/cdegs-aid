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
Building::Building() : Component(0, "", false, true){
    m_faces = 2;
    m_height = 6.0;
    m_distanceMin = 4.0;
    m_distanceMax = 6.0;
    m_step = 0.5;
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
Building::Building(int const& faces, double const& height, double const& distanceMin, double const& distanceMax, double const& step) : Component(0, "", false, true){
    m_faces = faces;
    m_height = height;
    m_distanceMin = distanceMin;
    m_distanceMax = distanceMax;
    m_step = step;
}

/*!
 \brief

 \fn Building::~Building
*/
Building::~Building(){}

/*!
 \brief

 \fn Building::getFaces
 \return const int
*/
int const& Building::getFaces() const{
    return m_faces;
}

/*!
 \brief

 \fn Building::getHeight
 \return const double
*/
double const& Building::getHeight() const{
    return m_height;
}

/*!
 \brief

 \fn Building::getDistanceMin
 \return const double
*/
double const& Building::getDistanceMin() const{
    return m_distanceMin;
}

/*!
 \brief

 \fn Building::getDistanceMax
 \return const double
*/
double const& Building::getDistanceMax() const{
    return m_distanceMax;
}

/*!
 \brief

 \fn Building::getStep
 \return const double
*/
double const& Building::getStep() const{
    return m_step;
}

/*!
 \brief

 \fn Building::setFaces
 \param faces
 \return Building
*/
Building& Building::setFaces(int const& faces){
    m_faces = faces;
    return *this;
}

/*!
 \brief

 \fn Building::setHeight
 \param height
 \return Building
*/
Building& Building::setHeight(double const& height){
    m_height = height;
    return *this;
}

/*!
 \brief

 \fn Building::setDistanceMin
 \param distanceMin
 \return Building
*/
Building& Building::setDistanceMin(double const& distanceMin){
    m_distanceMin = distanceMin;
    return *this;
}

/*!
 \brief

 \fn Building::setDistanceMax
 \param distanceMax
 \return Building
*/
Building& Building::setDistanceMax(double const& distanceMax){
    m_distanceMax = distanceMax;
    return *this;
}

/*!
 \brief

 \fn Building::setStep
 \param step
 \return Building
*/
Building& Building::setStep(double const& step){
    m_step = step;
    return *this;
}


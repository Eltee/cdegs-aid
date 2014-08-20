/******************************************************************************
* Projet:     PROJECT_NAME
*  /Project
*
* Nom/Name:    name_here.h
*
* Description: Lorem ipsum dolor sit amet, consectetur adipiscing elit.
*              Vestibulum posuere venenatis aliquet. Proin sit amet ornare
*              libero, nec aliquam mi. Curabitur iaculis, quam ultrices
*              vulputate laoreet, felis risus consectetur sem, quis semper
*              tortor ante ac lacus. Sed porttitor aliquam blandit. Nullam
*              vel eros ac velit mattis scelerisque.
*
* Auteur:      Renaud Bigras, Hydro-Qu�bec Trans�nergie
*  /Author
*
* Cr��:        07-05-2014
*  /Created
*
* Copyright:   (c) Renaud Bigras 2014
*
*   This file is part of PROJECT_NAME.
*
*   PROJECT_NAME is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   PROJECT_NAME is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with PROJECT_NAME. If not, see <http://www.gnu.org/licenses/>.
*******************************************************************************/

#ifndef STRUCTS_H
#define STRUCTS_H

#include <QDate>
#include <QTextDocument>
#include <vector>

/*!
 \brief Structure qui représente un ensemble de coordonnées XYZ.

 \class coords configuration.h "classes/configuration.h"
*/
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
};

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

    bool operator==(computations const& c){
        bool result = true;
        if(GPR != c.GPR) result = false;
        if(POTENTIAL_SCALAR != c.POTENTIAL_SCALAR) result = false;
        if(ELECTRIC != c.ELECTRIC) result = false;
        if(MAGNETIC != c.MAGNETIC) result = false;
        if(VECTOR_POTENTIAL != c.VECTOR_POTENTIAL) result = false;
        if(GRADIENT_SCALAR != c.GRADIENT_SCALAR) result = false;
        return result;
    }

    bool operator!=(computations const& c){
        bool result = true;
        if(*this == c) result = false;
        return result;
    }
};

/*!
 \brief Structure qui représente un profil d'analyse fournis à HiFreq

 \class profile configuration.h "classes/configuration.h"
*/
struct profile{

    profile(){
        id = -1;
        ptNum = 0;
        prNum = 0;
        start.x = 0;
        start.y = 0;
        start.z = 0;
        ptStep.x = 0;
        ptStep.y = 0;
        ptStep.z = 0;
        prStep.x = 0;
        prStep.y = 0;
        prStep.z = 0;
        surface = true;
    }

    profile(profile const* pro){
        id = pro->id;
        ptNum = pro->ptNum;
        prNum = pro->prNum;
        start.x = pro->start.x;
        start.y = pro->start.y;
        start.z = pro->start.z;
        ptStep.x = pro->ptStep.x;
        ptStep.y = pro->ptStep.y;
        ptStep.z = pro->ptStep.z;
        prStep.x = pro->prStep.x;
        prStep.y = pro->prStep.y;
        prStep.z = pro->prStep.z;
        surface = pro->surface;
    }

    double id = -1;

    coords start, ptStep, prStep;

    int ptNum = 0.0;
    int prNum = 0.0;

    bool surface = true;

    bool compare(profile const* pro){
        if(id == pro->id) return true;
        else return false;
    }

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

    void fromCoords(coords ptA, coords ptB, coords ptC, double stepsPt, double stepsPr){
        double minX = 9999.0;
        double minY = 9999.0;
        double minZ = -9999.0;
        double maxX = -9999.0;
        double maxY = -9999.0;
        double maxZ = 9999.0;

        if(ptA.x < minX) minX = ptA.x;
        if(ptB.x < minX) minX = ptB.x;
        if(ptC.x < minX) minX = ptC.x;

        if(ptA.y < minY) minY = ptA.y;
        if(ptB.y < minY) minY = ptB.y;
        if(ptC.y < minY) minY = ptC.y;

        if(ptA.z > minZ) minZ = ptA.z;
        if(ptB.z > minZ) minZ = ptB.z;
        if(ptC.z > minZ) minZ = ptC.z;

        if(ptA.x > maxX) maxX = ptA.x;
        if(ptB.x > maxX) maxX = ptB.x;
        if(ptC.x > maxX) maxX = ptC.x;

        if(ptA.y > maxY) maxY = ptA.y;
        if(ptB.y > maxY) maxY = ptB.y;
        if(ptC.y > maxY) maxY = ptC.y;

        if(ptA.z < maxZ) maxZ = ptA.z;
        if(ptB.z < maxZ) maxZ = ptB.z;
        if(ptC.z < maxZ) maxZ = ptC.z;

        start.x = minX;
        start.y = minY;
        start.z = minZ;

        if(maxX - minX > 0) ptStep.x = stepsPt;
        if(maxZ - minZ < 0) ptStep.z = -stepsPt;
        if(maxY - minY > 0) prStep.y = stepsPr;

        if(ptStep.x != 0 && ptStep.z != 0){
            if((maxX - minX) > std::abs(maxZ - minZ)){
                ptNum = ((maxX - minX) / ptStep.x);
            }
            else if((maxX - minX) < std::abs(maxZ - minZ)){
                ptNum = ((maxZ - minZ) / ptStep.z);
            }
        }

        if(prStep.y != 0){
            prNum = ((maxY - minY)  / prStep.y);
        }

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
        if(ptStep != p.ptStep) result = false;
        if(prStep != p.prStep) result = false;
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
 \brief Struct qui représente les métadonnées d'un projet.

 Cette structure contient les métadonnées du projet courant, c'est-à-dire:
 - son nom,
 - sa date de création,
 - l'auteur/propriétaire du projet,
 - un texte descriptif

 \class project_metadata project.h "classes/project.h"
*/
struct project_metadata{
        std::string name;
        QDate date;
        std::string author;
        QTextDocument description;

        bool operator==(const project_metadata& pm){
            bool result = true;
            if(author != pm.author) result = false;
            if(date != pm.date) result = false;
            //if(description != pm.description) result = false;
            if(name != pm.name) result = false;
            return result;
        }

        bool operator!=(const project_metadata& pm){
            bool result = true;
            if(*this == pm) result = false;
            return result;
        }
};

/*!
 \brief Struct qui représente les paramètres propres à un projet. Présentement non-implémenté.

 Cette struct représente les paramètres du projet courant. Les paramètres sont présentement
 non-implémentés.

 \class project_settings project.h "classes/project.h"
*/
struct project_settings{
        std::string set1;
        std::string set2;
        std::string set3;
        std::string set4;
};

#endif // STRUCTS_H

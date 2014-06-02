/******************************************************************************
* Projet:     CDEGS-Aid
*  /Project
*
* Nom/Name:    apputils.h
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

#ifndef APPUTILS_H
#define APPUTILS_H

#include <vector>
#include <QString>
#include <iostream>
#include <QDir>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fstream>
#include <memory>
#include <math.h>
#include <unordered_map>
#include <wchar.h>
#include "lib/pugixml.hpp"
#include "classes/project.h"
#include "classes/configuration.h"
#include "classes/building.h"
#include "classes/cabletype.h"
#include "classes/coating.h"
#include "classes/conductor.h"
#include "classes/conductortype.h"
#include "classes/energization.h"
#include "classes/leadtype.h"

class Project;
class Configuration;
class Building;
class CableType;
class Coating;
class Conductor;
class ConductorType;
class Energization;
class LeadType;

/*!
 \brief Classe singleton qui sert d'outil général pour le projet.

 La classe AppUtil est instanciée une seule fois et statique. La raison qu'elle est implémentée en tant que singleton plutôt que de simplement avoir des méthodes statiques est à cause de son rôle de logger.

 Contient des méthodes de sauvegarde, de log et de lecture.

 \class AppUtils apputils.h "util/apputils.h"
*/
class AppUtils
{
    public:
        static AppUtils& getInstance(){
            static AppUtils instance; // Guaranteed to be destroyed.
                                              // Instantiated on first use.
            return instance;
        }
        void saveProject(const Project& project, std::string& path); //done
        void saveProject(const Project& project); //done
        void saveConfiguration(const Configuration* config, pugi::xml_node& parent); //done
        void exportConfiguration(const Configuration* config, const std::string& fullPath); //done

        std::vector<double> drange(double start, double end, double step);
        std::string getOsName();
        double pi() { return std::atan(1)*4; }
        double radians(const double& d);
        double degrees(const double& r);
        std::string stringToUpper(std::string strToConvert);
        inline const char* BoolToString(const bool& b) const;
        void readXML(const pugi::xml_node& toIter, int iteration=0);

        std::string uniqueIdGenerator(); //done

        void loadStylesheets();
        std::unordered_map<std::string, QString> const& getStyleSheets() const;
        QString const& getStyle(std::string name) const;
        std::string getAppData();
        std::string getPath(const QString& folderPath, const QString& filename);
        std::string getPath(const QString& filename);

        void setDefaultConfig(); //done
        void loadDefaultConfig(); //done
        void generateDefaultConfig(); //done
        Configuration const* getDefaultConfig() const; //done
        Configuration* loadConfig(pugi::xml_node configNode) const; //done
        Project* loadProject(const QString& folder, const QString& filename); //done
        Project* loadProject(const wchar_t* fullPath); //done

        std::string my_utf8(const char * str) { return str; }
        std::string my_utf8(const wchar_t * str) { return pugi::as_utf8(str); }
        std::string dbl2str(const double& d);
        void append_dbl2str(std::string &s, const double& d);
    private:
        AppUtils() {}
        AppUtils(AppUtils const&);
        void operator=(AppUtils const&);
        double m_projectId=0;
        Configuration* m_defaultConfig;
        std::unordered_map<std::string, QString> m_styleSheets;
};

#endif // APPUTILS_H

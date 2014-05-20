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
#include "lib/pugixml.hpp"
#include "classes/project.h"
#include "classes/configuration.h"

class Project;
class Configuration;

class AppUtils
{
    public:
        static AppUtils& getInstance(){
            static AppUtils instance; // Guaranteed to be destroyed.
                                              // Instantiated on first use.
            return instance;
        }
        void initialize();
        void saveIds();
        void saveProject(const Project &project);
        void saveConfiguration(Configuration* const config, pugi::xml_document &doc);
        std::vector<double> drange(double start, double end, double step);
        std::string getOsName();
        void readXML(pugi::xml_node toIter, int iteration=0);
        std::string uniqueIdGenerator(std::string type);
        const wchar_t* getXMLPath(QString folderPath, QString filename);
        const wchar_t* getXMLPath(QString filename);
        std::string my_utf8(const char * str) { return str; }
        std::string my_utf8(const wchar_t * str) { return pugi::as_utf8(str); }
        std::string dbl2str(double d);
        void append_dbl2str(std::string &s, double d);
    private:
        AppUtils() {}
        AppUtils(AppUtils const&);
        void operator=(AppUtils const&);
        struct ids{
                double projectId=0;
                double configurationId=0;
                double leadTypeId=0;
                double coatingId=0;
                double energizationId=0;
                double conductorTypeId=0;
                double cableTypeId=0;
                double conductorId=0;
                double buildingConductorId=0;
                double buildingId=0;
                double profileId=0;
        } m_ids;
};

#endif // APPUTILS_H

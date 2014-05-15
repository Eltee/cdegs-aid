/******************************************************************************
* Projet:     CDEGS-Aid
*  /Project
*
* Nom/Name:    project.h
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

#ifndef PROJECT_H
#define PROJECT_H

#include <string>
#include <QDate>
#include <QTextDocument>
#include <vector>
#include "configuration.h"

class Project
{
    public:
        Project();
        ~Project();
    private:
        std::string m_id;
        std::string m_absPath;
        std::string m_relPath;
        Configuration* m_defaultConfig;
        Configuration* m_lastConfig;
        std::string m_defaultWindow;
        std::string m_lastWindow;
        struct metadata{
            std::string name;
            QDate date;
            std::string author;
            QTextDocument description;
        } m_metadata;
        struct projectSettings{
            std::string set1;
            std::string set2;
            std::string set3;
            std::string set4;
        } m_projectSettings;
        std::vector<Configuration*> m_configurations;
};

#endif // PROJECT_H

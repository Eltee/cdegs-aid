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
#include <unordered_map>
#include <QDir>
#include <QString>
#include <memory>
#include <stdio.h>
#include "structs.h"
#include "util/apputils.h"
#include "configuration.h"

class Configuration;

/*!
 \brief Classe conteneur mère. La classe principal du modèle. Contient le projet courant.

 Cette classe contient plusieurs attributs propre à un certain projet et contient une ou plusieurs
 configurations.

 \class Project project.h "classes/project.h"
*/
class Project
{
    public:
        Project();
        Project(std::string const& name, std::string fileName, QDate const& date, std::string const& author, std::string const& description);
        ~Project();
        Project(Project const* project);
        Project& operator=(Project const* project);
        bool operator==(Project const* project);
        bool operator!=(Project const* project);
        double componentIdGenerator();
    //Setters start---------------------------------------------------------------
        Project& setAbsPath(std::string const& absPath);
        Project& setRelPath(std::string const& relPath);
        Project& setFileName(const std::string& fileName);
        Project& setDefaultWindow(std::string const& defaultWindow);
        Project& setLastWindow(std::string const& lastWindow);
        Project& setDefaultConfig(std::shared_ptr<Configuration> defaultConfig);
        Project& setLastConfig(std::shared_ptr<Configuration> lastConfig);
        Project& setMetaName(std::string const& name);
        Project& setMetaAuthor(std::string const& author);
        Project& setMetaDescription(std::string const& description);
        Project& setMetaDate(std::string const& date);
        Project& setMetaDate(QDate const& date);
        Project& setProjSet1(std::string const& set1);
        Project& setProjSet2(std::string const& set2);
        Project& setProjSet3(std::string const& set3);
        Project& setProjSet4(std::string const& set4);
        Project& addConfiguration(std::shared_ptr<Configuration> config, const bool& newAdd=false);
        Project& removeConfiguration(std::shared_ptr<Configuration> config);
        Project& replaceConfiguration(std::shared_ptr<Configuration> config);
        Project& setId(std::string const& id);
        Project& setModified(bool const& mod);
    //Setters end-----------------------------------------------------------------
    //Getters start---------------------------------------------------------------
        std::string const& getId() const;
        std::string const& getAbsPath() const;
        std::string const& getRelPath() const;
        std::string const& getFileName() const;
        std::string const& getDefaultWindow() const;
        std::string const& getLastWindow() const;
        std::weak_ptr<Configuration> getDefaultConfig() const;
        std::weak_ptr<Configuration> getLastConfig() const;
        project_metadata const& getMetadata() const;
        project_settings const& getSettings() const;
        std::unordered_map<int, std::shared_ptr<Configuration>> getConfigurations() const;
        bool const& isModified() const;
    //Getters end-----------------------------------------------------------------
    private:
        std::string m_id, m_absPath, m_relPath, m_defaultWindow, m_lastWindow, m_fileName;
        std::weak_ptr<Configuration> m_defaultConfig;
        std::weak_ptr<Configuration> m_lastConfig;
        project_metadata m_metadata;
        project_settings m_projectSettings;
        std::unordered_map<int, std::shared_ptr<Configuration>> m_configurations;
        bool m_modified;
        double m_componentId = 0;
};

#endif // PROJECT_H

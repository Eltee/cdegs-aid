/******************************************************************************
* Projet:     CDEGS-Aid
*  /Project
*
* Nom/Name:    project.cpp
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

#include "project.h"


Project::Project(){
    m_id = AppUtils::getInstance().uniqueIdGenerator("ProjectId");
    m_absPath = QDir::current().absolutePath().toStdString();
    m_relPath = QDir::current().path().toStdString();
    m_defaultWindow = "Metadata";
    m_lastWindow = "Metadata";
    m_metadata.author = "";
    m_metadata.date = QDate::currentDate();
    m_metadata.name = "Project " + m_id;
    m_projectSettings.set1 = "";
    m_projectSettings.set2 = "";
    m_projectSettings.set3 = "";
    m_projectSettings.set4 = "";
}

Project::Project(std::string const& name, std::string const& date, std::string const& author, std::string const& description){
    m_id = AppUtils::getInstance().uniqueIdGenerator("ProjectId");
    m_absPath = QDir::current().absolutePath().toStdString();
    m_relPath = QDir::current().path().toStdString();
    m_defaultWindow = "Metadata";
    m_lastWindow = "Metadata";
    m_metadata.author = author;
    m_metadata.date = QDate::fromString(QString::fromStdString(date));
    m_metadata.description.setPlainText(QString::fromStdString(description));
    m_metadata.name = name;
    m_projectSettings.set1 = "";
    m_projectSettings.set2 = "";
    m_projectSettings.set3 = "";
    m_projectSettings.set4 = "";
}

Project::~Project(){
    delete(m_defaultConfig);
    delete(m_lastConfig);
    for(std::vector<Configuration*>::iterator it=m_configurations.begin(); it!=m_configurations.end(); it++){
        delete(*it);
    }
}

std::string const& Project::getId() const{
    return m_id;
}

std::string const& Project::getAbsPath() const{
    return m_absPath;
}

std::string const& Project::getRelPath() const{
    return m_relPath;
}

std::string const& Project::getDefaultWindow() const{
    return m_defaultWindow;
}

std::string const& Project::getLastWindow() const{
    return m_lastWindow;
}

Configuration const* Project::getDefaultConfig() const{
    return m_defaultConfig;
}

Configuration const* Project::getLastConfig() const{
    return m_lastConfig;
}

project_metadata const& Project::getMetadata() const{
    return m_metadata;
}

project_settings const& Project::getSettings() const{
    return m_projectSettings;
}

std::vector<Configuration*> Project::getConfigurations() const{
    return m_configurations;
}

Project& Project::setAbsPath(std::string const& absPath){
    m_absPath = absPath;
    return *this;
}

Project& Project::setRelPath(std::string const& relPath){
    m_relPath = relPath;
    return *this;
}

Project& Project::setDefaultWindow(std::string const& defaultWindow){
    m_defaultWindow = defaultWindow;
    return *this;
}

Project& Project::setLastWindow(std::string const& lastWindow){
    m_lastWindow = lastWindow;
    return *this;
}

Project& Project::setDefaultConfig(Configuration* defaultConfig){
    m_defaultConfig = defaultConfig;
    return *this;
}

Project& Project::setLastConfig(Configuration* lastConfig){
    m_lastConfig = lastConfig;
    return *this;
}

Project& Project::setMetaName(std::string const& name){
    m_metadata.name = name;
    return *this;
}

Project& Project::setMetaAuthor(std::string const& author){
    m_metadata.author = author;
    return *this;
}

Project& Project::setMetaDescription(std::string const& description){
    m_metadata.description.setPlainText(QString::fromStdString(description));
    return *this;
}

Project& Project::setMetaDate(std::string const& date){
    m_metadata.date = QDate::fromString(QString::fromStdString(date));
    return *this;
}

Project& Project::setMetaDate(QDate const& date){
    m_metadata.date = date;
    return *this;
}

Project& Project::setProjSet1(std::string const& set1){
    m_projectSettings.set1 = set1;
    return *this;
}

Project& Project::setProjSet2(std::string const& set2){
    m_projectSettings.set2 = set2;
    return *this;
}

Project& Project::setProjSet3(std::string const& set3){
    m_projectSettings.set3 = set3;
    return *this;
}

Project& Project::setProjSet4(std::string const& set4){
    m_projectSettings.set4 = set4;
    return *this;
}

Project& Project::addConfiguration(Configuration* config){
    bool alreadyPresent=false;

    for(std::vector<Configuration*>::iterator it=m_configurations.begin(); it!=m_configurations.end(); it++){
        if(*it == config){
            alreadyPresent = true;
            break;
        }
    }

    if(!alreadyPresent){
        m_configurations.push_back(config);
    }

    return *this;
}

Project& Project::removeConfiguration(Configuration* config){
    bool done;

    do{
        done = true;
        for(std::vector<Configuration*>::iterator it=m_configurations.begin(); it!=m_configurations.end(); it++){
            if(*it == config){
                m_configurations.erase(it);
                done = false;
                break;
            }
        }
    }while(!done);

    return *this;
}


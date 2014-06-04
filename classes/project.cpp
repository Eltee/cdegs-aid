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


/*!
 \brief

 \fn Project::Project
*/
Project::Project(){
    m_id = AppUtils::getInstance().uniqueIdGenerator();
    m_absPath = QDir::current().absolutePath().toStdString();
    m_relPath = QDir::current().path().toStdString();
    m_fileName = "Project" + m_id + ".cdp";
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

/*!
 \brief

 \fn Project::Project
 \param name
 \param fileName
 \param date
 \param author
 \param description
*/
Project::Project(std::string const& name, std::string fileName, QDate const& date, std::string const& author, std::string const& description){
    m_id = AppUtils::getInstance().uniqueIdGenerator();
    m_absPath = QDir::current().absolutePath().toStdString();
    m_relPath = QDir::current().path().toStdString();
    m_fileName = fileName;
    m_fileName.erase(remove_if(m_fileName.begin(), m_fileName.end(), isspace), m_fileName.end());
    m_defaultWindow = "Metadata";
    m_lastWindow = "Metadata";
    m_metadata.author = author;
    m_metadata.date = date;
    m_metadata.description.setPlainText(QString::fromStdString(description));
    m_metadata.name = name;
    m_projectSettings.set1 = "";
    m_projectSettings.set2 = "";
    m_projectSettings.set3 = "";
    m_projectSettings.set4 = "";
}

/*!
 \brief

 \fn Project::~Project
*/
Project::~Project(){
    for(std::unordered_map<std::string, Configuration*>::iterator it=m_configurations.begin(); it!=m_configurations.end(); it++){
        delete(it->second);
    }
}

/*!
 \brief

 \fn Project::Project
 \param project
*/
Project::Project(Project const* project){
    m_id = project->getId();
    m_absPath = project->getAbsPath();
    m_relPath = project->getRelPath();
    m_defaultConfig = project->getDefaultConfig();
    m_lastConfig = project->getLastConfig();
    m_defaultWindow = project->getDefaultWindow();
    m_lastWindow = project->getLastWindow();
    m_metadata.author = project->getMetadata().author;
    m_metadata.date = project->getMetadata().date;
    m_metadata.name = project->getMetadata().name;
    m_metadata.description.setPlainText(project->getMetadata().description.toPlainText());
    m_projectSettings.set1 = "";
    m_projectSettings.set2 = "";
    m_projectSettings.set3 = "";
    m_projectSettings.set4 = "";
    m_configurations = project->getConfigurations();
}

/*!
 \brief

 \fn Project::operator =
 \param project
 \return Project &Project::operator
*/
Project& Project::operator=(Project const* project){
    m_id = project->getId();
    m_absPath = project->getAbsPath();
    m_relPath = project->getRelPath();
    m_defaultConfig = project->getDefaultConfig();
    m_lastConfig = project->getLastConfig();
    m_defaultWindow = project->getDefaultWindow();
    m_lastWindow = project->getLastWindow();
    m_metadata.author = project->getMetadata().author;
    m_metadata.date = project->getMetadata().date;
    m_metadata.name = project->getMetadata().name;
    m_metadata.description.setPlainText(project->getMetadata().description.toPlainText());
    m_projectSettings.set1 = "";
    m_projectSettings.set2 = "";
    m_projectSettings.set3 = "";
    m_projectSettings.set4 = "";
    m_configurations = project->getConfigurations();

    return *this;
}

bool Project::operator==(Project const* project) const{
    bool result = true;
    if(m_id != project->getId()) result = false;
    if(m_absPath != project->getAbsPath()) result = false;
    if(m_relPath != project->getRelPath()) result = false;
    if(m_defaultConfig != project->getDefaultConfig()) result = false;
    if(m_lastConfig != project->getLastConfig()) result = false;
    if(m_defaultWindow != project->getDefaultWindow()) result = false;
    if(m_lastWindow != project->getLastWindow()) result = false;
    if(m_metadata != project->getMetadata()) result = false;
    if(m_configurations.size() == project->getConfigurations().size()){
        for(auto& config : project->getConfigurations()){
            if(m_configurations.at(config.first) != config.second) result = false;
        }
    }
    else{
        result = false;
    }
    return result;
}

bool Project::operator!=(Project const* project) const{
    bool result = true;
    if(*this == project) result = false;
    return result;
}

/*!
 \brief

 \fn Project::getId
 \return const std::string
*/
std::string const& Project::getId() const{
    return m_id;
}

/*!
 \brief

 \fn Project::getAbsPath
 \return const std::string
*/
std::string const& Project::getAbsPath() const{
    return m_absPath;
}

/*!
 \brief

 \fn Project::getRelPath
 \return const std::string
*/
std::string const& Project::getRelPath() const{
    return m_relPath;
}

/*!
 \brief

 \fn Project::getFileName
 \return const std::string
*/
std::string const& Project::getFileName() const{
    return m_fileName;
}

/*!
 \brief

 \fn Project::getDefaultWindow
 \return const std::string
*/
std::string const& Project::getDefaultWindow() const{
    return m_defaultWindow;
}

/*!
 \brief

 \fn Project::getLastWindow
 \return const std::string
*/
std::string const& Project::getLastWindow() const{
    return m_lastWindow;
}

/*!
 \brief

 \fn Project::getDefaultConfig
 \return Configuration
*/
Configuration* Project::getDefaultConfig() const{
    return m_defaultConfig;
}

/*!
 \brief

 \fn Project::getLastConfig
 \return Configuration
*/
Configuration* Project::getLastConfig() const{
    return m_lastConfig;
}

/*!
 \brief

 \fn Project::getMetadata
 \return const project_metadata
*/
project_metadata const& Project::getMetadata() const{
    return m_metadata;
}

/*!
 \brief

 \fn Project::getSettings
 \return const project_settings
*/
project_settings const& Project::getSettings() const{
    return m_projectSettings;
}

/*!
 \brief

 \fn Project::getConfigurations
 \return std::unordered_map<std::string, Configuration *>
*/
std::unordered_map<std::string, Configuration*> Project::getConfigurations() const{
    return m_configurations;
}

/*!
 \brief

 \fn Project::setAbsPath
 \param absPath
 \return Project
*/
Project& Project::setAbsPath(std::string const& absPath){
    m_absPath = absPath;
    return *this;
}

/*!
 \brief

 \fn Project::setRelPath
 \param relPath
 \return Project
*/
Project& Project::setRelPath(std::string const& relPath){
    m_relPath = relPath;
    return *this;
}

/*!
 \brief

 \fn Project::setFileName
 \param fileName
 \return Project
*/
Project& Project::setFileName(std::string const& fileName){
    m_fileName = fileName;
    m_fileName.erase(remove_if(m_fileName.begin(), m_fileName.end(), isspace), m_fileName.end());
    return *this;
}

/*!
 \brief

 \fn Project::setDefaultWindow
 \param defaultWindow
 \return Project
*/
Project& Project::setDefaultWindow(std::string const& defaultWindow){
    m_defaultWindow = defaultWindow;
    return *this;
}

/*!
 \brief

 \fn Project::setLastWindow
 \param lastWindow
 \return Project
*/
Project& Project::setLastWindow(std::string const& lastWindow){
    m_lastWindow = lastWindow;
    return *this;
}

/*!
 \brief

 \fn Project::setDefaultConfig
 \param defaultConfig
 \return Project
*/
Project& Project::setDefaultConfig(Configuration* defaultConfig){
    m_defaultConfig = defaultConfig;
    return *this;
}

/*!
 \brief

 \fn Project::setLastConfig
 \param lastConfig
 \return Project
*/
Project& Project::setLastConfig(Configuration* lastConfig){
    m_lastConfig = lastConfig;
    return *this;
}

/*!
 \brief

 \fn Project::setMetaName
 \param name
 \return Project
*/
Project& Project::setMetaName(std::string const& name){
    m_metadata.name = name;
    return *this;
}

/*!
 \brief

 \fn Project::setMetaAuthor
 \param author
 \return Project
*/
Project& Project::setMetaAuthor(std::string const& author){
    m_metadata.author = author;
    return *this;
}

/*!
 \brief

 \fn Project::setMetaDescription
 \param description
 \return Project
*/
Project& Project::setMetaDescription(std::string const& description){
    m_metadata.description.setPlainText(QString::fromStdString(description));
    return *this;
}

/*!
 \brief

 \fn Project::setMetaDate
 \param date
 \return Project
*/
Project& Project::setMetaDate(std::string const& date){
    m_metadata.date = QDate::fromString(QString::fromStdString(date));
    return *this;
}

/*!
 \brief

 \fn Project::setMetaDate
 \param date
 \return Project
*/
Project& Project::setMetaDate(QDate const& date){
    m_metadata.date = date;
    return *this;
}

/*!
 \brief

 \fn Project::setProjSet1
 \param set1
 \return Project
*/
Project& Project::setProjSet1(std::string const& set1){
    m_projectSettings.set1 = set1;
    return *this;
}

/*!
 \brief

 \fn Project::setProjSet2
 \param set2
 \return Project
*/
Project& Project::setProjSet2(std::string const& set2){
    m_projectSettings.set2 = set2;
    return *this;
}

/*!
 \brief

 \fn Project::setProjSet3
 \param set3
 \return Project
*/
Project& Project::setProjSet3(std::string const& set3){
    m_projectSettings.set3 = set3;
    return *this;
}

/*!
 \brief

 \fn Project::setProjSet4
 \param set4
 \return Project
*/
Project& Project::setProjSet4(std::string const& set4){
    m_projectSettings.set4 = set4;
    return *this;
}

/*!
 \brief

 \fn Project::addConfiguration
 \param config
 \return Project
*/
Project& Project::addConfiguration(Configuration* config){
    bool alreadyPresent=false;

    if(m_configurations.count(config->getIdentifier())) alreadyPresent = true;

    if(!alreadyPresent) m_configurations.emplace(config->getIdentifier(), config);

    return *this;
}

/*!
 \brief

 \fn Project::removeConfiguration
 \param config
 \return Project
*/
Project& Project::removeConfiguration(Configuration* config){
    if(m_configurations.count(config->getIdentifier())) m_configurations.erase(config->getIdentifier());

    return *this;
}

/*!
 \brief

 \fn Project::setId
 \param id
 \return Project
*/
Project& Project::setId(std::string const& id){
    m_id = id;

    return *this;
}

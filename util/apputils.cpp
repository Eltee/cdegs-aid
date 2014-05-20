/******************************************************************************
* Projet:     CDEGS-Aid
*  /Project
*
* Nom/Name:    apputils.cpp
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

#include "apputils.h"

void AppUtils::initialize(){
    pugi::xml_document doc;

    QString path = qgetenv("USERNAME").constData();
    path += "_ids.cdi";

    if (!doc.load_file(getXMLPath(path))){
        std::cout << "Failure";
    }

    pugi::xml_node node = doc.first_child();

    std::string value;

    for(pugi::xml_node_iterator it = node.children().begin(); it != node.children().end(); it++){
        if(my_utf8(it->name()) == "ProjectId"){
            value = it->attribute("Value").value();
            m_ids.projectId = atof(value.c_str());
        }
        else if(my_utf8(it->name()) == "ConfigurationId"){
            value = it->attribute("Value").value();
            m_ids.configurationId = atof(value.c_str());
        }
        else if(my_utf8(it->name()) == "LeadTypeId"){
            value = it->attribute("Value").value();
            m_ids.leadTypeId = atof(value.c_str());
        }
        else if(my_utf8(it->name()) == "CoatingId"){
            value = it->attribute("Value").value();
            m_ids.coatingId = atof(value.c_str());
        }
        else if(my_utf8(it->name()) == "EnergizationId"){
            value = it->attribute("Value").value();
            m_ids.energizationId = atof(value.c_str());
        }
        else if(my_utf8(it->name()) == "ConductorTypeId"){
            value = it->attribute("Value").value();
            m_ids.conductorTypeId = atof(value.c_str());
        }
        else if(my_utf8(it->name()) == "CableTypeId"){
            value = it->attribute("Value").value();
            m_ids.cableTypeId = atof(value.c_str());
        }
        else if(my_utf8(it->name()) == "ConductorId"){
            value = it->attribute("Value").value();
            m_ids.conductorId = atof(value.c_str());
        }
        else if(my_utf8(it->name()) == "BuildingConductorId"){
            value = it->attribute("Value").value();
            m_ids.buildingConductorId = atof(value.c_str());
        }
        else if(my_utf8(it->name()) == "BuildingId"){
            value = it->attribute("Value").value();
            m_ids.buildingId = atof(value.c_str());
        }
        else if(my_utf8(it->name()) == "ProfileId"){
            value = it->attribute("Value").value();
            m_ids.profileId = atof(value.c_str());
        }
    }
}

void AppUtils::saveIds(){
    pugi::xml_document doc;

    pugi::xml_node baseNode = doc.append_child("LastIds");

    pugi::xml_node node;
    QString value;

    node = baseNode.append_child("ProjectId");
    value = "P" + QString::number(m_ids.projectId);
    node.append_attribute("Value").set_value(value.toStdString().c_str());

    node = baseNode.append_child("ConfigurationId");
    value = "C" + QString::number(m_ids.configurationId);
    node.append_attribute("Value").set_value(value.toStdString().c_str());

    node = baseNode.append_child("LeadTypeId");
    value = "LT" + QString::number(m_ids.leadTypeId);
    node.append_attribute("Value").set_value(value.toStdString().c_str());

    node = baseNode.append_child("CoatingId");
    value = "CO" + QString::number(m_ids.coatingId);
    node.append_attribute("Value").set_value(value.toStdString().c_str());

    node = baseNode.append_child("EnergizationId");
    value = "E" + QString::number(m_ids.energizationId);
    node.append_attribute("Value").set_value(value.toStdString().c_str());

    node = baseNode.append_child("ConductorTypeId");
    value = "CT" + QString::number(m_ids.conductorTypeId);
    node.append_attribute("Value").set_value(value.toStdString().c_str());

    node = baseNode.append_child("CableTypeId");
    value = "CBT" + QString::number(m_ids.cableTypeId);
    node.append_attribute("Value").set_value(value.toStdString().c_str());

    node = baseNode.append_child("ConductorId");
    value = "CD" + QString::number(m_ids.conductorId);
    node.append_attribute("Value").set_value(value.toStdString().c_str());

    node = baseNode.append_child("BuildingConductorId");
    value = "BCD" + QString::number(m_ids.buildingConductorId);
    node.append_attribute("Value").set_value(value.toStdString().c_str());

    node = baseNode.append_child("BuildingId");
    value = "B" + QString::number(m_ids.buildingId);
    node.append_attribute("Value").set_value(value.toStdString().c_str());

    node = baseNode.append_child("ProfileId");
    value = "PR" + QString::number(m_ids.profileId);
    node.append_attribute("Value").set_value(value.toStdString().c_str());

    QString path = qgetenv("USERNAME").constData();
    path += "_ids.cdi";

    doc.save_file(getXMLPath(path));
}

std::vector<double> AppUtils::drange(double start, double end, double step){
    std::vector<double> range;

    for(double i=start; i<=end; i+=step){
        range.push_back(i);
    }

    return range;
}

std::string AppUtils::getOsName(){
    #ifdef _WIN64
        return "Windows 64-bit";
    #elif _WIN32
        return "Windows 32-bit";
    #elif __unix || __unix__
        return "Unix";
    #elif __APPLE__ || __MACH__
        return "Mac OSX";
    #elif __linux__
        return "Linux";
    #elif __FreeBSD__
        return "FreeBSD";
    #else
        return "Other";
    #endif
}

void AppUtils::readXML(pugi::xml_node toIter, int iteration){
    std::string whitespace = "";

    for(int i=0; i<iteration; i++){
        whitespace += "    ";
    }

    for(pugi::xml_node_iterator it = toIter.children().begin(); it != toIter.children().end(); it++){
        std::cout << whitespace << it->name();

        for(pugi::xml_attribute_iterator ait = it->attributes_begin(); ait != it->attributes_end(); ait++){
            std::cout <<  "(" << ait->name() << " = " << ait->value() << ")";
        }



        if(it->text()){
            std::cout << " Text: " << it->first_child().value() << std::endl;
        }
        else if(it->first_child()){ //has children
            std::cout << std::endl;
            readXML(*it, iteration+1);
        }
        else{
            std::cout << std::endl;
        }

    }

}

const wchar_t* AppUtils::getXMLPath(QString folderPath, QString filename){
    QDir appFolder(folderPath);
    const wchar_t* path = appFolder.absoluteFilePath(filename).toStdWString().c_str();
    return path;
}

const wchar_t* AppUtils::getXMLPath(QString filename){
    QString pathToFolder = qgetenv("APPDATA").constData();
    pathToFolder += "/CDEGS-AID";
    QDir appFolder(pathToFolder);
    const wchar_t* path = appFolder.absoluteFilePath(filename).toStdWString().c_str();
    return path;
}

std::string AppUtils::dbl2str(double d)
{
    size_t len = std::snprintf(0, 0, "%.10f", d);
    std::string s(len+1, 0);
    // technically non-portable, see below
    std::snprintf(&s[0], len+1, "%.10f", d);
    // remove nul terminator
    s.pop_back();
    // remove trailing zeros
    s.erase(s.find_last_not_of('0') + 1, std::string::npos);
    // remove trailing point
    if(s.back() == '.') {
        s.pop_back();
    }
    return s;
}

void AppUtils::append_dbl2str(std::string &s, double d) {
    size_t len = std::snprintf(0, 0, "%.10f", d);
    size_t oldsize = s.size();
    s.resize(oldsize + len + 1);
    // technically non-portable
    std::snprintf(&s[oldsize], len+1, "%.10f", d);
    // remove nul terminator
    s.pop_back();
    // remove trailing zeros
    s.erase(s.find_last_not_of('0') + 1, std::string::npos);
    // remove trailing point
    if(s.back() == '.') {
        s.pop_back();
    }
}

std::string AppUtils::uniqueIdGenerator(std::string type){
    std::string result = "failure";

    if(type == "ProjectId"){
        result = "P";
        append_dbl2str(result, m_ids.projectId+1);
        m_ids.projectId += 1;
    }
    else if(type == "ConfigurationId"){
        result = "C";
        append_dbl2str(result, m_ids.configurationId+1);
        m_ids.configurationId += 1;
    }
    else if(type == "LeadTypeId"){
        result = "LT";
        append_dbl2str(result, m_ids.leadTypeId+1);
        m_ids.leadTypeId += 1;
    }
    else if(type == "CoatingId"){
        result = "CO";
        append_dbl2str(result, m_ids.coatingId+1);
        m_ids.coatingId += 1;
    }
    else if(type == "EnergizationId"){
        result = "E";
        append_dbl2str(result, m_ids.energizationId+1);
        m_ids.energizationId += 1;
    }
    else if(type == "ConductorTypeId"){
        result = "CT";
        append_dbl2str(result, m_ids.conductorTypeId+1);
        m_ids.conductorTypeId += 1;
    }
    else if(type == "CableTypeId"){
        result = "CBT";
        append_dbl2str(result, m_ids.cableTypeId+1);
        m_ids.cableTypeId += 1;
    }
    else if(type == "ConductorId"){
        result = "CD";
        append_dbl2str(result, m_ids.conductorId+1);
        m_ids.conductorId += 1;
    }
    else if(type == "BuildingConductorId"){
        result = "BCD";
        append_dbl2str(result, m_ids.buildingConductorId+1);
        m_ids.buildingConductorId += 1;
    }
    else if(type == "BuildingId"){
        result = "B";
        append_dbl2str(result, m_ids.buildingId+1);
        m_ids.buildingId += 1;
    }
    else if(type == "ProfileId"){
        result = "PR";
        append_dbl2str(result, m_ids.profileId+1);
        m_ids.profileId += 1;
    }

    return result;
}

void AppUtils::saveProject(const Project &project){
    pugi::xml_document doc;

    pugi::xml_node projectNode = doc.append_child("Project");

    pugi::xml_node node;

    //Project node-------------------------------------------------------

    //Project attribute
    projectNode.append_attribute("Id").set_value(project.getId().c_str());

    //AbsPath node
    node = projectNode.append_child("AbsPath");
    node.append_attribute("Os").set_value(getOsName().c_str());
    node.append_attribute("Value").set_value(project.getAbsPath().c_str());

    //RelPath node
    node = projectNode.append_child("RelPath");
    node.append_attribute("Os").set_value(getOsName().c_str());
    node.append_attribute("Value").set_value(project.getRelPath().c_str());

    //DefaultConfig node
    node = projectNode.append_child("DefaultConfig");
    if(project.getDefaultConfig() != nullptr){
        node.append_attribute("Value").set_value(project.getDefaultConfig()->getId().c_str());
    }
    else{
        node.append_attribute("Value").set_value("NULL");
    }

    //LastConfig node
    node = projectNode.append_child("LastConfig");
    if(project.getDefaultConfig() != nullptr){
        node.append_attribute("Value").set_value(project.getLastConfig()->getId().c_str());
    }
    else{
        node.append_attribute("Value").set_value("NULL");
    }

    //DefaultWindow node
    node = projectNode.append_child("DefaultWindow");
    node.append_attribute("Value").set_value(project.getDefaultWindow().c_str());

    //LastWindow node
    node = projectNode.append_child("LastWindow");
    node.append_attribute("Value").set_value(project.getLastWindow().c_str());

    //Metadata node------------------------------------------------------------
    pugi::xml_node metadataNode = projectNode.append_child("Metadata");

    //Name node
    node = metadataNode.append_child("Name");
    node.append_child(pugi::node_pcdata).set_value(project.getMetadata().name.c_str());

    //Date node
    node = metadataNode.append_child("Date");
    node.append_child(pugi::node_pcdata).set_value(project.getMetadata().date.toString().toStdString().c_str());

    //Author node
    node = metadataNode.append_child("Author");
    node.append_child(pugi::node_pcdata).set_value(project.getMetadata().author.c_str());

    //Description node
    node = metadataNode.append_child("Description");
    node.append_child(pugi::node_pcdata).set_value(project.getMetadata().description.toPlainText().toStdString().c_str());

    //Metadata node end---------------------------------------------------------

    //ProjectSettings node------------------------------------------------------------
    pugi::xml_node projectSettingsNode = projectNode.append_child("ProjectSettings");

    //Set1 node
    node = projectSettingsNode.append_child("Set1");
    node.append_child(pugi::node_pcdata).set_value(project.getSettings().set1.c_str());

    //Set2 node
    node = projectSettingsNode.append_child("Set2");
    node.append_child(pugi::node_pcdata).set_value(project.getSettings().set2.c_str());

    //Set3 node
    node = projectSettingsNode.append_child("Set3");
    node.append_child(pugi::node_pcdata).set_value(project.getSettings().set3.c_str());

    //Set4 node
    node = projectSettingsNode.append_child("Set4");
    node.append_child(pugi::node_pcdata).set_value(project.getSettings().set4.c_str());

    //ProjectSettings node end---------------------------------------------------------

    //Project node end-----------------------------------------------------------------

    //Configurations
    pugi::xml_node configNode = doc.append_child("Configurations");

    for(std::vector<Configuration*>::iterator it=project.getConfigurations().begin(); it != project.getConfigurations().end(); it++ ){
        saveConfiguration(*it, configNode);
    }

    QString folder = "";
    QString path = "test.cdp";

    doc.save_file(getXMLPath(folder, path));

}

void AppUtils::saveConfiguration(Configuration* const config, pugi::xml_node &parent){

}

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

inline const char* AppUtils::BoolToString(const bool& b) const{
  return b ? "True" : "False";
}

void AppUtils::readXML(const pugi::xml_node& toIter, int iteration){
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

const wchar_t* AppUtils::getXMLPath(const QString& folderPath, const QString& filename){
    QDir appFolder(folderPath);
    const wchar_t* path = appFolder.absoluteFilePath(filename).toStdWString().c_str();
    return path;
}

const wchar_t* AppUtils::getXMLPath(const QString& filename){
    QString pathToFolder = qgetenv("APPDATA").constData();
    pathToFolder += "/CDEGS-AID";
    QDir appFolder(pathToFolder);
    const wchar_t* path = appFolder.absoluteFilePath(filename).toStdWString().c_str();
    return path;
}

std::string AppUtils::getPath(const QString& folderPath, const QString& filename){
    QDir appFolder(folderPath);
    std::string path = appFolder.absoluteFilePath(filename).toStdString();
    return path;
}

std::string AppUtils::getPath(const QString& filename){
    QString pathToFolder = qgetenv("APPDATA").constData();
    pathToFolder += "/CDEGS-AID";
    QDir appFolder(pathToFolder);
    std::string path = appFolder.absoluteFilePath(filename).toStdString();
    return path;
}

void AppUtils::setDefaultConfig(){
    if(0 == access(getPath("default_values.cdp").c_str(), 0)){ //Exists
        loadDefaultConfig();
    }
    else{ //Does not exist
        generateDefaultConfig();
        loadDefaultConfig();
    }
}

void AppUtils::loadDefaultConfig(){
    m_defaultConfig = new Configuration();

    pugi::xml_document doc;
    if (!doc.load_file(AppUtils::getInstance().getXMLPath("default_values.cdp"))){
        std::cout << "Failure" << std::endl;
    }

    pugi::xml_node node = doc.first_child().first_child();

    m_defaultConfig->setId(node.first_attribute().value());

    m_defaultConfig->setIdentifier(node.child("Identifier").first_attribute().value());

    m_defaultConfig->setUnits(node.child("Units").first_attribute().value());

    m_defaultConfig->setFrequency(node.child("Frequency").first_attribute().value());

    for(pugi::xml_node_iterator it = node.child("LeadTypes").children().begin(); it != node.child("LeadTypes").children().end(); it++){
        LeadType* lt = new LeadType(it->attribute("Name").value());
        lt->setId(it->attribute("Id").value());
        lt->setLocked(true);
        m_defaultConfig->addLeadType(lt);
    }

    for(pugi::xml_node_iterator it = node.child("Coatings").children().begin(); it != node.child("Coatings").children().end(); it++){
        Coating* co = new Coating(it->attribute("Name").value());
        co->setId(it->attribute("Id").value());
        co->setLocked(true);
        m_defaultConfig->addCoating(co);
    }

    for(pugi::xml_node_iterator it = node.child("Energizations").children().begin(); it != node.child("Energizations").children().end(); it++){
        Energization* en = new Energization(it->attribute("Identification").value(), it->attribute("Type").value(), it->attribute("Frequency").value(), it->attribute("Magnitude").as_double(), it->attribute("Angle").as_double());
        en->setId(it->attribute("Id").value());
        en->setLocked(true);
        m_defaultConfig->addEnergization(en);
    }

    for(pugi::xml_node_iterator it = node.child("Tolerances").children().begin(); it != node.child("Tolerances").children().end(); it++){
        m_defaultConfig->addTolerance(it->attribute("Value").as_double());
    }

    for(pugi::xml_node_iterator it = node.child("ConductorTypes").children().begin(); it != node.child("ConductorTypes").children().end(); it++){
        ConductorType* ct = new ConductorType(it->attribute("Type").value(), it->attribute("Name").value(), it->attribute("Resistivity").as_double(), it->attribute("Permeability").as_double());
        ct->setId(it->attribute("Id").value());
        ct->setLocked(true);
        m_defaultConfig->addConductorType(ct);
    }

    for(pugi::xml_node_iterator it = node.child("CableTypes").children().begin(); it != node.child("CableTypes").children().end(); it++){
        CableType* cbt = new CableType(it->attribute("Name").value());
        cbt->setId(it->attribute("Id").value());
        cbt->setLocked(true);
        m_defaultConfig->addCableType(cbt);
    }

    m_defaultConfig->setComputations().GPR = node.child("Computations").child("GPR").first_attribute().as_bool();
    m_defaultConfig->setComputations().POTENTIAL_SCALAR = node.child("Computations").child("POTENTIAL-SCALAR").first_attribute().as_bool();
    m_defaultConfig->setComputations().ELECTRIC = node.child("Computations").child("ELECTRIC").first_attribute().as_bool();
    m_defaultConfig->setComputations().MAGNETIC = node.child("Computations").child("MAGNETIC").first_attribute().as_bool();
    m_defaultConfig->setComputations().VECTOR_POTENTIAL = node.child("Computations").child("VECTOR-POTENTIAL").first_attribute().as_bool();
    m_defaultConfig->setComputations().GRADIENT_SCALAR = node.child("Computations").child("GRADIENT-SCALAR ").first_attribute().as_bool();

}

void AppUtils::generateDefaultConfig(){
    pugi::xml_document doc;

    pugi::xml_node defaultNode = doc.append_child("Default");
    pugi::xml_node configNode = defaultNode.append_child("Configuration");

    pugi::xml_node node;

    //Configuration node-------------------------------------------------------

    //Configuration attribute
    configNode.append_attribute("Id").set_value("C0");

    //Identifier node
    node = configNode.append_child("Identifier");
    node.append_attribute("Value").set_value("Default");

    //Units node
    node = configNode.append_child("Units");
    node.append_attribute("Value").set_value("Metric");

    //Frequency node
    node = configNode.append_child("Frequency");
    node.append_attribute("Value").set_value("AC");

    //LeadTypes node-----------------------------------------------------------
    pugi::xml_node leadTypesNode = configNode.append_child("LeadTypes");

    node = leadTypesNode.append_child("LeadType");
    node.append_attribute("Id").set_value("LT0");
    node.append_attribute("Name").set_value("Default Impedance");
    node.append_attribute("Locked").set_value("1");

    //LeadTypes end------------------------------------------------------------

    //Coatings node-----------------------------------------------------------
    pugi::xml_node coatingsNode = configNode.append_child("Coatings");

    node = coatingsNode.append_child("Coating");
    node.append_attribute("Id").set_value("CO0");
    node.append_attribute("Name").set_value("Default Coating");
    node.append_attribute("Locked").set_value("1");

    //Coatings end------------------------------------------------------------

    //Energizations node-----------------------------------------------------------
    pugi::xml_node energizationsNode = configNode.append_child("Energizations");

    node = energizationsNode.append_child("Energization");
    node.append_attribute("Id").set_value("E1");
    node.append_attribute("Identification").set_value("GND");
    node.append_attribute("Type").set_value("GPR-Potential");
    node.append_attribute("Frequency").set_value("Both");
    node.append_attribute("Angle").set_value("0");
    node.append_attribute("Magnitude").set_value("0.0");
    node.append_attribute("Locked").set_value("1");

    node = energizationsNode.append_child("Energization");
    node.append_attribute("Id").set_value("E2");
    node.append_attribute("Identification").set_value("PhaseA");
    node.append_attribute("Type").set_value("GPR-Potential");
    node.append_attribute("Frequency").set_value("AC");
    node.append_attribute("Angle").set_value("0");
    node.append_attribute("Magnitude").set_value("441700.0");
    node.append_attribute("Locked").set_value("1");

    node = energizationsNode.append_child("Energization");
    node.append_attribute("Id").set_value("E3");
    node.append_attribute("Identification").set_value("PhaseB");
    node.append_attribute("Type").set_value("GPR-Potential");
    node.append_attribute("Frequency").set_value("AC");
    node.append_attribute("Angle").set_value("-120");
    node.append_attribute("Magnitude").set_value("441700.0");
    node.append_attribute("Locked").set_value("1");

    node = energizationsNode.append_child("Energization");
    node.append_attribute("Id").set_value("E4");
    node.append_attribute("Identification").set_value("PhaseC");
    node.append_attribute("Type").set_value("GPR-Potential");
    node.append_attribute("Frequency").set_value("AC");
    node.append_attribute("Angle").set_value("120");
    node.append_attribute("Magnitude").set_value("441700.0");
    node.append_attribute("Locked").set_value("1");

    node = energizationsNode.append_child("Energization");
    node.append_attribute("Id").set_value("E5");
    node.append_attribute("Identification").set_value("PoleA");
    node.append_attribute("Type").set_value("GPR-Potential");
    node.append_attribute("Frequency").set_value("DC");
    node.append_attribute("Angle").set_value("0");
    node.append_attribute("Magnitude").set_value("441700000.0");
    node.append_attribute("Locked").set_value("1");

    node = energizationsNode.append_child("Energization");
    node.append_attribute("Id").set_value("E6");
    node.append_attribute("Identification").set_value("PoleB");
    node.append_attribute("Type").set_value("GPR-Potential");
    node.append_attribute("Frequency").set_value("DC");
    node.append_attribute("Angle").set_value("0");
    node.append_attribute("Magnitude").set_value("441700000.0");
    node.append_attribute("Locked").set_value("1");

    //Energizations end------------------------------------------------------------

    //Tolerances node-----------------------------------------------------------
    pugi::xml_node tolerancesNode = configNode.append_child("Tolerances");

    node = tolerancesNode.append_child("Tolerance");
    node.append_attribute("Value").set_value("0.001");

    node = tolerancesNode.append_child("Tolerance");
    node.append_attribute("Value").set_value("1.0");

    node = tolerancesNode.append_child("Tolerance");
    node.append_attribute("Value").set_value("0.005");

    node = tolerancesNode.append_child("Tolerance");
    node.append_attribute("Value").set_value("0.00005");

    node = tolerancesNode.append_child("Tolerance");
    node.append_attribute("Value").set_value("0.001");

    node = tolerancesNode.append_child("Tolerance");
    node.append_attribute("Value").set_value("0.0");

    node = tolerancesNode.append_child("Tolerance");
    node.append_attribute("Value").set_value("0.0");

    node = tolerancesNode.append_child("Tolerance");
    node.append_attribute("Value").set_value("0.0");

    node = tolerancesNode.append_child("Tolerance");
    node.append_attribute("Value").set_value("0.5");

    //Tolerances end------------------------------------------------------------

    //ConductorTypes node-----------------------------------------------------------
    pugi::xml_node conductorTypesNode = configNode.append_child("ConductorTypes");

    node = conductorTypesNode.append_child("ConductorType");
    node.append_attribute("Id").set_value("CT1");
    node.append_attribute("Type").set_value("Plastic");
    node.append_attribute("Name").set_value("Plastic");
    node.append_attribute("Resistivity").set_value("0.0");
    node.append_attribute("Permeability").set_value("1.0");
    node.append_attribute("Locked").set_value("1");

    node = conductorTypesNode.append_child("ConductorType");
    node.append_attribute("Id").set_value("CT2");
    node.append_attribute("Type").set_value("Default");
    node.append_attribute("Name").set_value("Default Conductor");
    node.append_attribute("Resistivity").set_value("1.0");
    node.append_attribute("Permeability").set_value("1.0");
    node.append_attribute("Locked").set_value("1");

    node = conductorTypesNode.append_child("ConductorType");
    node.append_attribute("Id").set_value("CT3");
    node.append_attribute("Type").set_value("Computed");
    node.append_attribute("Name").set_value("Aluminium");
    node.append_attribute("Resistivity").set_value("1.64");
    node.append_attribute("Permeability").set_value("1.0");
    node.append_attribute("Locked").set_value("1");

    node = conductorTypesNode.append_child("ConductorType");
    node.append_attribute("Id").set_value("CT4");
    node.append_attribute("Type").set_value("Computed");
    node.append_attribute("Name").set_value("Steel");
    node.append_attribute("Resistivity").set_value("12.0");
    node.append_attribute("Permeability").set_value("250.0");
    node.append_attribute("Locked").set_value("1");

    //ConductorTypes end------------------------------------------------------------

    //CableTypes node-----------------------------------------------------------
    pugi::xml_node cableTypesNode = configNode.append_child("CableTypes");

    node = cableTypesNode.append_child("CableType");
    node.append_attribute("Id").set_value("CBT0");
    node.append_attribute("Name").set_value("(Not a cable)");
    node.append_attribute("Locked").set_value("1");

    //CableTypes end------------------------------------------------------------

    node = configNode.append_child("Conductors");
    node = configNode.append_child("BuildingConductors");
    node = configNode.append_child("Buildings");

    //Computations node----------------------------------------------------------------
    pugi::xml_node computationsNode = configNode.append_child("Computations");

    node = computationsNode.append_child("GPR");
    node.append_attribute("Value").set_value("False");

    node = computationsNode.append_child("POTENTIAL-SCALAR");
    node.append_attribute("Value").set_value("False");

    node = computationsNode.append_child("ELECTRIC");
    node.append_attribute("Value").set_value("True");

    node = computationsNode.append_child("MAGNETIC");
    node.append_attribute("Value").set_value("False");

    node = computationsNode.append_child("VECTOR-POTENTIAL");
    node.append_attribute("Value").set_value("False");

    node = computationsNode.append_child("GRADIENT-SCALAR");
    node.append_attribute("Value").set_value("False");

    //Computations end-----------------------------------------------------------------

    node = configNode.append_child("Profiles");

    QString filename = "default_values.cdp";

    doc.save_file(getXMLPath(filename));
}

Configuration const* AppUtils::getDefaultConfig() const{
    return m_defaultConfig;
}

Configuration* AppUtils::loadConfig(pugi::xml_node configNode) const{
    Configuration* config = new Configuration();

    config->setId(configNode.first_attribute().value());

    config->setIdentifier(configNode.child("Identifier").first_attribute().value());

    config->setUnits(configNode.child("Units").first_attribute().value());

    config->setFrequency(configNode.child("Frequency").first_attribute().value());

    for(pugi::xml_node_iterator it = configNode.child("LeadTypes").children().begin(); it != configNode.child("LeadTypes").children().end(); it++){
        LeadType* lt = new LeadType(it->attribute("Name").value());
        lt->setId(it->attribute("Id").value());
        lt->setLocked(it->attribute("Locked").as_bool());
        config->addLeadType(lt);
    }

    for(pugi::xml_node_iterator it = configNode.child("Coatings").children().begin(); it != configNode.child("Coatings").children().end(); it++){
        Coating* co = new Coating(it->attribute("Name").value());
        co->setId(it->attribute("Id").value());
        co->setLocked(it->attribute("Locked").as_bool());
        config->addCoating(co);
    }

    for(pugi::xml_node_iterator it = configNode.child("Energizations").children().begin(); it != configNode.child("Energizations").children().end(); it++){
        Energization* en = new Energization(it->attribute("Identification").value(), it->attribute("Type").value(), it->attribute("Frequency").value(), it->attribute("Magnitude").as_double(), it->attribute("Angle").as_double());
        en->setId(it->attribute("Id").value());
        en->setLocked(it->attribute("Locked").as_bool());
        config->addEnergization(en);
    }

    for(pugi::xml_node_iterator it = configNode.child("Tolerances").children().begin(); it != configNode.child("Tolerances").children().end(); it++){
        config->addTolerance(it->attribute("Value").as_double());
    }

    for(pugi::xml_node_iterator it = configNode.child("ConductorTypes").children().begin(); it != configNode.child("ConductorTypes").children().end(); it++){
        ConductorType* ct = new ConductorType(it->attribute("Type").value(), it->attribute("Name").value(), it->attribute("Resistivity").as_double(), it->attribute("Permeability").as_double());
        ct->setId(it->attribute("Id").value());
        ct->setLocked(it->attribute("Locked").as_bool());
        config->addConductorType(ct);
    }

    for(pugi::xml_node_iterator it = configNode.child("CableTypes").children().begin(); it != configNode.child("CableTypes").children().end(); it++){
        CableType* cbt = new CableType(it->attribute("Name").value());
        cbt->setId(it->attribute("Id").value());
        cbt->setLocked(it->attribute("Locked").as_bool());
        config->addCableType(cbt);
    }



    for(pugi::xml_node_iterator it = configNode.child("Conductors").children().begin(); it != configNode.child("Conductors").children().end(); it++){
        Conductor* cd = new Conductor();
        std::string key;
        cd->setId(it->attribute("Id").value());

        key = it->child("LeadTypeId").first_attribute().value();
        if(key != "") cd->setLeadType(config->getLeadTypes().at(key));

        key = it->child("CoatingId").first_attribute().value();
        if(key != "") cd->setCoating(config->getCoatings().at(key));

        key = it->child("ConductorTypeId").first_attribute().value();
        if(key != "") cd->setConductorType(config->getConductorTypes().at(key));

        key = it->child("EnergizationId").first_attribute().value();
        if(key != "") cd->setEnergization(config->getEnergizations().at(key));

        key = it->child("CableTypeId").first_attribute().value();
        if(key != "") cd->setCableType(config->getCableTypes().at(key));

        cd->setRadius(it->child("Radius").first_attribute().as_double());
        coords start, end;
        start.x = it->child("CoordsStart").attribute("X").as_double();
        start.y = it->child("CoordsStart").attribute("Y").as_double();
        start.z = it->child("CoordsStart").attribute("Z").as_double();
        end.x = it->child("CoordsEnd").attribute("X").as_double();
        end.y = it->child("CoordsEnd").attribute("Y").as_double();
        end.z = it->child("CoordsEnd").attribute("Z").as_double();
        cd->setCoords(start, end);
        config->addConductor(cd);
    }

    for(pugi::xml_node_iterator it = configNode.child("BuildingConductors").children().begin(); it != configNode.child("BuildingConductors").children().end(); it++){
        Conductor* cd = new Conductor();
        cd->setId(it->attribute("Id").value());
        cd->setLeadType(config->getLeadTypes().at(it->child("LeadTypeId").first_attribute().value()));
        cd->setCoating(config->getCoatings().at(it->child("CoatingId").first_attribute().value()));
        cd->setConductorType(config->getConductorTypes().at(it->child("ConductorTypeId").first_attribute().value()));
        cd->setEnergization(config->getEnergizations().at(it->child("EnergizationId").first_attribute().value()));
        cd->setCableType(config->getCableTypes().at(it->child("CableTypeId").first_attribute().value()));
        cd->setRadius(it->child("Radius").first_attribute().as_double());
        coords start, end;
        start.x = it->child("CoordsStart").attribute("X").as_double();
        start.y = it->child("CoordsStart").attribute("Y").as_double();
        start.z = it->child("CoordsStart").attribute("Z").as_double();
        end.x = it->child("CoordsEnd").attribute("X").as_double();
        end.y = it->child("CoordsEnd").attribute("Y").as_double();
        end.z = it->child("CoordsEnd").attribute("Z").as_double();
        cd->setCoords(start, end);
        config->addBuildingConductor(cd);
    }

    for(pugi::xml_node_iterator it = configNode.child("Buildings").children().begin(); it != configNode.child("Buildings").children().end(); it++){
        Building* b = new Building(it->child("Faces").attribute("Value").as_int(), it->child("Height").attribute("Value").as_double(), it->child("Distance").attribute("Min").as_double(), it->child("Distance").attribute("Max").as_double(), it->child("Step").attribute("Value").as_double());
        b->setId(it->attribute("Id").value());
        config->addBuilding(b);
    }

    config->setComputations().GPR = configNode.child("Computations").child("GPR").first_attribute().as_bool();
    config->setComputations().POTENTIAL_SCALAR = configNode.child("Computations").child("POTENTIAL-SCALAR").first_attribute().as_bool();
    config->setComputations().ELECTRIC = configNode.child("Computations").child("ELECTRIC").first_attribute().as_bool();
    config->setComputations().MAGNETIC = configNode.child("Computations").child("MAGNETIC").first_attribute().as_bool();
    config->setComputations().VECTOR_POTENTIAL = configNode.child("Computations").child("VECTOR-POTENTIAL").first_attribute().as_bool();
    config->setComputations().GRADIENT_SCALAR = configNode.child("Computations").child("GRADIENT-SCALAR ").first_attribute().as_bool();

    for(pugi::xml_node_iterator it = configNode.child("Profiles").children().begin(); it != configNode.child("Profiles").children().end(); it++){
        profile* p = new profile;
        p->id = it->attribute("Id").value();
        p->xCoords.start = it->child("XCoords").attribute("Start").as_double();
        p->xCoords.end = it->child("XCoords").attribute("End").as_double();
        p->xCoords.step = it->child("XCoords").attribute("Step").as_double();
        p->yCoords.start = it->child("YCoords").attribute("Start").as_double();
        p->yCoords.end = it->child("YCoords").attribute("End").as_double();
        p->yCoords.step = it->child("YCoords").attribute("Step").as_double();
        p->NLine = it->child("NLine").attribute("Value").as_double();
        p->MCol = it->child("MCol").attribute("Value").as_double();
        config->addProfile(p);
    }

    return config;
}

Project* AppUtils::loadProject(const std::string& path, const std::string& filename){
    Project* project = new Project();

    pugi::xml_document doc;

    if(path != ""){
        doc.load_file(getXMLPath(QString::fromStdString(path), QString::fromStdString(filename)));
    }
    else{
        doc.load_file(getXMLPath(QString::fromStdString(filename)));
    }


    pugi::xml_node node = doc.first_child();

    project->setId(node.attribute("Id").value());

    project->setAbsPath(node.child("AbsPath").attribute("Value").value());

    project->setRelPath(node.child("RelPath").attribute("Value").value());

    project->setFileName(node.child("FileName").attribute("Value").value());

    project->setDefaultWindow(node.child("DefaultWindow").attribute("Value").value());

    project->setLastWindow(node.child("LastWindow").attribute("Value").value());

    project->setMetaAuthor(node.child("Metadata").child("Author").text().as_string());

    project->setMetaName(node.child("Metadata").child("Name").text().as_string());

    project->setMetaDescription(node.child("Metadata").child("Description").text().as_string());

    project->setMetaDate(QDate::fromString(node.child("Metadata").child("Date").text().as_string()));

    project->setProjSet1(node.child("ProjectSettings").child("Set1").text().as_string());

    project->setProjSet2(node.child("ProjectSettings").child("Set2").text().as_string());

    project->setProjSet3(node.child("ProjectSettings").child("Set3").text().as_string());

    project->setProjSet4(node.child("ProjectSettings").child("Set4").text().as_string());

    node = doc.last_child();

    for(pugi::xml_node_iterator it = node.children().begin(); it != node.children().end(); it++){
        project->addConfiguration(loadConfig(*it));
    }

    std::string key;

    node = doc.first_child();

    key = node.child("DefaultConfig").first_attribute().value();
    if(key != "") project->setDefaultConfig(project->getConfigurations().at(key));

    key = node.child("LastConfig").first_attribute().value();
    if(key != "") project->setLastConfig(project->getConfigurations().at(key));

    return project;
}

Project* AppUtils::loadProject(const wchar_t* fullPath){
    Project* project = new Project();

    pugi::xml_document doc;

    doc.load_file(fullPath);

    pugi::xml_node node = doc.first_child();

    project->setId(node.attribute("Id").value());

    project->setAbsPath(node.child("AbsPath").attribute("Value").value());

    project->setRelPath(node.child("RelPath").attribute("Value").value());

    project->setFileName(node.child("FileName").attribute("Value").value());

    project->setDefaultWindow(node.child("DefaultWindow").attribute("Value").value());

    project->setLastWindow(node.child("LastWindow").attribute("Value").value());

    project->setMetaAuthor(node.child("Metadata").child("Author").text().as_string());

    project->setMetaName(node.child("Metadata").child("Name").text().as_string());

    project->setMetaDescription(node.child("Metadata").child("Description").text().as_string());

    project->setMetaDate(QDate::fromString(node.child("Metadata").child("Date").text().as_string()));

    project->setProjSet1(node.child("ProjectSettings").child("Set1").text().as_string());

    project->setProjSet2(node.child("ProjectSettings").child("Set2").text().as_string());

    project->setProjSet3(node.child("ProjectSettings").child("Set3").text().as_string());

    project->setProjSet4(node.child("ProjectSettings").child("Set4").text().as_string());

    node = doc.last_child();

    for(pugi::xml_node_iterator it = node.children().begin(); it != node.children().end(); it++){
        project->addConfiguration(loadConfig(*it));
    }

    std::string key;

    node = doc.first_child();

    key = node.child("DefaultConfig").first_attribute().value();
    if(key != "") project->setDefaultConfig(project->getConfigurations().at(key));

    key = node.child("LastConfig").first_attribute().value();
    if(key != "") project->setLastConfig(project->getConfigurations().at(key));

    return project;
}

double AppUtils::radians(const double& d) {
return d * pi() / 180;
}

double AppUtils::degrees(const double& r) {
return r * 180/ pi();
}

std::string AppUtils::stringToUpper(std::string strToConvert){
    std::transform(strToConvert.begin(), strToConvert.end(), strToConvert.begin(), ::toupper);

    return strToConvert;
}

void AppUtils::exportConfiguration(const Configuration* config, const std::string& fullPath){
    std::ofstream configFile;
    std::string tolerances = "";
    std::unordered_map<std::string, int> enerPos;
    std::unordered_map<std::string, int> cTypePos;
    int phaseAIter = 0, phaseBIter = 0, phaseCIter = 0, poleAIter = 0, poleBIter = 0, GNDIter = 0;

    for(auto& i_cond : config->getConductors()){
        enerPos.emplace(i_cond.second->getEnergization()->getId(), enerPos.size());
        cTypePos.emplace(i_cond.second->getConductorType()->getId(), cTypePos.size());
    }

    for(auto& i_cond : config->getBuildingConductors()){
        enerPos.emplace(i_cond.second->getEnergization()->getId(), enerPos.size());
        cTypePos.emplace(i_cond.second->getConductorType()->getId(), cTypePos.size());
    }

    configFile.open(fullPath);
    configFile << "HIFREQ\n";
    configFile << "OPTIONS\n";
    configFile << "  RUN-IDENTIFI, " + stringToUpper(config->getIdentifier()) + "\n";
    configFile << "  UNITS, " + stringToUpper(config->getUnits()) + "\n";
    configFile << "  PRINOUT, DETAILED\n";
    configFile << "  SYSTEM\n";
    configFile << "    TOLERANCE,";

    for(double tolerance : config->getTolerances()){
        tolerances.append(dbl2str(tolerance)).append(",");
    }
    tolerances.pop_back();

    configFile << tolerances << "\n";

    for(auto& i_ener : enerPos){
        configFile << "    ENERGIZATION, " << stringToUpper(config->getEnergizations().at(i_ener.first)->getType()) << "," << dbl2str(config->getEnergizations().at(i_ener.first)->getMagnitude()) << "," << dbl2str(config->getEnergizations().at(i_ener.first)->getAngle() * 3600) << ",,,,,," << config->getEnergizations().at(i_ener.first)->getIdentification();

        if(config->getEnergizations().at(i_ener.first)->getIdentification() == "PhaseA"){
            configFile << phaseAIter << "\n";
            phaseAIter++;
        }
        else if(config->getEnergizations().at(i_ener.first)->getIdentification() == "PhaseB"){
            configFile << phaseBIter << "\n";
            phaseBIter++;
        }
        else if(config->getEnergizations().at(i_ener.first)->getIdentification() == "PhaseC"){
            configFile << phaseCIter << "\n";
            phaseCIter++;
        }
        else if(config->getEnergizations().at(i_ener.first)->getIdentification() == "PoleA"){
            configFile << poleAIter << "\n";
            poleAIter++;
        }
        else if(config->getEnergizations().at(i_ener.first)->getIdentification() == "PoleB"){
            configFile << poleBIter << "\n";
            poleBIter++;
        }
        else if(config->getEnergizations().at(i_ener.first)->getIdentification() == "GND"){
            configFile << GNDIter << "\n";
            GNDIter++;
        }
    }

    configFile << "    CHARACTERISTICS\n";

    for(auto& i_cType : cTypePos){
        configFile << "      CONDUCTOR-TYPE," << config->getConductorTypes().at(i_cType.first)->getType() << "," << dbl2str(config->getConductorTypes().at(i_cType.first)->getResistivity()) << "," << dbl2str(config->getConductorTypes().at(i_cType.first)->getPermeability()) << ",,,,,,," << config->getConductorTypes().at(i_cType.first)->getName() << "\n";
    }

    configFile << "\n";
    configFile << "    SUBDIVISION,YES,\n";
    configFile << "    NETWORK\n";
    configFile << "      MAIN-GROUND\n";
    configFile << "\n";

    for(auto& i_cond : config->getConductors()){
        configFile << "      CONDUCTOR, 0, " << cTypePos.at(i_cond.second->getConductorType()->getId()) << ", 0, " << enerPos.at(i_cond.second->getEnergization()->getId()) << "," << dbl2str(i_cond.second->getStartCoords().x) << "," << dbl2str(i_cond.second->getStartCoords().y) << "," << dbl2str(i_cond.second->getStartCoords().z) << "," << dbl2str(i_cond.second->getEndCoords().x) << "," << dbl2str(i_cond.second->getEndCoords().y) << "," << dbl2str(i_cond.second->getEndCoords().z) << "," << dbl2str(i_cond.second->getRadius()) << ",1,0\n";
    }

    configFile << "\n\n";
    configFile << "COMPUTATIONS\n";
    configFile << "  DETERMINE\n";
    configFile << "    GPR, ";
    if(config->getComputations().GPR){
        configFile << "ON\n";
    }
    else{
        configFile << "OFF\n";
    }
    configFile << "    POTENTIAL-SCALAR, ";
    if(config->getComputations().POTENTIAL_SCALAR){
        configFile << "ON\n";
    }
    else{
        configFile << "OFF\n";
    }
    configFile << "    ELECTRIC, ";
    if(config->getComputations().ELECTRIC){
        configFile << "ON\n";
    }
    else{
        configFile << "OFF\n";
    }
    configFile << "    MAGNETIC, ";
    if(config->getComputations().MAGNETIC){
        configFile << "ON\n";
    }
    else{
        configFile << "OFF\n";
    }
    configFile << "    VECTOR-POTENTIAL, ";
    if(config->getComputations().VECTOR_POTENTIAL){
        configFile << "ON\n";
    }
    else{
        configFile << "OFF\n";
    }
    configFile << "    GRADIENT-SCALAR, ";
    if(config->getComputations().GRADIENT_SCALAR){
        configFile << "ON\n";
    }
    else{
        configFile << "OFF\n";
    }

    configFile << "  FREQUENCY,60.,\n";
    configFile << "  OBSERVATION\n";

    for(auto& i_pro : config->getProfiles()){
        configFile << "    PROFILE, " << dbl2str(i_pro.second->NLine) << ",0," << dbl2str(i_pro.second->xCoords.start) << "," << dbl2str(i_pro.second->yCoords.start) << ",0,0," << dbl2str(i_pro.second->yCoords.step) << ",0\n";
        configFile << "      SURFACE, " << dbl2str(i_pro.second->MCol) << ",0," << dbl2str(i_pro.second->xCoords.step) << ",0,0\n";
    }

    configFile << "\n";
    configFile << "ENDPROGRAM";

    configFile.close();
}

std::string AppUtils::dbl2str(const double& d)
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
        s.append("0");
    }
    return s;
}

void AppUtils::append_dbl2str(std::string &s, const double& d) {
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

std::string AppUtils::uniqueIdGenerator(const std::string& type){
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

void AppUtils::saveProject(const Project &project, const std::string& path, const std::string& filename){
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
    if(project.getDefaultConfig() != NULL){
        node.append_attribute("Value").set_value(project.getDefaultConfig()->getId().c_str());
    }

    //LastConfig node
    node = projectNode.append_child("LastConfig");
    if(project.getLastConfig() != NULL){
        node.append_attribute("Value").set_value(project.getLastConfig()->getId().c_str());
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

    for(auto& config : project.getConfigurations()){
        saveConfiguration(config.second, configNode);
    }

    if(path != ""){
        doc.save_file(getXMLPath(QString::fromStdString(path), QString::fromStdString(filename)));
    }
    else{
        doc.save_file(getXMLPath(QString::fromStdString(filename)));
    }

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

    //FileName node
    node = projectNode.append_child("FileName");
    node.append_attribute("Value").set_value(project.getFileName().c_str());

    //DefaultConfig node
    node = projectNode.append_child("DefaultConfig");
    if(project.getDefaultConfig() != NULL){
        node.append_attribute("Value").set_value(project.getDefaultConfig()->getId().c_str());
    }

    //LastConfig node
    node = projectNode.append_child("LastConfig");
    if(project.getLastConfig() != NULL){
        node.append_attribute("Value").set_value(project.getLastConfig()->getId().c_str());
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

    for(auto& config : project.getConfigurations()){
        saveConfiguration(config.second, configNode);
    }

    doc.save_file(getXMLPath(QString::fromStdString(project.getAbsPath()), QString::fromStdString(project.getFileName())));

}

void AppUtils::saveConfiguration(const Configuration* config, pugi::xml_node &parent){
    pugi::xml_node configNode = parent.append_child("Configuration");

    pugi::xml_node node;

    //Configuration node-------------------------------------------------------

    //Configuration attribute
    configNode.append_attribute("Id").set_value(config->getId().c_str());

    //Identifier node
    node = configNode.append_child("Identifier");
    node.append_attribute("Value").set_value(config->getIdentifier().c_str());

    //Units node
    node = configNode.append_child("Units");
    node.append_attribute("Value").set_value(config->getUnits().c_str());

    //Frequency node
    node = configNode.append_child("Frequency");
    node.append_attribute("Value").set_value(config->getFrequency().c_str());

    //LeadTypes node-----------------------------------------------------------
    pugi::xml_node leadTypesNode = configNode.append_child("LeadTypes");

    for(auto& i_leadType : config->getLeadTypes()){
        node = leadTypesNode.append_child("LeadType");
        node.append_attribute("Id").set_value(i_leadType.first.c_str());
        node.append_attribute("Name").set_value(i_leadType.second->getName().c_str());
        node.append_attribute("Locked").set_value(i_leadType.second->isLocked());
    }

    //LeadTypes end------------------------------------------------------------

    //Coatings node-----------------------------------------------------------
    pugi::xml_node coatingsNode = configNode.append_child("Coatings");

    for(auto& i_coating : config->getCoatings()){
        node = coatingsNode.append_child("Coating");
        node.append_attribute("Id").set_value(i_coating.first.c_str());
        node.append_attribute("Name").set_value(i_coating.second->getName().c_str());
        node.append_attribute("Locked").set_value(i_coating.second->isLocked());
    }

    //Coatings end------------------------------------------------------------

    //Energizations node-----------------------------------------------------------
    pugi::xml_node energizationsNode = configNode.append_child("Energizations");

    for(auto& i_energization : config->getEnergizations()){
        node = energizationsNode.append_child("Energization");
        node.append_attribute("Id").set_value(i_energization.first.c_str());
        node.append_attribute("Identification").set_value(i_energization.second->getIdentification().c_str());
        node.append_attribute("Type").set_value(i_energization.second->getType().c_str());
        node.append_attribute("Frequency").set_value(i_energization.second->getFrequency().c_str());
        node.append_attribute("Angle").set_value(std::to_string(i_energization.second->getAngle()).c_str());
        node.append_attribute("Magnitude").set_value(dbl2str(i_energization.second->getMagnitude()).c_str());
        node.append_attribute("Locked").set_value(i_energization.second->isLocked());
    }

    //Energizations end------------------------------------------------------------

    //Tolerances node-----------------------------------------------------------
    pugi::xml_node tolerancesNode = configNode.append_child("Tolerances");

    for(double i_tolerance : config->getTolerances()){
        node = tolerancesNode.append_child("Tolerance");
        node.append_attribute("Value").set_value(dbl2str(i_tolerance).c_str());
    }

    //Tolerances end------------------------------------------------------------

    //ConductorTypes node-----------------------------------------------------------
    pugi::xml_node conductorTypesNode = configNode.append_child("ConductorTypes");

    for(auto& i_cType : config->getConductorTypes()){
        node = conductorTypesNode.append_child("ConductorType");
        node.append_attribute("Id").set_value(i_cType.first.c_str());
        node.append_attribute("Type").set_value(i_cType.second->getType().c_str());
        node.append_attribute("Name").set_value(i_cType.second->getName().c_str());
        node.append_attribute("Resistivity").set_value(dbl2str(i_cType.second->getResistivity()).c_str());
        node.append_attribute("Permeability").set_value(dbl2str(i_cType.second->getPermeability()).c_str());
        node.append_attribute("Locked").set_value(i_cType.second->isLocked());
    }

    //ConductorTypes end------------------------------------------------------------

    //CableTypes node-----------------------------------------------------------
    pugi::xml_node cableTypesNode = configNode.append_child("CableTypes");

    for(auto& i_cbType : config->getCableTypes()){
        node = cableTypesNode.append_child("CableType");
        node.append_attribute("Id").set_value(i_cbType.first.c_str());
        node.append_attribute("Name").set_value(i_cbType.second->getName().c_str());
        node.append_attribute("Locked").set_value(i_cbType.second->isLocked());
    }

    //CableTypes end------------------------------------------------------------

    //Conductors node----------------------------------------------------------------
    pugi::xml_node conductorsNode = configNode.append_child("Conductors");
    pugi::xml_node conductorNode;

    for(auto& i_conductor : config->getConductors()){
        conductorNode = conductorsNode.append_child("Conductor");
        conductorNode.append_attribute("Id").set_value(i_conductor.first.c_str());
        conductorNode.append_attribute("Type").set_value("Conductor");

        node = conductorNode.append_child("LeadTypeId");
        if(i_conductor.second->getLeadType() != NULL){
            node.append_attribute("Value").set_value(i_conductor.second->getLeadType()->getId().c_str());
        }

        node = conductorNode.append_child("ConductorTypeId");
        if(i_conductor.second->getConductorType() != NULL){
            node.append_attribute("Value").set_value(i_conductor.second->getConductorType()->getId().c_str());
        }

        node = conductorNode.append_child("CoatingId");
        if(i_conductor.second->getCoating() != NULL){
            node.append_attribute("Value").set_value(i_conductor.second->getCoating()->getId().c_str());
        }

        node = conductorNode.append_child("EnergizationId");
        if(i_conductor.second->getEnergization() != NULL){
            node.append_attribute("Value").set_value(i_conductor.second->getEnergization()->getId().c_str());
        }

        node = conductorNode.append_child("CableTypeId");
        if(i_conductor.second->getCableType() != NULL){
            node.append_attribute("Value").set_value(i_conductor.second->getCableType()->getId().c_str());
        }

        node = conductorNode.append_child("CoordsStart");
        node.append_attribute("X").set_value(dbl2str(i_conductor.second->getStartCoords().x).c_str());
        node.append_attribute("Y").set_value(dbl2str(i_conductor.second->getStartCoords().y).c_str());
        node.append_attribute("Z").set_value(dbl2str(i_conductor.second->getStartCoords().z).c_str());

        node = conductorNode.append_child("CoordsEnd");
        node.append_attribute("X").set_value(dbl2str(i_conductor.second->getEndCoords().x).c_str());
        node.append_attribute("Y").set_value(dbl2str(i_conductor.second->getEndCoords().y).c_str());
        node.append_attribute("Z").set_value(dbl2str(i_conductor.second->getEndCoords().z).c_str());

        node = conductorNode.append_child("Radius");
        node.append_attribute("Value").set_value(dbl2str(i_conductor.second->getRadius()).c_str());
    }

    //Conductors end-----------------------------------------------------------------

    //Building Conductors node----------------------------------------------------------------
        conductorsNode = configNode.append_child("BuildingConductors");

    for(auto& i_conductor : config->getBuildingConductors()){
        conductorNode = conductorsNode.append_child("Conductor");
        conductorNode.append_attribute("Id").set_value(i_conductor.first.c_str());
        conductorNode.append_attribute("Type").set_value("BuildingConductor");

        node = conductorNode.append_child("LeadTypeId");
        if(i_conductor.second->getLeadType() != NULL){
            node.append_attribute("Value").set_value(i_conductor.second->getLeadType()->getId().c_str());
        }

        node = conductorNode.append_child("ConductorTypeId");
        if(i_conductor.second->getConductorType() != NULL){
            node.append_attribute("Value").set_value(i_conductor.second->getConductorType()->getId().c_str());
        }

        node = conductorNode.append_child("CoatingId");
        if(i_conductor.second->getCoating() != NULL){
            node.append_attribute("Value").set_value(i_conductor.second->getCoating()->getId().c_str());
        }

        node = conductorNode.append_child("EnergizationId");
        if(i_conductor.second->getEnergization() != NULL){
            node.append_attribute("Value").set_value(i_conductor.second->getEnergization()->getId().c_str());
        }

        node = conductorNode.append_child("CableTypeId");
        if(i_conductor.second->getCableType() != NULL){
            node.append_attribute("Value").set_value(i_conductor.second->getCableType()->getId().c_str());
        }

        node = conductorNode.append_child("CoordsStart");
        node.append_attribute("X").set_value(dbl2str(i_conductor.second->getStartCoords().x).c_str());
        node.append_attribute("Y").set_value(dbl2str(i_conductor.second->getStartCoords().y).c_str());
        node.append_attribute("Z").set_value(dbl2str(i_conductor.second->getStartCoords().z).c_str());

        node = conductorNode.append_child("CoordsEnd");
        node.append_attribute("X").set_value(dbl2str(i_conductor.second->getEndCoords().x).c_str());
        node.append_attribute("Y").set_value(dbl2str(i_conductor.second->getEndCoords().y).c_str());
        node.append_attribute("Z").set_value(dbl2str(i_conductor.second->getEndCoords().z).c_str());

        node = conductorNode.append_child("Radius");
        node.append_attribute("Value").set_value(dbl2str(i_conductor.second->getRadius()).c_str());
    }

    //Building Conductors end-----------------------------------------------------------------

    //Buildings node----------------------------------------------------------------
    pugi::xml_node buildingsNode = configNode.append_child("Buildings");
    pugi::xml_node buildingNode;

    for(auto& i_building : config->getBuildings()){
        buildingNode = buildingsNode.append_child("Building");
        buildingNode.append_attribute("Id").set_value(i_building.first.c_str());

        node = buildingNode.append_child("Faces");
        node.append_attribute("Value").set_value(std::to_string(i_building.second->getFaces()).c_str());

        node = buildingNode.append_child("Height");
        node.append_attribute("Value").set_value(dbl2str(i_building.second->getHeight()).c_str());

        node = buildingNode.append_child("Step");
        node.append_attribute("Value").set_value(dbl2str(i_building.second->getStep()).c_str());

        node = buildingNode.append_child("Distance");
        node.append_attribute("Min").set_value(dbl2str(i_building.second->getDistanceMin()).c_str());
        node.append_attribute("Max").set_value(dbl2str(i_building.second->getDistanceMax()).c_str());
    }

    //Buildings end-----------------------------------------------------------------

    //Computations node----------------------------------------------------------------
    pugi::xml_node computationsNode = configNode.append_child("Computations");

    node = computationsNode.append_child("GPR");
    node.append_attribute("Value").set_value(BoolToString(config->getComputations().GPR));

    node = computationsNode.append_child("POTENTIAL-SCALAR");
    node.append_attribute("Value").set_value(BoolToString(config->getComputations().POTENTIAL_SCALAR));

    node = computationsNode.append_child("ELECTRIC");
    node.append_attribute("Value").set_value(BoolToString(config->getComputations().ELECTRIC));

    node = computationsNode.append_child("MAGNETIC");
    node.append_attribute("Value").set_value(BoolToString(config->getComputations().MAGNETIC));

    node = computationsNode.append_child("VECTOR-POTENTIAL");
    node.append_attribute("Value").set_value(BoolToString(config->getComputations().VECTOR_POTENTIAL));

    node = computationsNode.append_child("GRADIENT-SCALAR");
    node.append_attribute("Value").set_value(BoolToString(config->getComputations().GRADIENT_SCALAR));

    //Computations end-----------------------------------------------------------------

    //Profiles node----------------------------------------------------------------
    pugi::xml_node profilesNode = configNode.append_child("Profiles");
    pugi::xml_node profileNode;

    for(auto& i_profile : config->getProfiles()){
        profileNode = profilesNode.append_child("Profile");
        profileNode.append_attribute("Id").set_value(i_profile.first.c_str());

        node = profileNode.append_child("XCoords");
        node.append_attribute("Start").set_value(dbl2str(i_profile.second->xCoords.start).c_str());
        node.append_attribute("End").set_value(dbl2str(i_profile.second->xCoords.end).c_str());
        node.append_attribute("Step").set_value(dbl2str(i_profile.second->xCoords.step).c_str());

        node = profileNode.append_child("YCoords");
        node.append_attribute("Start").set_value(dbl2str(i_profile.second->yCoords.start).c_str());
        node.append_attribute("End").set_value(dbl2str(i_profile.second->yCoords.end).c_str());
        node.append_attribute("Step").set_value(dbl2str(i_profile.second->yCoords.step).c_str());

        node = profileNode.append_child("NLine");
        node.append_attribute("Value").set_value(dbl2str(i_profile.second->NLine).c_str());

        node = profileNode.append_child("MCol");
        node.append_attribute("Value").set_value(dbl2str(i_profile.second->MCol).c_str());
    }

    //Profiles end-----------------------------------------------------------------
}

/*
** EPITECH PROJECT, 2020
** save
** outfile description:
** save
*/

#include "bombermanManager.hpp"
#include "Map.hpp"
#include "Player.hpp"
#include "save.hpp"

Data::Data()
{
}

Data::~Data()
{
    this->outfile.close();
    this->infile.close();
}

void Data::save(std::vector<Player *> players, std::shared_ptr<Map> map, std::string fileName)
{
    std::string str;
    try
    {
        this->outfile.open(fileName);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        exit(84);
    }
    
    for (irr::s16 index = 0; index < players.size(); index++){
        this->outfile << players[index]->getPos().X << ";" << players[index]->getPos().Z;
        if (players[index]->getStatus() == true) {
            this->outfile << "\n\t" << '0' << ";"
            << '0' << ";" << '0' << ";" << '0' << ";" << '0' << "\n\t\t";
        }
        else
            this->outfile << "\n\t" << players[index]->getKeys().front << ";"
            << players[index]->getKeys().back << ";" << players[index]->getKeys().left << ";" << players[index]->getKeys().right << ";" << players[index]->getKeys().back << "\n\t\t";
        this->outfile << static_cast<irr::u16>(players[index]->getStatistics().bombNumber) << ";" << static_cast<irr::u16>(players[index]->getStatistics().bombRange) << ";" << static_cast<irr::u16>(players[index]->getStatistics().life) << ";"
        << static_cast<irr::u16>(players[index]->getStatistics().speed) << ";" << static_cast<irr::u16>(players[index]->getStatistics().wallPass) << std::endl;
    }
    for (irr::s16 index = map->getMap().size() - 1; index >= 0; index--) {
        this->outfile << "\t\t\t";
        for (irr::s16 block = 0; block < map->getMap()[index].size(); block++) {
            this->outfile << map->getMap()[index][block]->getBlockType();
        }
        this->outfile << std::endl;
    }
    this->outfile.close();
    try
    {
        this->infile.open("save/saveList.txt");
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        exit(84);
    }
    
    for (;std::getline(infile, str);){
        str.erase(str.size());
        if (str == fileName)
            return;
    }
    this->infile.close();
    try
    {
        this->outfile.open("save/saveList.txt", std::ios::app);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        exit(84);
    }
    this->outfile << fileName << "\n";
    this->outfile.close();
}

template <class T>
T myStnbr (std::string str, T nbr) {
    nbr = 0;
    bool isDecimal = false;
    bool isNeg = false;
    if (str[0] == '-') {
        str.erase(0, 1);
        isNeg = true;
    }
    irr::s16 sizeBeforeComa = 0;
    for (irr::s16 index = 0; str[index] != '.' && index != str.size(); index++)
        sizeBeforeComa = index;
    for (irr::s16 index = 0; index != str.size(); index++) {
        if (str[index] == '.') {
            isDecimal = true;
            index++;
        }
        if (isDecimal == true)
            nbr += (static_cast<irr::f32>(str[index] - '0')) / (std::pow(10, (index - sizeBeforeComa - 1)));
        else
            nbr += (str[index] - '0');
            if (index < sizeBeforeComa)
                nbr *= 10;
    }
    if (isNeg == true)
        nbr *= -1;
    return nbr;
}

key_binding_t setBinds(std::string input)
{
    input.erase(0,1);
    std::string token;
    std::string delimiter = ";";
    size_t pos = 0;
    key_binding_t binds;
    irr::s16 nbr = 0;
    pos = input.find(delimiter);
    token = input.substr(0, pos);
    binds.front = static_cast<irr::EKEY_CODE>(myStnbr(token, nbr));
    input.erase(0, pos + delimiter.length());
    pos = input.find(delimiter);
    token = input.substr(0, pos);
    binds.back = static_cast<irr::EKEY_CODE>(myStnbr(token, nbr));
    input.erase(0, pos + delimiter.length());
    pos = input.find(delimiter);
    token = input.substr(0, pos);
    binds.left = static_cast<irr::EKEY_CODE>(myStnbr(token, nbr));
    input.erase(0, pos + delimiter.length());
    pos = input.find(delimiter);
    token = input.substr(0, pos);
    binds.right = static_cast<irr::EKEY_CODE>(myStnbr(token, nbr));
    input.erase(0, pos + delimiter.length());
    pos = input.find(delimiter);
    token = input.substr(0, pos);
    binds.bomb = static_cast<irr::EKEY_CODE>(myStnbr(token, nbr));
    input.erase(0, pos + delimiter.length());
    return binds;
}

statistics_t setStat(std::string input)
{
    input.erase(0,2);
    std::string token;
    std::string delimiter = ";";
    size_t pos = 0;
    statistics_t stat;
    irr::s16 nbr = 0;
    pos = input.find(delimiter);
    token = input.substr(0, pos);
    stat.bombNumber = static_cast<irr::EKEY_CODE>(myStnbr(token, nbr));
    input.erase(0, pos + delimiter.length());
    pos = input.find(delimiter);
    token = input.substr(0, pos);
    stat.bombRange = static_cast<irr::EKEY_CODE>(myStnbr(token, nbr));
    input.erase(0, pos + delimiter.length());
    pos = input.find(delimiter);
    token = input.substr(0, pos);
    stat.life = static_cast<irr::EKEY_CODE>(myStnbr(token, nbr));
    input.erase(0, pos + delimiter.length());
    pos = input.find(delimiter);
    token = input.substr(0, pos);
    stat.speed = static_cast<irr::EKEY_CODE>(myStnbr(token, nbr));
    input.erase(0, pos + delimiter.length());
    pos = input.find(delimiter);
    token = input.substr(0, pos);
    stat.wallPass = static_cast<irr::EKEY_CODE>(myStnbr(token, nbr));
    input.erase(0, pos + delimiter.length());
    return stat;
}


std::vector<std::vector<irr::s16>> Data::setMap(std::string input)
{
    std::vector<std::vector<irr::s16>> tab;
    std::vector<irr::s16> line;

    for (irr::s16 index = 3; index < input.size(); index++)
        line.push_back(input[index] - '0');
    tab.push_back(line);
    line.clear();
    while (getline(this->infile, input)) {
        for (irr::s16 index = 3; index < input.size(); index++)
            line.push_back(input[index] - '0');
        tab.push_back(line);
        line.clear();
    }
    return tab;
}

void Data::load(std::shared_ptr<BManager> manager, std::shared_ptr<Map> map, std::string fileName)
{
    std::string input;
    std::string token;
    std::string delimiter = ";";
    size_t pos = 0;
    float X = 0;
    float Z = 0;
    irr::f32 nbr = 0.00000;
    irr::core::vector3df vec;
    key_binding_t binds;
    try
    {
        this->infile.open(fileName);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        exit(84);
    }
    while (std::getline(this->infile, input)) {
        if (input[0] != '\t'){
            pos = input.find(delimiter);
            token = input.substr(0, pos);
            vec.X = myStnbr(token, nbr);
            input.erase(0, pos + delimiter.length());
            pos = input.find(delimiter);
            token = input.substr(0, pos);
            vec.Z = myStnbr(token, nbr);
            input.erase(0, pos + delimiter.length());
            vec.Y = 0.1;
        }
        if (input[0] == '\t' && input[1] != '\t') {
            binds = setBinds(input);
        }
            /* add pos */
        if (input[0] == '\t' && input[1] == '\t' && input[2] != '\t') {
            manager->load(binds, vec, setStat(input));
        }
        if (input[0] == '\t' && input[1] == '\t' && input[2] == '\t')
            map->load(manager, setMap(input));
    }

}
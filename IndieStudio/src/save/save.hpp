/*
** EPITECH PROJECT, 2020
** save
** File description:
** save
*/

#ifndef SAVE_HPP_
#define SAVE_HPP_

#include <fstream>
#include <iostream>
#include <string>
#include <memory>

class Map;
class BManager;

class Data {
    public:
        Data();
        ~Data();
        void save(std::vector<Player *> players, std::shared_ptr<Map> map, std::string fileName);
        void load(std::shared_ptr<BManager> manager, std::shared_ptr<Map> map, std::string fileName);
        std::vector<std::vector<irr::s16>> setMap(std::string input);
    private:
        std::ofstream outfile;
        std::ifstream infile;
};

#endif /* !SAVE_HPP_ */

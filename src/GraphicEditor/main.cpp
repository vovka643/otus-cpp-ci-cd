#include <iostream>
#include <string>

class View
{
public:

private:

};

class GeoPrimitive //base class for geo primitives
{
public:

private:

}


class Model
{
public:
    bool add_figure()
    {
        std::cout<< "Model: add figure \n";
        return true;
    }

    bool del_figure()
    {
        std::cout<< "Model: del figure \n";
        return true;
    }

    bool load_file(std::string& fileName)
    {
        std::cout<< "Model: load file "<< fileName <<"\n";
        return true;
    }

    bool save_in_file(std::string& fileName)
    {
        std::cout<< "Model: save in file "<< fileName <<"\n";
        return true;
    }

    bool create_new()
    {
        std::cout<< "Model: create new \n";
        return true;
    }

private:
    std::list<GeoPrimitive> figures;

};

class Control
{
public:
    parce_command(std::string& command)
    {
        
    }

private:

}


int main()
{
    // wtf



}
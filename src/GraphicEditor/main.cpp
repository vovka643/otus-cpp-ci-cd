#include <iostream>
#include <string>

class GeoPrimitive //base class for geo primitives
{
public:
    GeoPrimitive(int x, int y, std::string& name): m_x(x), m_y(y), m_name(name)
    {
    }

    int m_x = 0;
    int m_y = 0;
    std::string m_name = "common figure";

}

class View
{
public:

    void draw_figure(GeoPrimitive * figure){
        std::cout << "draw figure" << figure->  
    }

private:

};

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

    void Connect(View * view)
    {
        m_view = view;
    }

private:
    std::list<GeoPrimitive> figures;
    View * m_view = nullptr;

};

class Control
{
public:
    void parce_command(std::string& command)
    {
        
    }

    void Connect(Model * model)
    {
        m_model = model;
    }

private:
    Model * m_model = nullptr; 
}


int main()
{
    Control control;
    Model model;
    View view;

    control.Connect(&model);
    model.Connect(&view);

}
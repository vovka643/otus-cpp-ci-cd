#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> split(std::string s, const std::string delimiter) {
    std::vector<std::string> tokens;
    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        tokens.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    tokens.push_back(s);

    return tokens;
}

class GeoPrimitive //base class for geo primitives
{
public:
    GeoPrimitive(std::string name): m_name(name)
    {
        std::cout<< "GeoPrimitive: create " << m_name << "\n";
    }
    std::string m_name = "common figure";
};

class View
{
public:

    void draw_figure(GeoPrimitive * figure)
    {
        std::cout << "View: draw figure" << figure->m_name << "\n";
    }

    void clear_all()
    {
        std::cout << "View: clear all\n";
    }
private:

};

class Model
{
public:
    bool add_figure(std::string & figureName)
    {
        std::cout<< "Model: add figure \n";
        
        GeoPrimitive * new_figure;

        if(figureName == "triangle")
        {
            new_figure = new GeoPrimitive("Triangle");
        } 
        if( figureName == "circle")
        {
            new_figure = new GeoPrimitive("Circle"); 
        } 
        if( figureName == "square")
        {
            new_figure = new GeoPrimitive("Square"); 
        } 
        else
        {
            return false;
        }

        m_figures.push_back(new_figure); 

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

    bool redraw()
    {
        m_view->clear_all();
        for (auto & fig: m_figures)
        {
            m_view->draw_figure(fig);
        }
        return true;
    }

private:
    std::vector<GeoPrimitive*> m_figures;
    View * m_view = nullptr;
};

class Control
{
public:
    void parce_command(std::string& command)
    {
        std::vector<std::string> coms = split(command, " ");

        if(coms[0] == "add")
        {
            m_model->add_figure(coms[1]);
        } 
        else if(coms[0] == "del")
        {
            m_model->del_figure();//delete last added figure
        } 
        else if(coms[0] == "save")
        {
            m_model->save_in_file(coms[1]);
        } 
        else if(coms[0] == "open")
        {
            m_model->load_file(coms[1]);
        } 
        else if(coms[0] == "new")
        {
            m_model->create_new();
        }
    }

    void Connect(Model * model)
    {
        m_model = model;
    }

private:
    Model * m_model = nullptr; 
};

int main()
{
    Control control;
    Model model;
    View view;

    control.Connect(&model);
    model.Connect(&view);


    while(true)
    {
        //read command from user
        std::string command; 
        std::getline(std::cin, command);
        control.parce_command(command);
    }

}
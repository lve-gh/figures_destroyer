#include <iostream>
#include <memory>
#include <ctime>
#include <locale>

#include <SimpleEngineCore/Application.hpp>
#include <../src/SimpleEngineCore/Window.hpp>

class MyApp : public SimpleEngine::Application
{
    virtual void on_update() override
    {
    //    std::cout << "Update frame: " << frame++ << std::endl;
    }

    int frame = 0;
};


int main()
{
    using std::cout;
    using std::endl;
    setlocale(LC_ALL, "RU");
    auto myApp = std::make_unique<MyApp>();
    int returnCode = myApp->start(1024, 768, "My first App");
    std::cin.get();
    return returnCode;
}
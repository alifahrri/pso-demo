#include "pso.h"
#include "mainwindow.h"
#include <iostream>
#include <thread>
#include <QApplication>

class PSOThread
{
public:
    PSOThread(PSO& pso_) :
        pso(pso_)
    {
        running = true;
        loop = std::thread([&]
        {
            while(running)
            {
                static double last_step = 0.1;
                auto t0 = std::chrono::high_resolution_clock::now();
                pso.optimize(last_step);
                auto t1 = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double_t,std::milli> dt = t1-t0;
                std::chrono::duration<double_t,std::milli> sleep_time(100.0);
                sleep_time -= dt;
                std::cout << "optimize : " << dt.count() << '\n';
                last_step = dt.count();
                std::this_thread::sleep_for(sleep_time);
            }
        });
    }

    ~PSOThread()
    {
        running = false;
        if(loop.joinable())
            loop.join();
    }

    std::atomic_bool running;

private:
    PSO& pso;
    std::thread loop;
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PSO pso(300);
    MainWindow w(pso);
    pso.setFitnessFn([](PSO::State2 p, PSO::State2 v)
    {
        auto x = p.s(0);
        auto y = p.s(1);
        return sin((x+275/2)/275.0*M_PI) + cos((y)/275.0*M_PI);
    });
    PSOThread pso_updater(pso);
    w.show();
    auto ret = a.exec();
    return ret;
}

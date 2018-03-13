#include "pso.h"
#include <random>
#include <iostream>

#define OMEGA 0.35
#define PHI_SELF 0.1
#define PHI_GLOBAL 1.0
#define PHI_GLOBAL_VEL 0.1
#define PHI_RANDOM 0.1

PSO::PSO(size_t n_particle_) :
    fitness_fn(NULL),
    n_particle(n_particle_)
{
    initParticles();
}

PSO::~PSO()
{

}

void PSO::optimize(double time_step, PSO::Particles *best_path)
{
    if(!fitness_fn)
        return;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::mt19937 v_gen(rd());
    std::uniform_real_distribution<> rnd(0.0,1.1);
    std::uniform_real_distribution<> v_rnd(-1.0,1.0);
    auto g_best = global_best;
    static double sum_fitness=0.0;
    double last_sum_fitness = sum_fitness;
    sum_fitness = 0.0;
    for(auto& p : particles)
    {
        sum_fitness += p.fitness;
        auto x = p.first;
        x.s(0) += p.second.s(0)*time_step;
        x.s(1) += p.second.s(1)*time_step;
        p.second.s(0) = OMEGA*p.second.s(0) +
                PHI_SELF * rnd(gen) * (x.s(0)-p.first.s(0)) +
                PHI_GLOBAL * rnd(gen) * (g_best.first.s(0) - p.first.s(0)); /*+
                PHI_GLOBAL_VEL * (g_best.first.s(0) - p.first.s(0)) * v_rnd(gen) +
                PHI_RANDOM * last_sum_fitness/particles.size()/global_best.fitness * v_rnd(v_gen);*/
        p.second.s(1) = OMEGA*p.second.s(1) +
                PHI_SELF * rnd(gen) * (x.s(1)-p.first.s(1)) +
                PHI_GLOBAL * rnd(gen) * (g_best.first.s(1) - p.first.s(1)); /*+
                PHI_GLOBAL_VEL * (g_best.first.s(1) - p.first.s(1)) * v_rnd(gen) +
                PHI_RANDOM * last_sum_fitness/particles.size()/global_best.fitness * v_rnd(v_gen);*/
        auto fitness = fitness_fn(x,p.second);
//        if(fitness > p.fitness)
        {
            p.first = x;
            p.fitness = fitness;
            if(global_best.fitness < fitness)
                global_best = p;
        }
    }
}

PSO::Particles PSO::getParticles() const
{
    return particles;
}

void PSO::setParticles(const Particles &value)
{
    particles = value;
}

PSO::Particle PSO::getGlobal_best() const
{
    return global_best;
}

inline
void PSO::initParticles()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> rnd(100.0,250.0);
    particles.clear();
    global_best.first.s(0) = 0.0;
    global_best.first.s(1) = 0.0;
    global_best.second.s(0) = 0.0;
    global_best.second.s(1) = 0.0;
    global_best.fitness = 0.0;
    for(size_t i=0; i<n_particle; i++)
    {
        Particle p;
        p.first.s(0) = rnd(gen);
        p.first.s(1) = rnd(gen);
        p.second.s(0) = 0.1;
        p.second.s(1) = 0.1;
        if(fitness_fn)
        {
            p.fitness = fitness_fn(p.first,p.second);
            if(p.fitness >= global_best.fitness)
                global_best = p;
        }
        particles.push_back(p);
    }
}

void PSO::setFitnessFn(const FitnessFunction &value)
{
    fitness_fn = value;
    initParticles();
}

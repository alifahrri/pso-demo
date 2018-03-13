#ifndef PSO_H
#define PSO_H

#include <vector>
#include <cstdlib>
#include <functional>

class PSO
{
public:
    template <int dim>
    struct State {
        double state[dim];
        double& s(int n)
        {
            if(n<dim)
                return (state[n]);
        }
    };
    typedef State<2> State2;
    struct Particle {
        State2 first;
        State2 second;
        double fitness;
    };

    typedef std::function<double(State2,State2)> FitnessFunction;
    typedef std::vector<Particle> Particles;

public:
    PSO(size_t n_particle_);
    ~PSO();
    void optimize(double time_step, Particles* best_path=NULL);
    Particles getParticles() const;
    void setParticles(const Particles &value);
    Particle getGlobal_best() const;
    void setFitnessFn(const FitnessFunction &value);

private:
    void initParticles();

private:
    FitnessFunction fitness_fn;
    Particles particles;
    Particle global_best;
    size_t n_particle;
};

#endif // PSO_H

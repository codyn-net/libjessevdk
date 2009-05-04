#include "particle.ih"

Fitness const &PSO::Particle::bestFitness() const
{
	return d_data->bestFitness;
}

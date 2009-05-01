#include "particle.ih"

double PSO::Particle::bestFitness() const
{
	return d_data->fitness;
}

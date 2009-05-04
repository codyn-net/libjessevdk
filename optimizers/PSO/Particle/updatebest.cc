#include "particle.ih"

void PSO::Particle::updateBest()
{
	if (fitness() > d_data->bestFitness)
	{
		d_data->bestFitness = fitness().copy();
		d_data->best.assign(values().begin(), values().end());
	}
}

#include "particle.ih"

void PSO::Particle::initialize(Boundaries const &boundaries, Fitness const &fitness)
{
	d_data = new Data();
	addPrivateData(&d_data);

	Solution::initialize(boundaries, fitness);
}

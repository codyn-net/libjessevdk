#include "particle.ih"

void PSO::Particle::reset()
{
	Solution::reset();
	
	d_data->velocity.resize(boundaries().size());
	d_data->best.resize(boundaries().size());
	
	/* Initialize velocity */
	for (size_t i = 0; i < boundaries().size(); ++i)
	{
		d_data->velocity[i] = 0;
	}
	
	d_data->bestFitness->reset();
}

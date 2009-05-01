#include "particle.ih"

void PSO::Particle::updateBest()
{
	double curf = fitness().value();
	
	if (curf > d_data->fitness)
	{
		d_data->fitness = curf;
		d_data->best.assign(values().begin(), values().end());
	}
}

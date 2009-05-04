#include "particle.ih"

vector<double> const &PSO::Particle::best() const
{
	return d_data->best;
}

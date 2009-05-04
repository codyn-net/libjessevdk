#include "particle.ih"

vector<double> const &PSO::Particle::velocity() const
{
	return d_data->velocity;
}

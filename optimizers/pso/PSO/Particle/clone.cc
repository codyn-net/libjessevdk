#include "particle.ih"

PSO::Particle *PSO::Particle::clone() const
{
	return new Particle(*this);
}

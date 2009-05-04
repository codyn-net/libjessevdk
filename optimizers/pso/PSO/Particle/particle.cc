#include "particle.ih"

PSO::Particle::Particle(size_t id, Boundaries const &boundaries, Fitness const &fitness)
:
	Solution(id, boundaries, fitness)
{
	initialize(boundaries, fitness);
}

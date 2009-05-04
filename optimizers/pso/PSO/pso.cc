#include "pso.ih"

PSO::PSO(Boundaries const &boundaries, Fitness const &fitness)
:
	Optimizer(boundaries, fitness)
{
	initialize(boundaries, fitness);
}

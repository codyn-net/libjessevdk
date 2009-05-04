#include "pso.ih"

void PSO::reset()
{
	Optimizer::reset();
	
	vector<Cloneable<Solution> > &sols = solutions();
	sols.resize(d_data->populationSize);

	/* Create new initial population of particles */	
	for (size_t i = 0; i < d_data->populationSize; ++i)
	{
		Fitness *fn = fitness().copy();
		sols[i] = Particle(i, boundaries(), *fn);
		delete fn;
	}
}

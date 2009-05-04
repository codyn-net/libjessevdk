#include "pso.ih"

PSO::PSO(optimizers::PSO &pso)
:
	Optimizer()
{
	d_data = new Data(pso);
	addPrivateData(d_data);
	
	construct(d_data);
}

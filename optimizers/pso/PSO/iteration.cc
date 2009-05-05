#include "pso.ih"

bool PSO::iteration()
{
	/* Iterate over all particles and update them */
	vector<Cloneable<Solution> > sols = solutions();
	vector<Cloneable<Solution> >::iterator iter;
	
	for (iter = sols.begin(); iter != sols.end(); ++iter)
	{
		Particle &part = dynamic_cast<Particle &>(**iter);
		part.update(d_data->updateSettings, best());
	}

	/* Main optimizer determines global best and increases iteration etc */
	return Optimizer::iteration();
}

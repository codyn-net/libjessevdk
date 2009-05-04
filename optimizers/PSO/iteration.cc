#include "pso.ih"

bool PSO::iteration()
{
	/* Iterate over all particles and update them */
	vector<Cloneable<Solution> > sols = solutions();
	vector<Cloneable<Solution> >::iterator iter;
	
	Particle newbest = d_data->best;
	Cloneable<Fitness> bestFitness(newbest.bestFitness().copy());
	
	/* Let all particles tryout (fills in fitness) */
	bool ret = Optimizer::iteration();
	
	for (iter = sols.begin(); iter != sols.end(); ++iter)
	{
		Particle &part = dynamic_cast<Particle &>(**iter);
		
		part.update(d_data->updateSettings, d_data->best);
		
		if (part.bestFitness() > bestFitness)
		{
			newbest = part;
			bestFitness = newbest.bestFitness().copy();
		}
	}

	if (bestFitness > d_data->best.bestFitness())
	{
		d_data->best = newbest;
	}

	return ret;
}

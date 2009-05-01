#include "pso.ih"

bool PSO::iterate()
{
	/* Iterate over all particles and update them */
	vector<Cloneable<Solution> > sols = solutions();
	vector<Cloneable<Solution> >::iterator iter;
	
	/* Let all particles tryout (fills in fitness) */
	bool ret = Optimizer::iterate();
	
	/* Update particle velocity and positions */
	Particle best = d_data->best;
	Particle newbest = best;

	for (iter = sols.begin(); iter != sols.end(); ++iter)
	{
		Particle &part = dynamic_cast<Particle &>(*iter);
		
		part.update(d_data->updateSettings);
		
		if (part.fitness().value() > newbest.fitness().value())
		{
			newbest = part;
		}
	}
	
	d_data->best = newbest;
	return ret;
}

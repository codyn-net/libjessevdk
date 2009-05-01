#include "particle.ih"

void PSO::Particle::update(PSO::Settings const &settings, Particle const &gbest)
{
	updateBest();

	/* Update velocities and positions */
	vector<double> &position = values();
	vector<double> &velocity = d_data->velocity;
	vector<double> &best = d_data->best;

	size_t num = position.size();
	double cf = settings.cognitiveFactor;
	double sf = settings.socialFactor;

	for (size_t i = 0; i < num; ++i)
	{
		double r1 = Random<double>::range(0, 1);
		double r2 = Random<double>::range(0, 1);
		
		velocity[i] = settings.constriction * (velocity[i] + 
		                                       r1 * cf * (best[i] - position[i]) + 
		                                       r2 * sf * (gbest.best()[i] - position[i]));
		updatePosition(settings, i);
	}
}

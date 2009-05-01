#include "pso.ih"

void PSO::initialize(Boundaries const &boundaries, Fitness const &fitness)
{
	Optimizer::initialize(boundaries, fitness);
	Particle best(boundaries, fitness);

	d_data = new Data(best);
	addPrivateData(&d_data);

	/* Default settings */
	d_data->populationSize = 30;

	d_data->updateSettings.cognitiveFactor = 1.49455;
	d_data->updateSettings.socialFactor = 1.49455;
	d_data->updateSettings.constriction = 0.729;
	
	d_data->updateSettings.boundaryCondition = BoundaryCondition::None;
	d_data->updateSettings.boundaryDamping = 0;

	/* Register settings */
	settings().registerProperty("populationSize", d_data->populationSize);
	
	settings().registerProperty("cognitiveFactor", d_data->updateSettings.cognitiveFactor);
	settings().registerProperty("socialFactor", d_data->updateSettings.socialFactor);
	settings().registerProperty("constriction", d_data->updateSettings.constriction);
	
	settings().registerProperty("boundaryDamping", d_data->updateSettings.boundaryDamping);
	settings().registerProperty("boundaryCondition", d_data->updateSettings.boundaryCondition);
	
}

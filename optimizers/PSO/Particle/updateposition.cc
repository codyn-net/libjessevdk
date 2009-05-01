#include "particle.ih"

void PSO::Particle::updatePosition(PSO::Settings const &settings, size_t dimension)
{
	/* Update velocities and positions */
	vector<double> &position = values();
	vector<double> &velocity = d_data->velocity;
	vector<Boundaries::Boundary> const &bounds = boundaries();

	Boundaries::Boundary const &b = bounds[dimension];
	double newpos = position[dimension] + velocity[dimension];

	if (newpos > b.max || newpos < b.min)
	{
		switch (settings.boundaryCondition)
		{
			case BoundaryCondition::None:
				position[dimension] = newpos;
			break;
			case BoundaryCondition::NoneNoUpdate:
				position[dimension] = newpos;
			break;
			case BoundaryCondition::Stick:
				position[dimension] = Math::min(Math::max(newpos, b.min), b.max);
			break;
			case BoundaryCondition::Bounce:
				if (newpos > b.max)
				{
					position[dimension] = b.max - settings.boundaryDamping * (newpos - b.max);
				}
				else
				{
					position[dimension] = b.min - settings.boundaryDamping * (newpos + b.min);
				}
				
				velocity[dimension] = settings.boundaryDamping * -velocity[dimension];
			break;
		}
	}
	else
	{
		position[dimension] = newpos;
	}
}

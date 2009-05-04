#include "particle.ih"

PSO::Particle *PSO::Particle::copy() const
{
	Fitness *fitness = this->fitness().copy();
	Fitness *dummy = this->fitness().copy();
	
	Particle *p = new Particle(id(), boundaries(), *dummy);
	delete dummy;

	p->setFitness(*fitness);
	delete fitness;
	
	p->setValues(values());

	p->d_data->velocity = d_data->velocity;
	p->d_data->best = d_data->best;
	p->d_data->bestFitness = d_data->bestFitness->copy();
		
	return p;
}

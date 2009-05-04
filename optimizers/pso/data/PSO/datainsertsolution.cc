#include "pso.ih"

void PSO::Data::insertSolution(optimization::Solution const &solution) 
{
	Optimizer::Data::insertSolution(solution);
	
	size_t last = db.lastInsertId();
	optimizers::PSO::Particle const &particle = dynamic_cast<optimizers::PSO::Particle const &>(solution);
	
	db.query() << "UPDATE `solution` SET `velocity` = '" <<
	              SQLite::serialize(particle.velocity()) << "' WHERE " <<
	              "ROWID = " << last <<
	SQLite::Query::end();
}

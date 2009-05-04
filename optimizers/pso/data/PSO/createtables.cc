#include "pso.ih"

void PSO::createTables() 
{
	Optimizer::createTables();
	
	/* Create velocity column */
	d_data->db.query("ALTER TABLE `solution` ADD COLUMN `velocity` TEXT");
}

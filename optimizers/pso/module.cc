#include "optimization/Optimizer/optimizer.hh"
#include "PSO/pso.hh"
#include "data/PSO/pso.hh"
#include "ModuleInfo/moduleinfo.hh"

using namespace optimization;
using namespace optimizers;

static Optimizer *
create_optimizer (Boundaries const &boundaries, Fitness const &fitness)
{
	return new PSO(boundaries, fitness);
}

static data::Optimizer *
create_data (Optimizer &optimizer)
{
	return new data::PSO(dynamic_cast<PSO &>(optimizer));
}

void
optimizer_module_info (ModuleInfo *info)
{
	info->name = "pso";

	info->constructor = create_optimizer;
	info->dataConstructor = create_data;
}

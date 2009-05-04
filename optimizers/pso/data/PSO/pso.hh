#ifndef __DATA_PSO_H__
#define __DATA_PSO_H__

#include "pso/PSO/pso.hh"
#include "data/Optimizer/optimizer.hh"

namespace data
{
	class PSO : public Optimizer
	{
		struct Data : public Optimizer::Data
		{
			virtual void insertSolution(optimization::Solution const &solution);
			
			Data(optimizers::PSO &pso);
		};
		
		Data *d_data;
		
		public:
			/* Constructor/destructor */
			PSO(optimizers::PSO &pso);
			
			/* Public functions */
		protected:
			virtual void createTables();
		private:
			/* Private functions */
		
	};
}

#endif /* __DATA_PSO_H__ */

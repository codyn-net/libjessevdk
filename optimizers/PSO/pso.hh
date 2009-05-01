#ifndef __OPTIMIZERS_PSO_H__
#define __OPTIMIZERS_PSO_H__

#include "Optimizer/optimizer.hh"
#include "Solution/solution.hh"
#include "PSO/Particle/particle.hh"

#include <vector>

namespace optimizers
{
	class PSO : public optimization::Optimizer
	{
		public:
			struct BoundaryCondition
			{
				enum Values
				{
					None = 0,
					NoneNoUpdate,
					Stick,
					Bounce
				};
			};
			
			struct Settings
			{
				double cognitiveFactor;
				double socialFactor;
				double constriction;
				
				double boundaryDamping;				
				size_t boundaryCondition;				
			};
			
			class Particle : public optimization::Solution
			{
				struct Data : public base::Object::PrivateData
				{
					std::vector<double> velocity;
					std::vector<double> best;
					
					double fitness;
				};
				
				Data *d_data;
				
				public:
					Particle(optimization::Boundaries const &boundaries, optimization::Fitness const &fitness);
					
					virtual void reset();
					
					virtual Particle *clone() const;

					virtual void update(Settings const &settings);
					virtual void update(Settings const &settings, Particle const &gbest);
					
					virtual std::vector<double> const &best() const;
					virtual double bestFitness() const;
				protected:
					virtual void initialize(optimization::Boundaries const &boundaries, optimization::Fitness const &fitness);
					virtual void updateBest();
					virtual void updatePosition(Settings const &settings, size_t dimension);
			};

			/* Public functions */
			PSO(optimization::Boundaries const &boundaries, optimization::Fitness const &fitness);
			
			virtual void reset();
			virtual bool iterate();
		private:
			struct Data : public base::Object::PrivateData
			{
				/* Instance data */
				Particle best;
			
				/* Settings */
				size_t populationSize;
				Settings updateSettings;
				
				Data(Particle const &best);
			};
		
			Data *d_data;

			/* Private functions */
			virtual void initialize(optimization::Boundaries const &boundaries, optimization::Fitness const &fitness);
	};
}

#endif /* __OPTIMIZERS_PSO_H__ */


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
					
					/* Best position and fitness */
					std::vector<double> best;
					base::Cloneable<optimization::Fitness> bestFitness;
				};
				
				Data *d_data;
				
				public:
					Particle(size_t id, optimization::Boundaries const &boundaries, optimization::Fitness const &fitness);
					
					virtual void reset();
					
					virtual Particle *clone() const;
					virtual Particle *copy() const;

					virtual void update(Settings const &settings);
					virtual void update(Settings const &settings, Particle const &gbest);
					
					virtual std::vector<double> const &velocity() const;
					
					virtual std::vector<double> const &best() const;
					virtual optimization::Fitness const &bestFitness() const;
				protected:
					virtual void updateBest();
					virtual void updatePosition(Settings const &settings, size_t dimension);
				private:
					void initialize(optimization::Boundaries const &boundaries, optimization::Fitness const &fitness);
			};

			/* Public functions */
			PSO(optimization::Boundaries const &boundaries, optimization::Fitness const &fitness);
			
			virtual void reset();
			virtual bool iteration();
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
			
			void initialize(optimization::Boundaries const &boundaries, optimization::Fitness const &fitness);
	};
}

#endif /* __OPTIMIZERS_PSO_H__ */


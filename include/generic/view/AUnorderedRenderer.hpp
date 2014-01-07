#ifndef _GENERIC_VIEW_AUNORDEREDRENDERER_INCLUDED_
#define _GENERIC_VIEW_AUNORDEREDRENDERER_INCLUDED_

#include <generic/view/ARenderer.hpp>
#include <unordered_set>

namespace generic
{
	namespace view
	{
		template <class T> class AUnorderedRenderer : public ARenderer<T>
		{
		public:
			virtual bool addModel( const T * model ) override final
				{ return models.insert(model).second; }
			virtual bool removeModel( const T * model ) override final
				{ return models.erase(model) != 0; }
			virtual const std::unordered_set< const T * > & getModels() const override final
				{ return models; }
		private:
			std::unordered_set< const T * > models;
		};
	}
}

#endif

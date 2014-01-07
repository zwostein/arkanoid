#include <generic/type/Vector2.hpp>
#include <generic/model/OrderedModelUpdater.hpp>


using namespace generic;
using namespace generic::type;


bool model::OrderedModelUpdater::addUpdateable( generic::model::AUpdateable * updateable, int order )
{
	auto it = updateablesAsKeys.find( updateable );
	if( it != updateablesAsKeys.end() )
		return false; // already tracked
	updateablesAsKeys[updateable] = order;
	updateablesAsValues.insert( std::pair< int, generic::model::AUpdateable * >( order, updateable ) );
	return true;
}


bool model::OrderedModelUpdater::addUpdateable( generic::model::AUpdateable * updateable )
{
	return addUpdateable( updateable, 0 );
}


bool model::OrderedModelUpdater::removeUpdateable( generic::model::AUpdateable * updateable )
{
	auto itUpdateables = updateablesAsKeys.find( updateable );
	if( itUpdateables == updateablesAsKeys.end() )
		return false; // not tracked
	int order = (*itUpdateables).second;
	updateablesAsKeys.erase( itUpdateables );

	auto itOrderRamge = updateablesAsValues.equal_range( order );
	for( auto it = itOrderRamge.first; it != itOrderRamge.second; ++it )
	{
		if( it->second == updateable )
		{
			updateablesAsValues.erase( it );
			break;
		}
	}
	return true;
}


void model::OrderedModelUpdater::update( const double & delta )
{
	for( const auto & i : updateablesAsValues )
		i.second->update( delta );
}

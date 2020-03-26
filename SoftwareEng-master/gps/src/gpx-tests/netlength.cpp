#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "types.h"
#include "route.h"

using namespace GPS;

BOOST_AUTO_TEST_SUITE( Route_netlength )

const bool isFileName = false;

//1. Test if it is zero when there's only one position
BOOST_AUTO_TEST_CASE( OnePosition )
{
   const std::string gpxData =
           "<gpx><rte><rtept lat=\"1\" lon=\"1\"></rtept></rte></gpx>";
   Route route = Route(gpxData, isFileName);
   BOOST_CHECK_EQUAL( route.netLength(), 0 );
}

//2. Test if the answer correct when there are two positions
BOOST_AUTO_TEST_CASE( TwoPositions )
{
   const std::string gpxData =
           "<gpx><rte><rtept lat=\"1\" lon=\"1\"></rtept><rtept lat=\"2\" lon=\"2\"></rtept></rte></gpx>";
   Route route = Route(gpxData, isFileName);
   BOOST_CHECK_GT( route.netLength(), 100000 );
}

//3. Test if adding third position is the same result with the second position
BOOST_AUTO_TEST_CASE( ThreePositions )
{
   const std::string gpxData =
           "<gpx><rte><rtept lat=\"1\" lon=\"1\"></rtept><rtept lat=\"2\" lon=\"2\"></rtept><rtept lat=\"3\" lon=\"3\"></rtept></rte></gpx>";
   Route route = Route(gpxData, isFileName);
   BOOST_CHECK_GT( route.netLength(), 300000 );
}

//4. Test if two positions getting too close will be detected as one position
BOOST_AUTO_TEST_CASE( ArePositionsClose )
{
   const metres granularity = 99999999;
   const std::string gpxData =
           "<gpx><rte><rtept lat=\"1\" lon=\"1\"></rtept><rtept lat=\"2\" lon=\"2\"></rtept></rte></gpx>";
   Route route = Route(gpxData, isFileName, granularity);
   BOOST_CHECK_EQUAL( route.netLength(), 0 );
}

//5. Test if many positions getting too close will be detected as one position
BOOST_AUTO_TEST_CASE( ManyPositionsClose )
{
   const metres granularity = 99999999;
   const std::string gpxData =
           "<gpx><rte><rtept lat=\"1\" lon=\"1\"></rtept><rtept lat=\"2\" lon=\"2\"></rtept><rtept lat=\"3\" lon=\"3\"></rtept></rte></gpx>";
   Route route = Route(gpxData, isFileName, granularity);
   BOOST_CHECK_EQUAL( route.netLength(), 0 );
}

//6. Test if two positions getting too far will be detected as two positions
BOOST_AUTO_TEST_CASE( ArePositionsFar )
{
   const metres granularity = 0;
   const std::string gpxData =
           "<gpx><rte><rtept lat=\"1\" lon=\"1\"></rtept><rtept lat=\"2\" lon=\"2\"></rtept></rte></gpx>";
   Route route = Route(gpxData, isFileName, granularity);
   BOOST_CHECK_GT( route.netLength(), 100000 );
}

//7. Test if many positions getting too far will be detected as two positions
BOOST_AUTO_TEST_CASE( ManyPositionsFar )
{
   const metres granularity = 0;
   const std::string gpxData =
           "<gpx><rte><rtept lat=\"1\" lon=\"1\"></rtept><rtept lat=\"2\" lon=\"2\"></rtept><rtept lat=\"3\" lon=\"3\"></rtept></rte></gpx>";
   Route route = Route(gpxData, isFileName, granularity);
   BOOST_CHECK_GT( route.netLength(), 300000 );
}

//8. Test if total length is the same with net length when there is only one position
BOOST_AUTO_TEST_CASE( OnePos_TotalvsNET )
{
   const std::string gpxData =
           "<gpx><rte><rtept lat=\"1\" lon=\"1\"></rtept></rte></gpx>";
   Route route = Route(gpxData, isFileName);
   BOOST_CHECK( route.netLength() == route.totalLength());
}

//9. Test if total length is the same with net length when there are two positions
BOOST_AUTO_TEST_CASE( TwoPos_TotalvsNET )
{
   const std::string gpxData =
           "<gpx><rte><rtept lat=\"1\" lon=\"1\"></rtept><rtept lat=\"2\" lon=\"2\"></rtept></rte></gpx>";
   Route route = Route(gpxData, isFileName);
   BOOST_CHECK( route.netLength() == route.totalLength());
}

//10. Test if total length is the same with net length when there are many positions
BOOST_AUTO_TEST_CASE( ManyPos_TotalvsNET )
{
   const std::string gpxData =
           "<gpx><rte><rtept lat=\"1\" lon=\"1\"></rtept><rtept lat=\"3\" lon=\"3\"></rtept><rtept lat=\"2\" lon=\"2\"></rtept></rte></gpx>";
   Route route = Route(gpxData, isFileName);
   BOOST_CHECK( route.netLength() != route.totalLength() );
}

BOOST_AUTO_TEST_SUITE_END()

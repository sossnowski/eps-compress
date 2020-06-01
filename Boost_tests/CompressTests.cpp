#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <vector>
#include "../File.h"
#include "../Coords.h"
#include "../Compress.h"


namespace utf = boost::unit_test;
using namespace std;



BOOST_AUTO_TEST_SUITE (CompressFileSuite)

    BOOST_AUTO_TEST_CASE( CountingScale, * utf::tolerance(0.00001) )
    {
        Compress c;
        c.setImageDimension(400);
        c.setOriginalImageWidth(300);
        float scale = c.getScale();
        float result = 400.0 /300.0;

        BOOST_TEST(scale == result);
    }

    BOOST_AUTO_TEST_CASE (FileDataIterating, * utf::tolerance(0.0000001))
    {

        Compress c;
        float number = 10.4511;
        float rounded = c.roundToTwoDecimal(number);
        BOOST_TEST (rounded == 10.45);
    }

    BOOST_AUTO_TEST_CASE (SortingByY)
    {

        Compress c;
        Coords c1 = {5, 8, 1}, c2 = {4,4,7}, c3 = {8, 12,143}, c4 = {56, 9, 11};
        vector<Coords>v;
        v.push_back(c1);
        v.push_back(c2);
        v.push_back(c3);
        v.push_back(c4);
        c.sortVectorByY(&v);
        BOOST_TEST (v[0].y == c2.y);
    }

    BOOST_AUTO_TEST_CASE (SortingByX)
    {

        Compress c;
        Coords c1 = {5, 8, 1}, c2 = {4,4,7}, c3 = {8, 12,143}, c4 = {56, 9, 11};
        vector<Coords>v;
        v.push_back(c1);
        v.push_back(c2);
        v.push_back(c3);
        v.push_back(c4);
        c.sortVectorByX(&v);
        BOOST_TEST (v[3].x == c4.x);
    }

    BOOST_AUTO_TEST_CASE (SortingByPosition)
    {

        Compress c;
        Coords c1 = {5, 8, 1}, c2 = {4,4,7}, c3 = {8, 12,143}, c4 = {56, 9, 11};
        vector<Coords>v;
        v.push_back(c1);
        v.push_back(c2);
        v.push_back(c3);
        v.push_back(c4);
        c.sortVectorByPosition(&v);
        BOOST_TEST (v[3].position == c3.position);
    }

BOOST_AUTO_TEST_SUITE_END( )
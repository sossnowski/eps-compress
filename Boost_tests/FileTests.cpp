#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include "../File.h"



BOOST_AUTO_TEST_SUITE (FileTestSuite)

    BOOST_AUTO_TEST_CASE( OutputFileName )
    {
        File f = File("path/to/file.eps");
        BOOST_CHECK(f.getOutFileName() == "path/to/file_out.eps");
    }

    BOOST_AUTO_TEST_CASE (FileOpenError)
    {

        File f = File("path/to/file.eps");
        int width = 400;
        BOOST_CHECK_THROW (f.processData(width), std::ios_base::failure);
    }

    BOOST_AUTO_TEST_CASE (OpenFileToGetEssentialLines)
    {

        File f = File("path/to/file.eps");
        Compress c;
        BOOST_CHECK_THROW (f.findEssentialLines(&c, "path/to/file.eps"), std::ios_base::failure);
    }

    BOOST_AUTO_TEST_CASE (SaveToOutputFile)
    {

        File f = File("/Users/sossnowski/ownProjects/epsCompress/Boost_tests/testFile.txt");
        int width = 400;
        BOOST_CHECK_NO_THROW( f.processData(width) );
    }

BOOST_AUTO_TEST_SUITE_END( )
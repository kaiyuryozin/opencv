// This file is part of OpenCV project.
// It is subject to the license terms in the LICENSE file found in the top-level directory
// of this distribution and at http://opencv.org/license.html.

// Note: all tests here are DISABLED by default due specific requirements.
// Don't use #if 0 - these tests should be tested for compilation at least.
//
// Usage: opencv_test_videoio --gtest_also_run_disabled_tests --gtest_filter=*VideoIO_Camera*<tested case>*

#include "test_precomp.hpp"

namespace opencv_test { namespace {

TEST(DISABLED_VideoIO_Camera, basic)
{
    VideoCapture capture(0);
    ASSERT_TRUE(capture.isOpened());
    std::cout << "Camera 0 via " << capture.getBackendName() << " backend" << std::endl;
    std::cout << "Frame width: " << capture.get(CAP_PROP_FRAME_WIDTH) << std::endl;
    std::cout << "     height: " << capture.get(CAP_PROP_FRAME_HEIGHT) << std::endl;
    std::cout << "Capturing FPS: " << capture.get(CAP_PROP_FPS) << std::endl;

    const int N = 100;
    Mat frame;
    int64 time0 = cv::getTickCount();
    for (int i = 0; i < N; i++)
    {
        SCOPED_TRACE(cv::format("frame=%d", i));

        capture >> frame;
        ASSERT_FALSE(frame.empty());

        EXPECT_GT(cvtest::norm(frame, NORM_INF), 0) << "Complete black image has been received";
    }
    int64 time1 = cv::getTickCount();
    printf("Processed %d frames on %.2f FPS\n", N, (N * cv::getTickFrequency()) / (time1 - time0 + 1));

    capture.release();
}

}} // namespace

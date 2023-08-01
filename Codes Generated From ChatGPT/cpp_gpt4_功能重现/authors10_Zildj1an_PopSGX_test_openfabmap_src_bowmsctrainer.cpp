#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/features2d.hpp>

class MeanShiftBoWTrainer
{
public:
    MeanShiftBoWTrainer(float clusterSize) : clusterSize_(clusterSize) {}

    void add(const std::vector<cv::Mat> &descriptors);
    void clear();
    std::vector<cv::Mat> cluster() const;

private:
    float clusterSize_;
    std::vector<cv::Mat> descriptors_;
};

void MeanShiftBoWTrainer::add(const std::vector<cv::Mat> &descriptors)
{
    for (const auto &descriptor : descriptors)
    {
        descriptors_.push_back(descriptor);
    }
}

void MeanShiftBoWTrainer::clear()
{
    descriptors_.clear();
}

std::vector<cv::Mat> MeanShiftBoWTrainer::cluster() const
{
    if (descriptors_.empty())
    {
        return std::vector<cv::Mat>();
    }

    // 1. Merge all descriptors and use Mean Shift to generate centroids as initial cluster centers
    cv::Mat mergedDescriptors;
    cv::vconcat(descriptors_, mergedDescriptors);

    cv::Mat labels;
    cv::Mat stats;
    cv::Mat centroids;

    cv::TermCriteria termCriteria(cv::TermCriteria::COUNT + cv::TermCriteria::EPS, 100, 0.1);
    int numCentroids = cv::meanShift(mergedDescriptors, labels, stats, centroids, clusterSize_, termCriteria);

    std::cout << "Number of centroids found: " << numCentroids << std::endl;

    // 2. Assign each descriptor to the nearest centroid
    std::vector<std::vector<cv::Mat>> clusters(numCentroids);
    for (int i = 0; i < mergedDescriptors.rows; ++i)
    {
        int label = labels.at<int>(i, 0);
        clusters[label].push_back(mergedDescriptors.row(i));
    }

    // 3. Compute cluster centers (Bag of Words)
    std::vector<cv::Mat> bagOfWords(numCentroids);
    for (int i = 0; i < numCentroids; ++i)
    {
        if (!clusters[i].empty())
        {
            cv::Mat clusterSamples;
            cv::vconcat(clusters[i], clusterSamples);
            cv::reduce(clusterSamples, bagOfWords[i], 0, cv::REDUCE_AVG);
            bagOfWords[i] = bagOfWords[i].reshape(0, 1);
        }
    }

    std::cout << "Bag of Words computed." << std::endl;

    return bagOfWords;
}

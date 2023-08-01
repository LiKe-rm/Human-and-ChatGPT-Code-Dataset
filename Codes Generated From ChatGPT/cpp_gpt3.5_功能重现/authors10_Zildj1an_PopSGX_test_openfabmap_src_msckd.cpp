#include <iostream>
#include <vector>
#include <algorithm>
#include <opencv2/core.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/xfeatures2d.hpp>

using namespace cv;
using namespace std;

class ModifiedSequentialClustering {
public:
    ModifiedSequentialClustering(int cluster_size, int min_descriptors_per_cluster, bool random_shuffle = false)
        : cluster_size_(cluster_size), min_descriptors_per_cluster_(min_descriptors_per_cluster), random_shuffle_(random_shuffle) {}

    Mat createVisualVocabulary(const vector<Mat>& descriptors_list) {
        Mat merged_descriptors = mergeDescriptors(descriptors_list);
        vector<int> initial_centroid_indices = selectInitialCentroids(merged_descriptors);

        FlannBasedMatcher matcher;
        vector<DMatch> matches;
        matcher.add(merged_descriptors);
        matcher.train();

        // Compute the initial clusters
        vector<vector<int>> clusters(cluster_size_);
        for (int centroid_index : initial_centroid_indices) {
            Mat centroid = merged_descriptors.row(centroid_index);
            matcher.match(centroid, matches);

            for (const DMatch& match : matches) {
                int cluster_id = match.trainIdx;
                clusters[cluster_id].push_back(match.queryIdx);
            }
        }

        // Refine clusters and compute the final centroids
        Mat visual_vocabulary(cluster_size_, merged_descriptors.cols, merged_descriptors.type());
        for (int i = 0; i < cluster_size_; ++i) {
            if (clusters[i].size() >= min_descriptors_per_cluster_) {
                Mat cluster_descriptor(0, merged_descriptors.cols, merged_descriptors.type());
                for (int idx : clusters[i]) {
                    cluster_descriptor.push_back(merged_descriptors.row(idx));
                }
                reduce(cluster_descriptor, visual_vocabulary.row(i), 0, REDUCE_AVG);
            } else {
                visual_vocabulary.row(i).setTo(Scalar(0));
            }
        }

        return visual_vocabulary;
    }

private:
    Mat mergeDescriptors(const vector<Mat>& descriptors_list) {
        Mat merged_descriptors;
        for (const Mat& descriptors : descriptors_list) {
            merged_descriptors.push_back(descriptors);
        }
        return merged_descriptors;
    }

    vector<int> selectInitialCentroids(const Mat& merged_descriptors) {
        int num_descriptors = merged_descriptors.rows;
        vector<int> indices(num_descriptors);
        for (int i = 0; i < num_descriptors; ++i) {
            indices[i] = i;
        }

        if (random_shuffle_) {
            random_shuffle(indices.begin(), indices.end());
        }

        int step = num_descriptors / cluster_size_;
        vector<int> initial_centroid_indices(cluster_size_);
        for (int i = 0; i < cluster_size_; ++i) {
            initial_centroid_indices[i] = indices[i * step];
        }

        return initial_centroid_indices;
    }

    int cluster_size_;
    int min_descriptors_per_cluster_;
    bool random_shuffle_;
};

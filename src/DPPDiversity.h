#ifndef DPP_DIVERSITY_DPPDIVERSITY_H
#define DPP_DIVERSITY_DPPDIVERSITY_H


#include <unordered_map>
#include <vector>
#include <iostream>
#include "deps/eigen-3.3.9/Eigen/Core"
#include "deps/eigen-3.3.9/Eigen/Dense"


class DPPDiversity {

public:
    typedef Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic> Mat;
    typedef Eigen::Matrix<float, Eigen::Dynamic, 1> RatingVec;

    DPPDiversity(): N(0), d(0) {}
    void init(
            const std::vector<std::vector<float> > &item_representations,
            const std::vector<float> &item_ratings);
    void select(int n, std::vector<std::pair<int, float> >* res);
    void show_weighted_corr_mat() {
        std::cout << corr_mat << std::endl;
    }

private:
    static float dot_product(const std::vector<float> &v1, const std::vector<float> &v2) {
        size_t n1 = v1.size(), n2 = v2.size();
        float res = 0;
        if (n1 != n2 || n1 == 0)
            return res;
        for (size_t i = 0; i < n1; i++) {
            res += v1[i] * v2[i];
        }
        return res;
    }

    int N; int d;
    Mat item_mat;
    RatingVec rating_vec;
    Mat corr_mat;
};


#endif //DPP_DIVERSITY_DPPDIVERSITY_H

#ifndef DPP_DIVERSITY_DPPDIVERSITY_H
#define DPP_DIVERSITY_DPPDIVERSITY_H


#include <unordered_map>
#include <vector>
#include <iostream>
#include "deps/eigen-3.3.9/Eigen/Core"
#include "deps/eigen-3.3.9/Eigen/Dense"


class DPPDiversity {

public:
    typedef std::unordered_map<std::string, int> t_mapping;
    typedef std::unordered_map<int, std::string> t_mapping_reverse;
    typedef std::pair<float, std::vector<float> > t_item_representation;
    typedef Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic> ItemMatrix;
    typedef Eigen::Matrix<float, Eigen::Dynamic, 1> RatingVec;
    typedef Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic> CorrMatrix;

    DPPDiversity(): N(0), d(0), _name_id_mp(nullptr) {}
    void init(const std::unordered_map<std::string, t_item_representation > &items, int feature_dim);
    void select(int n, std::unordered_map<int, float>* res);
    void show_id_mapping() {
        for (const auto &p : *_name_id_mp)
            std::cout << p.first << " = " << p.second << ";";
        std::cout << std::endl;
    }
    int getN() { return N; }
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
    std::shared_ptr<t_mapping> _name_id_mp;
    std::shared_ptr<t_mapping_reverse> _id_name_mp;
    ItemMatrix item_mat;
    RatingVec rating_vec;
    CorrMatrix corr_mat;
};


#endif //DPP_DIVERSITY_DPPDIVERSITY_H

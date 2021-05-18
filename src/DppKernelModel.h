#ifndef UNTITLED_DPPKERNELMODEL_H
#define UNTITLED_DPPKERNELMODEL_H


#include <cstddef>
#include <memory>
#include <vector>
#include <random>
#include <unordered_set>
#include <iostream>
#include <chrono>
#include <cstring>
#include "ctime"
#include "deps/eigen-3.3.9/Eigen/Core"
#include "deps/eigen-3.3.9/Eigen/Dense"


class DppKernelModel {

public:
    typedef Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic> Mat;

    explicit DppKernelModel(size_t num_items, size_t embedding_size, float regularization = 0.1): _num_items(num_items), _emb_size(embedding_size), _num_iter(0), _accumulate_log_likelihood(0), _regularization(regularization) {
        std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
        std::chrono::system_clock::duration tp = now.time_since_epoch();
        generator = std::default_random_engine(static_cast<unsigned>(tp / std::chrono::microseconds(1)));
        _item_representations_ptr = std::shared_ptr<Mat>(new Mat(_num_items, _emb_size));
        std::uniform_real_distribution<float > rand = std::uniform_real_distribution<float>(-1, 1);
        for (size_t i = 0; i < _num_items; i++) {
            for (size_t j = 0; j < _emb_size; j++) {
                (*_item_representations_ptr)(i, j) = rand(generator);
            }
        }
        _iter_log_likelihood_ptr = std::shared_ptr<std::vector<float> >(new std::vector<float>());
    }

    void stochastic_train(const std::vector<std::vector<size_t > > &samples, float learning_rate, size_t neg_sample_cnt, size_t epoch) {
        size_t i = 0;
        while (epoch-- > 0) {
            for (const auto &one_pos_sample: samples) {
                size_t n = one_pos_sample.size();
                if (n == 0) continue;
                i = 0;
                while (i++ < neg_sample_cnt) {
                    std::vector<size_t> one_neq_sample(n);
                    neg_sampling(&one_neq_sample, _num_items-1);
                    update_param(one_neq_sample, -1, learning_rate);
                }
                update_param(one_pos_sample, 1, learning_rate);
            }
        }
    };

    Mat get_item_representation() {
        return *_item_representations_ptr;
    }

    std::vector<float> get_log_likelihoods() {
        return *_iter_log_likelihood_ptr;
    }

    static void parse_sample(const std::string &file_path, std::vector<std::vector<size_t> >* sample_ptr, std::vector<std::string> *item_names);

private:
    void update_param(const std::vector<size_t > &sample, float label /*+1 -1*/, float learning_rate) {
        size_t n = sample.size();
        if (n == 0) return;
        Mat pos_grad(n, _emb_size);
        gradient(sample, &pos_grad, label);
        for (size_t i = 0; i < n; i++)
            for (size_t j = 0; j < _emb_size; j++)
                (*_item_representations_ptr)(sample[i], j) += learning_rate * pos_grad(i, j);
    };

    void gradient(const std::vector<size_t > &index_set, Mat* grad, float label) {
        size_t n = grad->rows();
        if (n == 0) return;
        Mat subset_item_mat(n, _emb_size);
        for (size_t i = 0; i < n; i++)
            subset_item_mat.row(i) = _item_representations_ptr->row(index_set[i]);
        Mat subset_kernel_mat = subset_item_mat * subset_item_mat.transpose();
        for (size_t i = 0; i < n; i++)
            subset_kernel_mat(i, i) += _regularization;
        _num_iter++;
        float det_Y = subset_kernel_mat.determinant();
        _accumulate_log_likelihood += log(det_Y);
        float avg_log_likelihood = _accumulate_log_likelihood / _num_iter;
        _iter_log_likelihood_ptr->emplace_back(avg_log_likelihood);
        *(grad) = label / det_Y * subset_kernel_mat.adjoint().transpose() * subset_item_mat;
    }

    void neg_sampling(std::vector<size_t >* res, size_t max_index) {
        if (!res)
            return;
        size_t n = res->size();
        std::unordered_set<size_t > uniq;
        size_t uniq_cnt = 0;
        std::uniform_int_distribution<size_t > rand = std::uniform_int_distribution<size_t>(0, max_index);
        while (uniq_cnt < n) {
            size_t rand_num = rand(generator);
            if (uniq.find(rand_num) == uniq.end()) {
                uniq.insert(rand_num);
                (*res)[uniq_cnt] = rand_num;
                uniq_cnt++;
            }
        }
    }


    size_t _num_items;
    size_t _emb_size;
    std::shared_ptr<Mat> _item_representations_ptr;
    std::default_random_engine generator;
    float _num_iter, _accumulate_log_likelihood, _regularization;
    std::shared_ptr<std::vector<float > > _iter_log_likelihood_ptr;
};


#endif //UNTITLED_DPPKERNELMODEL_H

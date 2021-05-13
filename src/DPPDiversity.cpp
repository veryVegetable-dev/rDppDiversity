#include "DPPDiversity.h"
#include <cmath>



void DPPDiversity::init(const std::unordered_map<std::string, t_item_representation > &items, int feature_dim) {
    N = items.size();
    d = feature_dim;
    _name_id_mp = std::shared_ptr<t_mapping>(new t_mapping());
    _id_name_mp = std::shared_ptr<t_mapping_reverse>(new t_mapping_reverse());
    item_mat.resize(N, d);
    rating_vec.resize(N);
    corr_mat.resize(N, N);
    for (const auto &p : items) {
        if (_name_id_mp->find(p.first) == _name_id_mp->end()) {
            int curr_idx = _name_id_mp->size();
            (*_name_id_mp)[p.first] = curr_idx;
            (*_id_name_mp)[curr_idx] = p.first;
        }
        rating_vec((*_name_id_mp)[p.first]) = p.second.first;
        if (p.second.second.size() != d) return;
        for (int i = 0; i < d; i++)
            item_mat((*_name_id_mp)[p.first], i) = p.second.second[i];
    }
    ItemMatrix weighted_corr_mat = item_mat.transpose() * rating_vec.asDiagonal();
    corr_mat = weighted_corr_mat.transpose() * weighted_corr_mat;
}

void DPPDiversity::select(int n, std::unordered_map<int, float>* res) {
    if (n > N || N <= 0) return;
    // init
    int init_elem = 0;
    for (int i = init_elem + 1; i < N; i++) {
        if (corr_mat(i, i) > corr_mat(init_elem, init_elem))
            init_elem = i;
    }
    (*res)[init_elem] = corr_mat(init_elem, init_elem);
    n--;
    // iter
    std::unordered_map<int, std::vector<float> > cond_prob_mp;
    int last_added_elem = init_elem;
    while (n-- > 0) {
        int i = 0, curr_added_elem = 0;
        for (; i < N; i++) {
            if (res->find(i) != res->end() && curr_added_elem == i) {
                curr_added_elem++;
                continue;
            }
            float curr_cond_prob = (corr_mat(last_added_elem,i) - dot_product(cond_prob_mp[last_added_elem], cond_prob_mp[i])) / (sqrt(corr_mat(last_added_elem, last_added_elem)) + 1e-4);
            cond_prob_mp[i].emplace_back(curr_cond_prob);
            corr_mat(i, i) -= curr_cond_prob * curr_cond_prob;
            if (corr_mat(i, i) > corr_mat(curr_added_elem, curr_added_elem)) {
                curr_added_elem = i;
            }
        }
        (*res)[curr_added_elem] = corr_mat(curr_added_elem, curr_added_elem);
        last_added_elem = curr_added_elem;
    }
}

#include "DPPDiversity.h"
#include <cmath>
#include <unordered_set>


void DPPDiversity::init(
        std::vector<std::vector<float> > item_representations,
        std::vector<float> item_ratings) {
    N = item_representations.size();
    if (N == 0 || item_ratings.size() != N)
        return;
    d = item_representations[0].size();
    item_mat.resize(N, d);
    rating_vec.resize(N);
    corr_mat.resize(N, N);
    for (int i = 0; i < N; i++) {
        rating_vec(i) = item_ratings[i];
        if (item_representations[i].size() != d) return;
        for (int j = 0; j < d; j++)
            item_mat(i, j) = item_representations[i][j];
    }
    Mat weighted_corr_mat = item_mat.transpose() * rating_vec.asDiagonal();
    corr_mat = weighted_corr_mat.transpose() * weighted_corr_mat;
}

void DPPDiversity::select(int n, std::vector<std::pair<int, float> >* res) {
    if (n > N || N <= 0) return;
    std::unordered_set<int> selected;
    // init
    int init_elem = 0;
    for (int i = init_elem + 1; i < N; i++) {
        if (corr_mat(i, i) > corr_mat(init_elem, init_elem))
            init_elem = i;
    }
    res->emplace_back(init_elem, corr_mat(init_elem, init_elem));
    selected.insert(init_elem);
    n--;
    // iter
    std::unordered_map<int, std::vector<float> > cond_prob_mp;
    int last_added_elem = init_elem;
    while (n-- > 0) {
        int i = 0, curr_added_elem = 0;
        for (; i < N; i++) {
            if (selected.find(i) != selected.end()) {
                if (curr_added_elem == i)
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
        res->emplace_back(curr_added_elem, corr_mat(curr_added_elem, curr_added_elem));
        selected.insert(curr_added_elem);
        last_added_elem = curr_added_elem;
    }
}

#include <Rcpp.h>
#include "DppKernelModel.h"
#include <string>


// [[Rcpp::export]]
Rcpp::List learnItemEmb(
        std::string train_data_path,
        int emb_size, float regularization, float learning_rate, int neg_sample_cnt, int epoch) {

    // parse sample
    std::vector<std::vector<size_t > > samples;
    std::vector<std::string> item_names;
    DppKernelModel::parse_sample(train_data_path, &samples, &item_names);
    size_t num_items = item_names.size();

    // init model & train emb
    DppKernelModel dppKernelModel(num_items, emb_size, regularization);
    dppKernelModel.stochastic_train(samples, learning_rate, neg_sample_cnt, epoch);

    // return item_emb / corr mat / avg log likelihood / item name vec
    DppKernelModel::Mat item_emb = dppKernelModel.get_item_representation();
    std::vector<float> log_likelihood = dppKernelModel.get_log_likelihoods();
    Rcpp::List tmp(3);
    Rcpp::NumericMatrix itemEmb(num_items, emb_size);
    Rcpp::CharacterVector itemNames(num_items);
    for (size_t i = 0; i < num_items; i++) {
        for (size_t j = 0; j < emb_size; j++)
            itemEmb(i, j) = item_emb(i, j);
        itemNames(i) = item_names[i];
    }
    Rcpp::NumericVector avgLogLikelihood(log_likelihood.begin(), log_likelihood.end());
    tmp[0] = itemEmb;
    tmp[1] = itemNames;
    tmp[2] = avgLogLikelihood;
    return tmp;
}

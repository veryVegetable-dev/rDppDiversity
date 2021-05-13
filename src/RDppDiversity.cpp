#include <Rcpp.h>
#include "DPPDiversity.h"



// [[Rcpp::export]]
Rcpp::NumericVector meanC(Rcpp::List item_representations, Rcpp::NumericVector ratings, int n) {
    DPPDiversity dppDiversity;
    int list_n = item_representations.size();
    if (list_n == 0) {
        Rcpp::NumericVector res(0);
        return res;
    }
    int d = Rcpp::as<Rcpp::NumericVector>(item_representations[0]).size();
    std::vector<std::vector<float> > itemsCpp(list_n, std::vector<float>(d));
    std::vector<float> ratingsCpp(list_n);
    for (int i = 0; i < list_n; i++) {
        ratingsCpp[i] = ratings[i];
        Rcpp::NumericVector tmp_items = Rcpp::as<Rcpp::NumericVector>(item_representations[i]);
        for (int j = 0; j < d; j++)
            itemsCpp[i][j] = tmp_items[j];
    }
    dppDiversity.init(itemsCpp, ratingsCpp);
    std::vector<std::pair<int, float> > *res = new std::vector<std::pair<int, float> >();
    dppDiversity.select(n, res);
    std::vector<float> gain(n);
    for (size_t i = 0; i < n; i++)
        gain[i] = (*res)[i].second;
    Rcpp::NumericVector res_r_1(gain.begin(), gain.end());
    return res_r_1;
}

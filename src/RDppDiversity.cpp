#include <Rcpp.h>
#include "DPPDiversity.h"



// [[Rcpp::export]]
Rcpp::DataFrame bestSubset(Rcpp::NumericMatrix item_representations, Rcpp::NumericVector ratings, int n) {
    DPPDiversity dppDiversity;
    int rows = item_representations.nrow();
    int cols = item_representations.ncol();
    if (rows == 0 || cols == 0) {
        Rcpp::NumericVector res(0);
        return res;
    }
    std::vector<std::vector<float> > itemsCpp(rows, std::vector<float>(cols));
    std::vector<float> ratingsCpp(rows);
    for (int i = 0; i < rows; i++) {
        ratingsCpp[i] = ratings[i];
        for (int j = 0; j < cols; j++)
            itemsCpp[i][j] = item_representations(i, j);
    }
    dppDiversity.init(itemsCpp, ratingsCpp);
    std::vector<std::pair<int, float> > *res = new std::vector<std::pair<int, float> >();
    dppDiversity.select(n, res);
    int valid_n = res->size();
    std::vector<float> gain(valid_n), id(valid_n);
    for (size_t i = 0; i < valid_n; i++) {
        gain[i] = (*res)[i].second;
        id[i] = (*res)[i].first;
    }
    Rcpp::NumericVector gainVec(gain.begin(), gain.end());
    Rcpp::NumericVector idVec(id.begin(), id.end());
    Rcpp::List tmp(2);
    Rcpp::CharacterVector names(2);
    tmp[0] = idVec;
    tmp[1] = gainVec;
    names[0] = "id";
    names[1] = "gain";
    Rcpp::DataFrame df(tmp);
    df.attr("names") = names;
    return df;
}

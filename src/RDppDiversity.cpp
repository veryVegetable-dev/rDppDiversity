#include <Rcpp.h>
#include "DPPDiversity.h"


using namespace Rcpp;

// [[Rcpp::export]]
NumericVector meanC(NumericVector item_ratings) {
    DPPDiversity dppDiversity;
    std::vector<float> res = {1, 2, 3};
    NumericVector res_r(res.begin(), res.end());
    return res_r;
}

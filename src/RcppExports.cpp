// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

// bestSubset
Rcpp::DataFrame bestSubset(Rcpp::NumericMatrix item_representations, Rcpp::NumericVector ratings, int n);
RcppExport SEXP _rDppDiversity_bestSubset(SEXP item_representationsSEXP, SEXP ratingsSEXP, SEXP nSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::NumericMatrix >::type item_representations(item_representationsSEXP);
    Rcpp::traits::input_parameter< Rcpp::NumericVector >::type ratings(ratingsSEXP);
    Rcpp::traits::input_parameter< int >::type n(nSEXP);
    rcpp_result_gen = Rcpp::wrap(bestSubset(item_representations, ratings, n));
    return rcpp_result_gen;
END_RCPP
}
// learnItemEmb
Rcpp::List learnItemEmb(std::string train_data_path, int emb_size, float regularization, float learning_rate, int neg_sample_cnt, int epoch);
RcppExport SEXP _rDppDiversity_learnItemEmb(SEXP train_data_pathSEXP, SEXP emb_sizeSEXP, SEXP regularizationSEXP, SEXP learning_rateSEXP, SEXP neg_sample_cntSEXP, SEXP epochSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::string >::type train_data_path(train_data_pathSEXP);
    Rcpp::traits::input_parameter< int >::type emb_size(emb_sizeSEXP);
    Rcpp::traits::input_parameter< float >::type regularization(regularizationSEXP);
    Rcpp::traits::input_parameter< float >::type learning_rate(learning_rateSEXP);
    Rcpp::traits::input_parameter< int >::type neg_sample_cnt(neg_sample_cntSEXP);
    Rcpp::traits::input_parameter< int >::type epoch(epochSEXP);
    rcpp_result_gen = Rcpp::wrap(learnItemEmb(train_data_path, emb_size, regularization, learning_rate, neg_sample_cnt, epoch));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_rDppDiversity_bestSubset", (DL_FUNC) &_rDppDiversity_bestSubset, 3},
    {"_rDppDiversity_learnItemEmb", (DL_FUNC) &_rDppDiversity_learnItemEmb, 6},
    {NULL, NULL, 0}
};

RcppExport void R_init_rDppDiversity(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}

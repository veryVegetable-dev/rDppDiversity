// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

// meanC
Rcpp::DataFrame meanC(Rcpp::NumericMatrix item_representations, Rcpp::NumericVector ratings, int n);
RcppExport SEXP _rDppDiversity_meanC(SEXP item_representationsSEXP, SEXP ratingsSEXP, SEXP nSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::NumericMatrix >::type item_representations(item_representationsSEXP);
    Rcpp::traits::input_parameter< Rcpp::NumericVector >::type ratings(ratingsSEXP);
    Rcpp::traits::input_parameter< int >::type n(nSEXP);
    rcpp_result_gen = Rcpp::wrap(meanC(item_representations, ratings, n));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_rDppDiversity_meanC", (DL_FUNC) &_rDppDiversity_meanC, 3},
    {NULL, NULL, 0}
};

RcppExport void R_init_rDppDiversity(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}

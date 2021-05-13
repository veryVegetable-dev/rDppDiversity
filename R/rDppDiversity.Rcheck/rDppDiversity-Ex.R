pkgname <- "rDppDiversity"
source(file.path(R.home("share"), "R", "examples-header.R"))
options(warn = 1)
library('rDppDiversity')

base::assign(".oldSearch", base::search(), pos = 'CheckExEnv')
base::assign(".old_wd", base::getwd(), pos = 'CheckExEnv')
cleanEx()
nameEx("bestSubset")
### * bestSubset

flush(stderr()); flush(stdout())

### Name: bestSubset
### Title: Title
### Aliases: bestSubset

### ** Examples

library(rDppDiversity)
bestSubset(matrix(c(-0.1, -0.15, 0.2, 0.3, -0.2, -0.3), nrow=3, ncol=2, byrow=TRUE), c(1, 2, 3), 3)



### * <FOOTER>
###
cleanEx()
options(digits = 7L)
base::cat("Time elapsed: ", proc.time() - base::get("ptime", pos = 'CheckExEnv'),"\n")
grDevices::dev.off()
###
### Local variables: ***
### mode: outline-minor ***
### outline-regexp: "\\(> \\)?### [*]+" ***
### End: ***
quit('no')

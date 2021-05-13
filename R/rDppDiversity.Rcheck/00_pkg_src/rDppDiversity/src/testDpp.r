install.packages("/Users/menglingwu/Documents/2021/coding/personal_projects/rDppDiversity_0.0.0.9000.tar.gz", repos = NULL, type="source")
library(rDppDiversity)
bestSubset(matrix(c(-0.1, -0.15, 0.2, 0.3, -0.2, -0.3), nrow=3, ncol=2, byrow=TRUE), c(1, 2, 3), 3)

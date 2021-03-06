# Source code for MULCCH: Multi-task consensus clustering
Please see our publication in Bioinformatics:
Z Niu, D Chasman, AJ Eisfeld, Y Kawaoka, S Roy. 2016. Multi-task consensus clustering of genome-wide transcriptomes from related biological conditions. Bioinformatics 32 (10), 1509-1517. https://doi.org/10.1093/bioinformatics/btw007

This code is designed to be run AFTER producing the original Arboretum results for several random initializations on the input data.

For more information about Arboretum, please see Roy et al, Genome Research 2013 (http://genome.cshlp.org/content/23/6/1039.full).


## There are 2 steps to do the consensus clustering on the results from separate inits of Arboretum.
*********************************************************
1. compute eigen vector for similarity matrix. => Eigen
This code is included in EigenVector. We included executable program(Eigen) and an example of usage (runEigen.sh).

Usage1 :./Eigen -s similarity file  -d dimension -n [0|1] normalize -t threshold -b binary -o outfile
Usage2 :./Eigen -l file list  -d dimension -n [0|1] normalize -t threshold -b binary -o outfile

Input Arguments:
-s similarity matrix, e.g.similarityMatrix.txt
-l file list of multiple cluster assignments
-d dimension
-n 1 or 0 normalized laplacian or not
-t threshold, if less than threshold, set to be 0, if threshold=0 weighted graph is equal to fully connected graph.
-b binary,1 or 0. if 1, set the value that is greater than threshold to be 1.
-o name of outfile

*NOTE: 
The genes in output files are placed in the same order as that of similarity matrix (usage1) or the first input cluster assignment(usage2).

*********************************************************
2. use arboretum to cluster eigen vector. => Arboretum
We included executable program(incAncClust_SpcFast) with example of usage (runArboretum.sh) in directory of Arboretum.

Usage: ./incAncClust_SpcFast viruses_order mapping k tree initial_clusters random[rseed|none] output_dir mode[learn|generate|visualize] src_virus init_type[uniform|branch_length] p_diagonal_nonleaf

Input Arguments:
viruses_order: the order of multiple viruses
mapping: viruses mapping
k: number of clusters
tree: tree structure of viruses describing their relationship
initial_clusters: initial cluster assignments



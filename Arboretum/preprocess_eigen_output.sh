for f in `cat Order_human_influenza`
do
cut -f 1 -d _ ../input/clusterassign1.txt > ${f}_genes.txt
paste ${f}_genes.txt result_vector | cut -f 1-6 > ${f}.txt
done

awk '{printf("%s_A\t%s\t%s\t%s\t%s\t%s\t%s\n",$1,$2,$3,$4,$5,$6)} ' H1N1.txt > H1N1_A.txt
awk '{printf("%s_B\t%s\t%s\t%s\t%s\t%s\t%s\n",$1,$2,$3,$4,$5,$6)} ' NL.txt > NL_B.txt
awk '{printf("%s_C\t%s\t%s\t%s\t%s\t%s\t%s\n",$1,$2,$3,$4,$5,$6)} ' PB2-627E.txt > PB2-627E_C.txt
awk '{printf("%s_D\t%s\t%s\t%s\t%s\t%s\t%s\n",$1,$2,$3,$4,$5,$6)} ' NS1trunc124.txt > NS1trunc124_D.txt
awk '{printf("%s_E\t%s\t%s\t%s\t%s\t%s\t%s\n",$1,$2,$3,$4,$5,$6)} ' H5N1.txt > H5N1_E.txt
awk '{printf("%s_F\t%s\t%s\t%s\t%s\t%s\t%s\n",$1,$2,$3,$4,$5,$6)} ' PB1-F2del.txt > PB1-F2del_F.txt
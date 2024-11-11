set term pdfcairo dashed enhanced
set datafile separator " "
set size ratio 0.7

zRef=6
zMin=0

#set xrange [0.001:1]
set yrange [0:50]
set grid
set key top right
set xlabel "{/Symbol e} [m^2 s^{-3}]"
set ylabel "Non-dimensionalised height, z/z_{ref}"
set offset .05, .05

set linestyle 1 lt 6 lw 1 ps 1.2 pt 6 lc rgb "black"
set linestyle 2 lt 6 lw 2 ps 0.5 pt 2 lc rgb "orange"
set linestyle 3 lt 6 lw 2 ps 0.8 pt 4 lc rgb "brown"
set linestyle 4 lt 6 lw 2 lc rgb "red"
set linestyle 5 lt 6 lw 2 lc rgb "blue"

# OpenFOAM
endTime=5000
samplesCellAt0=sprintf("postProcessing/samples_omega/%d/x_0mCell_omega.xy", endTime)
samplesPatchAt0=sprintf("postProcessing/samples_omega/%d/x_0mPatch_omega.xy", endTime)

samplesAt2500=sprintf("postProcessing/samples_omega/%d/x_2500m_omega.xy", endTime)
samplesAt4000=sprintf("postProcessing/samples_omega/%d/x_4000m_omega.xy", endTime)

samplesCellAt5000=sprintf("postProcessing/samples_omega/%d/x_5000mCell_omega.xy", endTime)
samplesPatchAt5000=sprintf("postProcessing/samples_omega/%d/x_5000mPatch_omega.xy", endTime)
   
set output "omega.pdf"
plot \
    samplesCellAt0 u 2:(($1-zMin)/zRef) t "OpenFOAM, x=0 m (Patch)" w l ls 2,\
    samplesAt2500 u 2:(($1-zMin)/zRef) t "OpenFOAM, x=2500 m" w l ls 3,\
    samplesAt4000 u 2:(($1-zMin)/zRef) t "OpenFOAM, x=4000 m" w l ls 4,\
    samplesCellAt5000 u 2:(($1-zMin)/zRef) t "OpenFOAM, x=5000 m (Patch)" w l ls 5
    

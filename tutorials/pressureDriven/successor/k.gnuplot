set term pdfcairo dashed enhanced
set datafile separator " "
set size ratio 0.7

set xrange [0:2]
set yrange [0:500]
set grid
set key top right
set xlabel "k [m^2 s^{-2}]"
set ylabel "Height, z"
set offset .05, .05

set linestyle 1 lt 6 lw 1 ps 0.5 pt 6 lc rgb "black"
set linestyle 2 lt 6 lw 1 ps 0.5 pt 6 lc rgb "orange"
set linestyle 3 lt 6 lw 1 ps 0.8 pt 4 lc rgb "brown"
set linestyle 4 lt 6 lw 2 lc rgb "red"
set linestyle 5 lt 6 lw 2 lc rgb "blue"
set linestyle 6 lt 6 lw 2 lc rgb "gray"
set linestyle 7 lt 6 lw 2 lc rgb "green"

# Benchmark

benchmark="../data/k-RN-Fig11a"

# OpenFOAM
endTime=5000
samplesCellAt0=sprintf("postProcessing/samples_k/%d/x_0mCell_k.xy", endTime)
samplesPatchAt0=sprintf("postProcessing/samples_k/%d/x_0mPatch_k.xy", endTime)

samplesAt2500=sprintf("postProcessing/samples_k/%d/x_2500m_k.xy", endTime)
samplesAt4000=sprintf("postProcessing/samples_k/%d/x_4000m_k.xy", endTime)

samplesCellAt5000=sprintf("postProcessing/samples_k/%d/x_5000mCell_k.xy", endTime)
samplesPatchAt5000=sprintf("postProcessing/samples_k/%d/x_5000mPatch_k.xy", endTime)
   
set output "k.pdf"
plot \
    benchmark u 1:2 w lp t "Richards-Norris inlet" ls 1 pointinterval 5,\
    benchmark u 3:4 w lp t "Richards-Norris outlet" ls 2 pointinterval 5,\
    samplesCellAt0 u 2:1 t "OpenFOAM, x=0 m (Patch)" w l ls 4,\
    samplesAt2500 u 2:1 t "OpenFOAM, x=2500 m" w l ls 5,\
    samplesAt4000 u 2:1 t "OpenFOAM, x=4000 m" w l ls 6,\
    samplesCellAt5000 u 2:1 t "OpenFOAM, x=5000 m (Patch)" w l ls 7,\
    

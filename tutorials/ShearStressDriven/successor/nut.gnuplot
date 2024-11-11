set term pdfcairo dashed enhanced
set datafile separator " "
set size ratio 0.7

zRef=6
zMin=0
rho = 1.2

set xrange [0:120]
set yrange [0:50]
set grid
set key bottom right
set xlabel "{/Symbol m}_t [Pa.s]"
set ylabel "Non-dimensionalised height, z/z_{ref}"
set offset .05, .05

set linestyle 1 lt 6 lw 1 ps 1.2 pt 6 lc rgb "black"
set linestyle 2 lt 6 lw 1 ps 0.5 pt 2 lc rgb "orange"
set linestyle 3 lt 6 lw 1 ps 0.8 pt 4 lc rgb "brown"
set linestyle 4 lt 6 lw 2 lc rgb "red"
set linestyle 5 lt 6 lw 2 lc rgb "blue"
set linestyle 6 lt 6 lw 2 lc rgb "gray"
set linestyle 7 lt 6 lw 2 lc rgb "green"

# Benchmark

benchmark0="data/mut-RH-Fig6d"
benchmark1="data/mut-HW-Fig6d-2500"
benchmark2="data/mut-HW-Fig6d-4000"

# OpenFOAM
endTime=5000
samplesCellAt0=sprintf("postProcessing/samples_nut/%d/x_0mCell_nut.xy", endTime)
samplesPatchAt0=sprintf("postProcessing/samples_nut/%d/x_0mPatch_nut.xy", endTime)

samplesAt2500=sprintf("postProcessing/samples_nut/%d/x_2500m_nut.xy", endTime)
samplesAt4000=sprintf("postProcessing/samples_nut/%d/x_4000m_nut.xy", endTime)

samplesCellAt5000=sprintf("postProcessing/samples_nut/%d/x_5000mCell_nut.xy", endTime)
samplesPatchAt5000=sprintf("postProcessing/samples_nut/%d/x_5000mPatch_nut.xy", endTime)
   
set output "nut.pdf"
plot \
    benchmark0 u 1:2 t "Richards-Hoxey" ls 1,\
    benchmark1 u 1:2 t "Hargreaves-Wright, x=2500 m" w p ls 2,\
    benchmark2 u 1:2 t "Hargreaves-Wright, x=4000 m" w p ls 3,\
    samplesCellAt0 u ($2*rho):(($1-zMin)/zRef) t "OpenFOAM, x=0 m (Patch)" w l ls 4,\
    samplesAt2500 u ($2*rho):(($1-zMin)/zRef) t "OpenFOAM, x=2500 m" w l ls 5,\
    samplesAt4000 u ($2*rho):(($1-zMin)/zRef) t "OpenFOAM, x=4000 m" w l ls 6,\
        samplesCellAt5000 u ($2*rho):(($1-zMin)/zRef) t "OpenFOAM, x=5000 m (Patch)" w l ls 7,\
    

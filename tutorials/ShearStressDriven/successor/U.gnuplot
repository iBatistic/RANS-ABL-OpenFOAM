set term pdfcairo dashed enhanced
set datafile separator " "
set size ratio 0.7

zRef=6
zMin=0

set xrange [4:18]
set yrange [0:50]
set grid
set key top left
set xlabel "U_x [m s^{-1}]"
set ylabel "Non-dimensionalised height, z/z_{ref}"
set offset .05, .05

set linestyle 1 lt 6 lw 2 ps 1.2 pt 6 lc rgb "black"
set linestyle 2 lt 6 lw 2 ps 0.5 pt 2 lc rgb "orange"
set linestyle 3 lt 6 lw 2 ps 0.8 pt 4 lc rgb "brown"
set linestyle 4 lt 6 lw 2 lc rgb "red"
set linestyle 5 lt 6 lw 2 lc rgb "blue"

# Benchmark
benchmark="data/Ux-HW-RH-Fig6a"

# OpenFOAM
endTime=5000
samplesCellAt0=sprintf("postProcessing/samples_u/%d/x_0mCell_U.xy", endTime)
samplesPatchAt0=sprintf("postProcessing/samples_u/%d/x_0mPatch_U.xy", endTime)

samplesAt2500=sprintf("postProcessing/samples_u/%d/x_2500m_U.xy", endTime)
samplesAt4000=sprintf("postProcessing/samples_u/%d/x_4000m_U.xy", endTime)

samplesCellAt5000=sprintf("postProcessing/samples_u/%d/x_5000mCell_U.xy", endTime)
samplesPatchAt5000=sprintf("postProcessing/samples_u/%d/x_5000mPatch_U.xy", endTime)

set output "U_x=0.pdf"
plot \
    benchmark u 1:2 t "Richards-Hoxey" ls 1,\
    benchmark u 1:2 t "Hargreaves-Wright, x=2500m" w p ls 2,\
    benchmark u 1:2 t "Hargreaves-Wright, x=4000m" w p ls 3,\
    samplesCellAt0 u 2:(($1-zMin)/zRef) t "OpenFOAM, x=0 m (Patch)" w l ls 4,\
    samplesPatchAt0 u 2:(($1-zMin)/zRef) t "OpenFOAM, x=0 m (Cell)" w l ls 5

set output "U_x=5000.pdf"
plot \
    benchmark u 1:2 t "Richards-Hoxey" ls 1,\
    benchmark u 1:2 t "Hargreaves-Wright, x=2500 m" w p ls 2,\
    benchmark u 1:2 t "Hargreaves-Wright, x=4000 m" w p ls 3,\
    samplesCellAt5000 u 2:(($1-zMin)/zRef) t "OpenFOAM, x=5000 m (Patch)" w l ls 4,\
    samplesPatchAt5000 u 2:(($1-zMin)/zRef) t "OpenFOAM, x=50000 m (Cell)" w l ls 5

set output "U_x=2500and4000.pdf"
plot \
    benchmark u 1:2 t "Richards-Hoxey" ls 1,\
    benchmark u 1:2 t "Hargreaves-Wright, x=2500m" w p ls 2,\
    benchmark u 1:2 t "Hargreaves-Wright, x=4000m" w p ls 3,\
    samplesAt2500 u 2:(($1-zMin)/zRef) t "OpenFOAM, x=2500 m" w l ls 4,\
    samplesAt4000 u 2:(($1-zMin)/zRef) t "OpenFOAM, x=4000 m" w l ls 5
    
set output "U_x_0_2500_4000_5000.pdf"
plot \
    samplesCellAt0 u 2:(($1-zMin)/zRef) t "OpenFOAM, x=0 m (Patch)" w l ls 4,\
    samplesAt2500 u 2:(($1-zMin)/zRef) t "OpenFOAM, x=2500 m" w l ls 3,\
    samplesAt4000 u 2:(($1-zMin)/zRef) t "OpenFOAM, x=4000 m" w l ls 2,\
        samplesCellAt5000 u 2:(($1-zMin)/zRef) t "OpenFOAM, x=5000 m (Patch)" w l ls 5,\
    

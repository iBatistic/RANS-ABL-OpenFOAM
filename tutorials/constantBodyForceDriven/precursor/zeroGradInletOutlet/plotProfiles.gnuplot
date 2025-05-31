set terminal pdfcairo enhanced font "Nimbus Roman,12"
set datafile separator " "
set size ratio 0.7

zRef=6
uRef=10
rho=1.2
uTau=0.6252
endTime=100000

set linestyle 1 lt 6 lw 3 ps 0.5 pt 6 lc rgb "blue"
set linestyle 2 lt 6 lw 3 ps 0.5 pt 2 lc rgb "red"
set linestyle 3 lt 6 lw 2 ps 1.2 pt 4 lc rgb "black"
set linestyle 4 lt 6 lw 2 ps 1.2 lc rgb "grey"

samplesCellAt0=sprintf("postProcessing/sample_lines/%d/x_0mCell_epsilon_k_nut_U.xy", endTime)
samplesCellAt5000=sprintf("postProcessing/sample_lines/%d/x_5000mCell_epsilon_k_nut_U.xy", endTime)

###############################################################################
#                                Velocity profile
###############################################################################

set output "U.pdf"
set xrange [0.4:1.8]
set yrange [0:50]
set grid
set key spacing 1.5
set key top left
set xlabel "{/:Italic u} / {/:Italic u}_{ref}" font "Nimbus Roman,14"
set ylabel "{/:Italic z} / {/:Italic z}_{ref}" font "Nimbus Roman,14"
set offset .05, .05

plot \
    samplesCellAt0 u ($5/uRef):($1/zRef) t "OpenFOAM, x = 0 m" w l ls 1,\
    samplesCellAt5000 u ($5/uRef):($1/zRef) t "OpenFOAM, x = 5000 m" w l ls 2

###############################################################################
#                                k profile
###############################################################################
set output "k.pdf"
set xrange [0:5]
set yrange [0:50]
set grid
set key spacing 1.5
set key t r
set ylabel "{/:Italic z} / {/:Italic z}_{ref}" font "Nimbus Roman,14"
set xlabel "{/:Italic k} / {/:Italic u}_{{/Symbol t}}^2" font "Nimbus Roman,14"
set offset .05, .05

benchmark="../../literature/k-Cai-Fig3"

plot \
    samplesCellAt0 u ($3/uTau**2):(($1)/zRef) t "OpenFOAM, x = 0 m" w l ls 1,\
    samplesCellAt5000 u ($3/uTau**2):(($1)/zRef) t "OpenFOAM, x = 5000 m" w l ls 2,\
    benchmark u 1:2 w lp t "Cai et al. (2014)" ls 3 pointinterval 3,\

###############################################################################
#                                epsilon profile
###############################################################################

set output "epsilon.pdf"
set xrange [0:2]
set yrange [0:50]
set grid
set key spacing 1.5
set key top right
set ylabel "{/:Italic z} / {/:Italic z}_{ref}" font "Nimbus Roman,14"
set xlabel "{/:Italic {/Symbol e}} {/:Italic z}_{ref} / {/:Italic u}_{{/Symbol t}}^3" font "Nimbus Roman,14"
set offset .05, .05

plot \
    samplesCellAt0 u ($2*zRef/uTau):($1/zRef) t "OpenFOAM, x = 0 m" w l ls 1,\
    samplesCellAt5000 u ($2*zRef/uTau):($1/zRef) t "OpenFOAM, x = 5000 m" w l ls 2


###############################################################################
#                                nut profile
###############################################################################

set output "nut.pdf"
set xrange [0:25]
set yrange [0:50]
set grid
set key spacing 1.5
set key b right
set ylabel "{/:Italic z} / {/:Italic z}_{ref}" font "Nimbus Roman,14"
set xlabel "{/:Italic {/Symbol m}}_t / ( {/:Italic {/Symbol r}} {/:Italic u}_{{/Symbol t}} {/:Italic z}_{ref})" font "Nimbus Roman,14"
set offset .05, .05

plot \
    samplesCellAt0 u ($4*rho/(rho*uTau*zRef)):($1/zRef) w l ls 1 t "OpenFOAM, x = 0 m",\
    samplesCellAt5000 u ($4*rho/(rho*uTau*zRef)):($1/zRef) w l ls 2 t "OpenFOAM, x = 5000 m"
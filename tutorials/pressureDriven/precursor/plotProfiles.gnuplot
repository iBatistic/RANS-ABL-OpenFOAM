set terminal pdfcairo enhanced font "Nimbus Roman,12"
set datafile separator " "
set size ratio 0.7

zRef=6
uRef=10
rho=1.2
uTau=0.6252
endTime=20000

set linestyle 1 lt 6 lw 3 ps 0.5 pt 6 lc rgb "blue"
set linestyle 2 lt 6 lw 3 ps 0.5 pt 2 lc rgb "red"
set linestyle 3 lt 6 lw 2 ps 1.2 pt 4 lc rgb "black"
set linestyle 4 lt 6 lw 2 ps 1.2 lc rgb "grey"

###############################################################################
#                                Velocity profile
###############################################################################
# Benchmark
benchmark="../literature/Ux-RN-Fig11b"

samplesCellAt0=sprintf("postProcessing/samples_u/%d/x_0mCell_U.xy", endTime)
samplesCellAt5000=sprintf("postProcessing/samples_u/%d/x_5000mCell_U.xy", endTime)

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
    samplesCellAt0 u ($2/uRef):($1/zRef) t "OpenFOAM, x = 0 m" w l ls 1,\
    samplesCellAt5000 u ($2/uRef):($1/zRef) t "OpenFOAM, x = 5000 m" w l ls 2,\
    benchmark u ($1/uRef):($2/zRef) every 3 t "Richards and Norris (2015)" w lp ls 3


###############################################################################
#                                k profile
###############################################################################
# Benchmark
benchmark="../literature/k-RN-Fig11a"

set output "k.pdf"
set xrange [0:5]
set yrange [0:50]
set grid
set key spacing 1.5
set key t r
set ylabel "{/:Italic z} / {/:Italic z}_{ref}" font "Nimbus Roman,14"
set xlabel "{/:Italic k} / {/:Italic u}_{{/Symbol t}}^2" font "Nimbus Roman,14"
set offset .05, .05

samplesCellAt0=sprintf("postProcessing/samples_k/%d/x_0mCell_k.xy", endTime)
samplesCellAt5000=sprintf("postProcessing/samples_k/%d/x_5000mCell_k.xy", endTime)

plot \
    samplesCellAt0 u ($2/uTau**2):(($1)/zRef) t "OpenFOAM, x = 0 m" w l ls 1,\
    samplesCellAt5000 u ($2/uTau**2):(($1)/zRef) t "OpenFOAM, x = 5000 m" w l ls 2,\
    benchmark u ($1/uTau**2):(($2)/zRef) w lp t "Richards and Norris (2015), x = 0 m" ls 3 pointinterval 3,\
    benchmark u ($3/uTau**2):(($4)/zRef) w lp t "Richards and Norris (2015),\n x = 5000 m" ls 4 pointinterval 4
    
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

samplesCellAt0=sprintf("postProcessing/samples_epsilon/%d/x_0mCell_epsilon.xy", endTime)
samplesCellAt5000=sprintf("postProcessing/samples_epsilon/%d/x_5000mCell_epsilon.xy", endTime)
   
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

samplesCellAt0=sprintf("postProcessing/samples_nut/%d/x_0mCell_nut.xy", endTime)
samplesCellAt5000=sprintf("postProcessing/samples_nut/%d/x_5000mCell_nut.xy", endTime)
   
plot \
    samplesCellAt0 u ($2*rho/(rho*uTau*zRef)):($1/zRef) w l ls 1 t "OpenFOAM, x = 0 m",\
    samplesCellAt5000 u ($2*rho/(rho*uTau*zRef)):($1/zRef) w l ls 2 t "OpenFOAM, x = 5000 m"

###############################################################################
#                                omega profile
###############################################################################
# Uncoment for the case of k-omega turbulence model

set output "omega.pdf"
set xrange [0:25]
set yrange [0:50]
set grid
set key spacing 1.5
set key b right
set ylabel "{/:Italic z} / {/:Italic z}_{ref}" font "Nimbus Roman,14"
set xlabel "{/Symbol e} [m^2 s^{-3}]"
set offset .05, .05

#samplesCellAt0=sprintf("postProcessing/samples_omega/%d/x_0mCell_omega.xy", endTime)
#samplesCellAt5000=sprintf("postProcessing/samples_omega/%d/x_5000mCell_omega.xy", endTime)
   
#set output "omega.pdf"
#plot \
#    samplesCellAt0 u 2:($1/zRef) t "OpenFOAM, x = 0 m" w l ls 1,\
#    samplesCellAt5000 u 2:($1/zRef) t "OpenFOAM, x = 5000 m" w l ls 2
    
  

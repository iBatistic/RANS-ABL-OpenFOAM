set term pdfcairo dashed enhanced color size 8in,10in

set output "Forces.pdf"
set grid
set key top right
set xlabel "Iteration"
set ylabel "Force [N]"

buildingForce = "postProcessing/forces-building/0/force.dat"

set multiplot layout 3,1 title "Forces on the building"

set title "Total force, x-component"
plot buildingForce using 1:2 title "building" with lines lw 2

set title "Total force, y-component"
plot buildingForce using 1:(-$3) title "building (negative)" with lines lw 2

set title "Total force, z-component"
plot buildingForce using 1:4 title "building" with lines lw 2

unset multiplot
unset output

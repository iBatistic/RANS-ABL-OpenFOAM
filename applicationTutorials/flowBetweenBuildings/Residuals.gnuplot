set term pdfcairo dashed enhanced

set log y
set grid
set format y '%.0e';
set size ratio 0.7
set title "Residuals"
set ylabel 'Residual'
set xlabel 'Iteration'
set output "Residuals.pdf"

plot "< cat log.simpleFoam| grep 'Solving for Ux' | cut -d' ' -f9 | tr -d ','" title 'Ux' with lines,\
     "< cat log.simpleFoam| grep 'Solving for Uz' | cut -d' ' -f9 | tr -d ','" title 'Uz' with lines,\
     "< cat log.simpleFoam| grep 'Solving for p' | cut -d' ' -f9 | tr -d ','" title 'p' with lines,\
     "< cat log.simpleFoam| grep 'Solving for k' | cut -d' ' -f9 | tr -d ','" title 'k' with lines,\
     "< cat log.simpleFoam| grep 'Solving for epsilon' | cut -d' ' -f9 | tr -d ','" title 'epsilon' with lines

# Add this line in the case of k-omega turbulence model
     #"< cat log.simpleFoam| grep 'Solving for omega' | cut -d' ' -f9 | tr -d ','" title 'omega' with lines

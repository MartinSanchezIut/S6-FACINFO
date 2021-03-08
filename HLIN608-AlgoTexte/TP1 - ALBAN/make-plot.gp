#!/usr/bin/gnuplot

set terminal png notransparent interlace truecolor enhanced nocrop font "arial,18" size 1600,1200

set title "Comparatif des algorithmes\npour la Somme\ndes entiers Consécutifs"
set xtics 0,25000
set xlabel "Valeur de n"
set ylabel "Somme calculée"

set key outside below height 2

algos  = "Iter Rec Math OptV1 OptV2"
nb_algos = words(algos)

do for [o=0:3] {
  png_file = sprintf("valeurs-O%d.png", o)
  titre = "Résultats des algorithmes calulant\n"
  titre = titre . "la somme des entiers consécutifs de 0 à 10000\n"
  titre = titre . sprintf("(compilés avec l'option -O%d)", o)
  files = ""
  do for [i=1:nb_algos] {
    files = files . sprintf(" res-%s-O%d.csv", word(algos, i), o)
  }
  set output png_file
  set title titre
  plot for [i=1:nb_algos] word(files,i) using 3:4 with linespoints pointsize (nb_algos-i+1) title sprintf("Algo %s", word(algos, i))
}

set yrange [-0.125:4]
set ylabel "Temps (en sec.)"
set ytics nomirror
set y2label "Mémoire (KB)"
set y2range [-128:4*1024]
set y2tics 0,1024

set key maxcols 2

do for [o=0:3] {
  png_file = sprintf("performances-O%d.png", o)
  titre = "Performances des algorithmes calulant\n"
  titre = titre . "la somme des entiers consécutifs de 0 à 10000\n"
  titre = titre . sprintf("(compilés avec l'option -O%d)", o)
  files = ""
  do for [i=1:nb_algos] {
    files = files . sprintf(" res-%s-O%d.csv", word(algos, i), o)
  }
  set output png_file
  set title titre
  plot for [i=1:nb_algos] word(files,i) using 3:($5/1000) with lines title sprintf("Temps %s", word(algos, i)), \
       for [i=1:nb_algos] word(files,i) using 3:6 with linespoints pointtype 6 pointsize 1 title sprintf("Mémoire %s", word(algos, i)) axes x1y2
}

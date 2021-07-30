BEGIN {
  prod = 1
}

{
  prod *= $3-$4
}

END {
  print prod
}

BEGIN {
  s = 0
}

{
  s = s + $3
}

END {
  print s
}

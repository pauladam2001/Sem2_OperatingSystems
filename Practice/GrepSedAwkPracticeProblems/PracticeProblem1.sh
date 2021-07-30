#!/bin/sh

grep -E -v "^$" PracticeProblem1.txt | sed -E "s/^-/\"/" | sed -E "s/(^\".*)($)/\1\"/" | awk '{if($1 ~ /\<Hagrid\>/)
													print $1, $2, NF
											       else
                                                                                                        print    #SAU print $0 (entire input line)
												}'

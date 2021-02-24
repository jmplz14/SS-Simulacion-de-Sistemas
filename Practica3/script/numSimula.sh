totalTor=0
totalVel=0
for i in {1..100}
do  
    varSinMejora=$(./$1 $2 3)
    varSinMejora="$( cut -d ':' -f 1 <<< "$varSinMejora" )"
    varConMejoraTor=$(./$1 $2 3 1)
    varConMejoraTor="$( cut -d ':' -f 1 <<< "$varConMejoraTor" )"
    
    if (( $(echo "$varSinMejora > $varConMejoraTor" |bc -l) ))
    then
        totalTor=$((totalTor+1))
    fi
    varConMejoraVel=$(./$1 $2 3 0 1)
    varConMejoraVel="$( cut -d ':' -f 1 <<< "$varConMejoraVel" )"
    if (( $(echo "$varSinMejora > $varConMejoraVel" |bc -l) ))
    then
        totalVel=$((totalVel+1))
    fi
    
    echo $i

done

echo "Veces que es mejor con tormenta: $totalTor"
echo "Veces que es mejor con velocidad: $totalVel"
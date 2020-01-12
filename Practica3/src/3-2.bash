totalTor=0
totalVel=0
n = 100
for i in {1..100}
do  
    varSinMejora=$(./$1 $2 3)
    varSinMejora="$( cut -d ':' -f 1 <<< "$varSinMejora" )"
    sleep 1
    varConMejoraTor=$(./$1 $2 3 1)
    varConMejoraTor="$( cut -d ':' -f 1 <<< "$varConMejoraTor" )"
    sleep 1
    #totalTor = `expr "$totalTor" + "$varConMejoraTornum"`
    totalTor =  echo ' $totalTor + $varConMejoraTor' | bc -l
    #totalTor = $((totalTor + varConMejoraTor))

    varConMejoraVel=$(./$1 $2 3 0 1)
    varConMejoraVel="$( cut -d ':' -f 1 <<< "$varConMejoraVel" )"    
    #totalVel = `expr "$totalVel" + "$varConMejorVel"`
    totalVel = $(($totalVel + $varConMejoraVel))
    sleep 1

done

echo "Veces que es mejor con tormenta: $totalTor"
echo "Veces que es mejor con velocidad: $totalVel"
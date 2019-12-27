rm "datosTor.txt"
rm "datosVel.txt"
repes=125
for (( c=1; c<=$repes; c++ ))
do
	varSinMejora=$(./$1 $2 3)
    varSinMejora="$( cut -d ':' -f 1 <<< "$varSinMejora" )"
    varConMejoraTor=$(./$1 $2 3 1)
    varConMejoraTor="$( cut -d ':' -f 1 <<< "$varConMejoraTor" )"
    
    echo $varConMejoraTor >> "datosTor.txt"
    varConMejoraVel=$(./$1 $2 3 0 1)
    varConMejoraVel="$( cut -d ':' -f 1 <<< "$varConMejoraVel" )"
    echo $varConMejoraVel >> "datosVel.txt"
    
    echo $c
done





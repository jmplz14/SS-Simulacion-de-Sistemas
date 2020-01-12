rm "datos5.txt"
rm "datos4.txt"
rm "datosTor.txt"
rm "datosVel.txt"
repes=125
for (( c=1; c<=$repes; c++ ))
do

    var=$(./$1 $2 4)
    var="$( cut -d ':' -f 1 <<< "$var" )"
    
    echo $var >> "datos4.txt"

    sleep 1

    var=$(./$1 $2 5)
    var="$( cut -d ':' -f 1 <<< "$var" )"
    echo $var >> "datos5.txt"
    sleep 1
    

    var=$(./$1 $2 3 1)
    var="$( cut -d ':' -f 1 <<< "$var" )"
    echo $var >> "datosTor.txt"

    sleep 1

    var=$(./$1 $2 3 0 1)
    var="$( cut -d ':' -f 1 <<< "$var" )"
    echo $var >> "datosVel.txt"
    echo $c
    sleep 1
done





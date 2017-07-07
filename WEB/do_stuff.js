
window.onload = function(){
  getdata('GET', 'http://crypter.dynu.com/FTA/lora/WEB/api/v2/devices', )
 };




 function getdata(metod, url, argumenti){
    var rekvest = new XMLHttpRequest()
     if (metod.toUpperCase()=="GET") {

    console.log("GET");
    if ( argumenti && argumenti.length ) var celourl = url+"?"+argumenti;
    else celourl = url;
         rekvest.open(metod, celourl, false);
         /*rekvest.onreadystatechange = function() {//Call a function when the state changes.
             if(rekvest.readyState == 4 && rekvest.status == 200) {
                 return rekvest.responseText;
             }
         }*/
         rekvest.send(null);
         if (rekvest.status === 200) return rekvest.responseText;
         else return 0;
     }
     if (metod.toUpperCase()=="POST"){
    console.log("POST");
         rekvest.open(metod, url, false);
         /*rekvest.onreadystatechange = function() {//Call a function when the state changes.
             if(rekvest.readyState == 4 && rekvest.status == 200) {
                 return rekvest.responseText;
             }
         }*/
         rekvest.send(argumenti);
         if (rekvest.status === 200) return rekvest.responseText;
         else return 0;
     }
 }

</script>
